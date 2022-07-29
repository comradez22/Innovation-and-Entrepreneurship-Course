#include"sm3.h"
#include<cstdio>
#include<bitset>
#include<chrono>

uint8_t* padding(uint8_t* input, unsigned long long length)//length单位是比特,输入是以uint8_t数组的形式，输出padding好的uint8_t数组
{
	int k = 1;
	int total_length = (length / 512 + 1) * 512;//填充后比特长度
	int byte_length = length / 8;//填充前字节长度
	int total_byte_length = total_length / 8;//填充后字节长度
	for (k; k < total_length; k++)
	{
		if (((length + 1 + k) % 512) == 448)
			break;
	}
	uint8_t* output = (uint8_t*)malloc((total_length / 8) * sizeof(uint8_t));
	for (int i = 0; i < byte_length; i++)//首先output的前几个和input一致
	{
		output[i] = input[i];
	}

	output[byte_length] = 0x80;//赋值一个1和7个零

	int outfix = byte_length + 1 + (k - 7) / 8;//剩下的0的个数是（k-7）/8
	for (int i = byte_length + 1; i < outfix; i++)//为这些补0
	{
		output[i] = 0x00;
	}

	uint8_t* ptr = (uint8_t*)&length;
	for (int i = 0; i < 8; i++)
	{
		uint8_t temp = *ptr;
		output[total_byte_length - i - 1] = temp;
		ptr = ptr + 1;
	}
	after_padding_length = total_byte_length;
	return output;
}
void message_extension(uint8_t* input, uint32_t* W, uint32_t* W_1)//W是w0-w67，W_1是w0'-w63' uint32只支持输入长度是512bit以内,W和W_1传入之前必须先分配68和64个uint32_t空间
{
	int word_length = after_padding_length / 16;//消息字大小,也即一个消息字含有的uint8_t的数量
	//uint32_t* W = (uint32_t*)malloc(68 * sizeof(uint32_t));//即Wi不带'
	//uint32_t* W_1 = (uint32_t*)malloc(64 * sizeof(uint32_t));//Wi'
	for (int i = 0; i < 16; i++)
	{
		W[i] = MERAGE4(input[i * 4 + 0], input[i * 4 + 1], input[i * 4 + 2], input[i * 4 + 3]);
	}
	/*for (int i = 0; i < 16; i++)
	{
		printf("%x", W015[i]);
	}*/
	for (int i = 16; i < 68; i++)//W的计算 有68个
	{
		uint32_t Wj_16 = W[i - 16];
		uint32_t Wj_9 = W[i - 9];
		uint32_t Wj_3 = W[i - 3];
		uint32_t Wj_13 = W[i - 13];
		uint32_t Wj_6 = W[i - 6];
		uint32_t round_shift1 = round_shift_left(Wj_3, 15);
		uint32_t round_shift2 = round_shift_left(Wj_13, 7);
		uint32_t P1_input = Wj_16 ^ Wj_9 ^ round_shift1;
		uint32_t P1_result = P1(P1_input);
		W[i] = P1_result ^ round_shift2 ^ Wj_6;
	}
	/*for (int i = 0; i < 68; i++)
	{
		if (W[i] == 0)
			printf("00000000 ");
		else
			printf("%x ", W[i]);
		if (i % 4 == 0&&i!=0)
		{
			printf("\n");
		}
	}*/
	for (int i = 0; i < 64; i++)//w'的计算，64个
	{
		W_1[i] = W[i] ^ W[i + 4];
	}
	/*for (int i = 0; i < 64; i++)
	{
		printf("%x", W_1[i]);
	}*/

}
void CF(uint32_t* Vi, uint8_t* Bi, uint32_t* W, uint32_t* W_1,unsigned long long input_length)
{
	uint8_t* padding_result = (uint8_t*)malloc(64 * sizeof(uint8_t));
	padding_result = padding(Bi, input_length);
	message_extension(padding_result, W, W_1);


	uint32_t A, B, C, D, E, F, G, H, SS1, SS2, TT1, TT2, shift_left_Ti,FF_result,GG_result;//shift_left_Ti是Ti常数向左循环移位的结果
	A = IV[0], B = IV[1], C = IV[2], D = IV[3], E = IV[4], F = IV[5], G = IV[6], H = IV[7];
	for (int i = 0; i < 64; i++)
	{
		uint32_t A_round_shift_left_12 = round_shift_left(A, 12);
		unsigned int j_shift_left = i % 32;
		if (i <= 15)
			shift_left_Ti = round_shift_left(Tj015, j_shift_left);
		else
			shift_left_Ti = round_shift_left(Tj1663, j_shift_left);
		
		SS1 = (A_round_shift_left_12 + E + shift_left_Ti) % MODNUM;
		SS1 = round_shift_left(SS1, 7);
		SS2 = SS1 ^ A_round_shift_left_12;
		if (i <= 15)
		{
			FF_result = FFj015(A, B, C);
			GG_result = GGj015(E, F, G);
			TT1 = (FF_result + D + SS2 + W_1[i]) % MODNUM;
			TT2 = (GG_result + H + SS1 + W[i]) % MODNUM;
		}

		else
		{
			FF_result = FFj1663(A, B, C);
			GG_result = GGj1663(E, F, G);
			TT1 = (FF_result + D + SS2 + W_1[i]) % MODNUM;
			TT2 = (GG_result + H + SS1 + W[i]) % MODNUM;
		}
		D = C;
		C = round_shift_left(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = round_shift_left(F, 19);
		F = E;
		E = P0(TT2);
		//printf("%x %x %x %x %x %x %x %x \n", A, B, C, D, E, F, G, H);
	}
	SM3_hash_result[0] = A ^ IV[0];
	SM3_hash_result[1] = B ^ IV[1];
	SM3_hash_result[2] = C ^ IV[2];
	SM3_hash_result[3] = D ^ IV[3];
	SM3_hash_result[4] = E ^ IV[4];
	SM3_hash_result[5] = F ^ IV[5];
	SM3_hash_result[6] = G ^ IV[6];
	SM3_hash_result[7] = H ^ IV[7];
}
void CF_length_extension_attack(uint32_t* Vi, uint8_t* after_padding_input, uint32_t* W, uint32_t* W_1)
{
	message_extension(after_padding_input, W, W_1);


	uint32_t A, B, C, D, E, F, G, H, SS1, SS2, TT1, TT2, shift_left_Ti, FF_result, GG_result;//shift_left_Ti是Ti常数向左循环移位的结果
	A = IV[0], B = IV[1], C = IV[2], D = IV[3], E = IV[4], F = IV[5], G = IV[6], H = IV[7];
	for (int i = 0; i < 64; i++)
	{
		uint32_t A_round_shift_left_12 = round_shift_left(A, 12);
		unsigned int j_shift_left = i % 32;
		if (i <= 15)
			shift_left_Ti = round_shift_left(Tj015, j_shift_left);
		else
			shift_left_Ti = round_shift_left(Tj1663, j_shift_left);

		SS1 = (A_round_shift_left_12 + E + shift_left_Ti) % MODNUM;
		SS1 = round_shift_left(SS1, 7);
		SS2 = SS1 ^ A_round_shift_left_12;
		if (i <= 15)
		{
			FF_result = FFj015(A, B, C);
			GG_result = GGj015(E, F, G);
			TT1 = (FF_result + D + SS2 + W_1[i]) % MODNUM;
			TT2 = (GG_result + H + SS1 + W[i]) % MODNUM;
		}

		else
		{
			FF_result = FFj1663(A, B, C);
			GG_result = GGj1663(E, F, G);
			TT1 = (FF_result + D + SS2 + W_1[i]) % MODNUM;
			TT2 = (GG_result + H + SS1 + W[i]) % MODNUM;
		}
		D = C;
		C = round_shift_left(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = round_shift_left(F, 19);
		F = E;
		E = P0(TT2);
		//printf("%x %x %x %x %x %x %x %x \n", A, B, C, D, E, F, G, H);
	}
	SM3_hash_result[0] = A ^ IV[0];
	SM3_hash_result[1] = B ^ IV[1];
	SM3_hash_result[2] = C ^ IV[2];
	SM3_hash_result[3] = D ^ IV[3];
	SM3_hash_result[4] = E ^ IV[4];
	SM3_hash_result[5] = F ^ IV[5];
	SM3_hash_result[6] = G ^ IV[6];
	SM3_hash_result[7] = H ^ IV[7];
}
void sm3(uint8_t *input,unsigned long long length)//sm3哈希函数，输入仅支持512比特以内，以uint8数组形式输入,第二个参数是输入数据长度，单位是bit,函数计算完成后全局变量SM3_hash_result存储运算结果，形式是长度为8的uint32数组
{
	uint8_t* padding_result = (uint8_t*)malloc(64 * sizeof(uint8_t));
	padding_result = padding(input, length);
	uint32_t* W = (uint32_t*)malloc(68 * sizeof(uint32_t));//即Wi不带'
	uint32_t* W_1 = (uint32_t*)malloc(64 * sizeof(uint32_t));//Wi'
	CF(IV, input, W, W_1,length);
}
void print_sm3_result()
{
	for (int i = 0; i < 8; i++)
	{
		printf("%x ", SM3_hash_result[i]);
	}
}
void length_extension_attack(uint32_t* known_hash_result, uint8_t* append, unsigned long long append_length, uint32_t* W, uint32_t* W_1)
{
	CF(known_hash_result, append, W, W_1, append_length);
}
bool check_attack_result(uint32_t* known_hash_result, uint8_t* append, unsigned long long append_length, uint32_t* W, uint32_t* W_1,uint8_t *after_padding_input)//W和W_1传入之前必须先分配68和64个uint32_t空间
{
	bool check_result = 1;
	length_extension_attack(known_hash_result, append, append_length, W, W_1);
	uint32_t length_extension_attack_result[8];
	for (int i = 0; i < 8; i++)
	{
		length_extension_attack_result[i] = SM3_hash_result[i];//长度扩展攻击的结果
	}
//-------------------------------------------正常hash----------------------------------------	
	CF_length_extension_attack(IV, after_padding_input, W, W_1);
	CF(IV, append, W, W_1, 8);//正常哈希函数的结果
//-------------------------------------------正常hash----------------------------------------	
	for (int i = 0; i < 8; i++)//检测结果一致性
	{
		if (length_extension_attack_result[i] != SM3_hash_result[i])
		{
			return CHECK_FAIL;
		}
	}
	return CHECK_PASS;
}
int main()
{
	//-------------------------------------------sm3 hash使用--------------------------------------------------------
	int length = 24;
	uint8_t input[3] = {0x61,0x62,0x63};
	auto t_a = chrono::high_resolution_clock::now();
	for (int i = 0; i < 10000; i++)
	{
		sm3(input, length);
	}
	auto t_b = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<chrono::microseconds>(t_b - t_a).count() << endl;
	print_sm3_result();//66C7F0F4 62EEEDD9 D1F2D46B DC10E4E2 4167C487 5CF2F7A2 297DA02B 8F4BA8E0 验证结果正确

	//-------------------------------------------sm3 hash使用--------------------------------------------------------


		//-------------------------------------------sm3 长度拓展攻击--------------------------------------------------------
	uint32_t* W = (uint32_t*)malloc(68 * sizeof(uint32_t));//即Wi不带'
	uint32_t* W_1 = (uint32_t*)malloc(64 * sizeof(uint32_t));//Wi'
	uint8_t append[1] = { 0x18 };
	uint8_t* padding_result = (uint8_t*)malloc(64 * sizeof(uint8_t));
	padding_result = padding(input, length);
	bool check_result = check_attack_result(length_extension_example_known_hash_result, append, 8, W, W_1, padding_result);
	if (check_result == CHECK_PASS)
		printf("%s", "check pass!");
	else
		printf("%s", "check fail!");
	//-------------------------------------------sm3 长度拓展攻击--------------------------------------------------------
}
