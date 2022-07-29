#include"sm3.h"
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
	free(padding_result);

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
	free(W);
	free(W_1);
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
string strRand(int length) {			// length: 产生字符串的长度
	char tmp;							// tmp: 暂存一个随机数
	string buffer;						// buffer: 保存返回值

	// 下面这两行比较重要:
	random_device rd;					// 产生一个 std::random_device 对象 rd
	default_random_engine random(rd());	// 用 rd 初始化一个随机数发生器 random

	for (int i = 0; i < length; i++) {
		tmp = random() % 36;	// 随机一个小于 36 的整数，0-9、A-Z 共 36 种字符
		if (tmp < 10) {			// 如果随机数小于 10，变换成一个阿拉伯数字的 ASCII
			tmp += '0';
		}
		else {				// 否则，变换成一个大写字母的 ASCII
			tmp -= 10;
			tmp += 'A';
		}
		buffer += tmp;
	}
	return buffer;
}
bool GetBitStatu(int num, int pos)
{
	if (num & (1 << pos)) //按位与之后的结果非0
		return 1;
	else
		return 0;
}
void build_tree(normal_node *root,uint32_t input,string sm3_input)//二叉搜索树储存器，用路径存储hash结果，叶子节点存储hash输入，将hash结果和hash输入存储入树中
{
	normal_node* ptr = root;
	int bit_status;
	for (int i = 0; i < 32; i++)
	{
		bit_status = GetBitStatu(input, i);
		if (bit_status == 1)
		{
			if (ptr->left_child != NULL)
				ptr = ptr->left_child;
			else
			{
				normal_node* child_node = new normal_node;
				child_node->left_child = nullptr;
				child_node->right_child = nullptr;
				ptr->left_child = child_node;
				ptr = ptr->left_child;
			}
		}
		else
		{
			if (ptr->right_child != NULL)
				ptr = ptr->right_child;
			else
			{
				normal_node* child_node = new normal_node;
				child_node->left_child = nullptr;
				child_node->right_child = nullptr;
				ptr->right_child = child_node;
				ptr = ptr->right_child;
			}
		}
	}
	ptr->sm3_input = sm3_input;
}
bool search_tree(uint32_t hash_result,normal_node* root)//搜索树接口，输入哈希结果及根节点，返回该结果是否在树中
{
	int bit_status;
	normal_node* ptr = root;
	for (int i = 0; i < 32; i++)
	{
		bit_status = GetBitStatu(hash_result, i);
		if (bit_status == 1)
		{
			if (ptr->left_child == NULL)
				return RESULT_NOT_FOUND;
			else
				ptr = ptr->left_child;
		}
		else
		{
			if (ptr->right_child == NULL)
				return RESULT_NOT_FOUND;
			else
				ptr = ptr->right_child;
		}
	}
	return RESULT_FOUND;
}
string get_hash_input_from_root(normal_node* root,uint32_t hash_result)//输入hash结果，root节点，从树中查询hash值对应的原像
{
	bool bit_status;
	normal_node* ptr = root;
	for (int i = 0; i < 32; i++)
	{
		bit_status = GetBitStatu(hash_result, i);
		if (bit_status == 1)
		{
			if (ptr->left_child == NULL)
				return "nod found";
			else
				ptr = ptr->left_child;
		}
		else
		{
			if (ptr->right_child == NULL)
				return "not found";
			else
				ptr = ptr->right_child;
		}
	}
	return ptr->sm3_input;
}
bool birthday_attack(normal_node* root)
{
	unsigned int length;
	char* hash_input;
	for (int i = 0; i < 65535; i++)
	{
		length = rand() % 56;
		string temp = strRand(length);
		hash_input = (char*)temp.c_str();
		uint8_t* sm3_input = (uint8_t*)malloc(length * sizeof(uint8_t));
		for (int i = 0; i < length; i++)
		{
			sm3_input[i] = hash_input[i];
		}
		sm3(sm3_input, length * 8);
		free(sm3_input);
		uint32_t reduce_result = SM3_hash_result[0];
		bool result = search_tree(reduce_result, root);
		if (result == RESULT_FOUND)
		{
			return RESULT_FOUND;//找到碰撞
		}
		build_tree(root, reduce_result, temp);
	}
}
int main()
{
	normal_node* root = new normal_node;
	root->left_child = nullptr;
	root->right_child = nullptr;
	bool collison_result=birthday_attack(root);
	if (collison_result == RESULT_FOUND)
	{
		printf("%s", "collision found!!!");
	}
}
