#include<iostream>
#include "SM4.h"
#include<map>
#include<bitset>
#include<chrono>
#include <mmintrin.h> //MMX  
#include <xmmintrin.h> //SSE(include mmintrin.h)  
#include <emmintrin.h> //SSE2(include xmmintrin.h)  
#include <pmmintrin.h> //SSE3(include emmintrin.h)  
#include <tmmintrin.h>//SSSE3(include pmmintrin.h)  
#include <smmintrin.h>//SSE4.1(include tmmintrin.h)  
#include <nmmintrin.h>//SSE4.2(include smmintrin.h)  
#include <wmmintrin.h>//AES(include nmmintrin.h)  
#include <immintrin.h>//AVX(include wmmintrin.h)  
#include <intrin.h>//(include immintrin.h)
double supertime = 0;
double timesuper = 0;
/*以下四个宏定义用来解包读好的256寄存器中的某些32bit的数据
LOLOLO 用于解包所有8个明文的第3个
HILOLO 用于解包所有8个明文的第2个
LOHIHI 用于解包所有8个明文的第1个
HIHIHI 用于解包所有8个明文的第0个*/
#define _64_32_32_LO_LO_LO(a, b, c, d)                  \
    _mm256_unpacklo_epi64(_mm256_unpacklo_epi32(a, b), \
                          _mm256_unpacklo_epi32(c, d))
#define _64_32_32_HI_LO_LO(a, b, c, d)                  \
    _mm256_unpackhi_epi64(_mm256_unpacklo_epi32(a, b), \
                          _mm256_unpacklo_epi32(c, d))
#define _64_32_32_LO_HI_HI(a, b, c, d)                  \
    _mm256_unpacklo_epi64(_mm256_unpackhi_epi32(a, b), \
                          _mm256_unpackhi_epi32(c, d))
#define _64_32_32_HI_HI_HI(a, b, c, d)                  \
    _mm256_unpackhi_epi64(_mm256_unpackhi_epi32(a, b), \
                          _mm256_unpackhi_epi32(c, d))
//循环移位，向左循环，循环移出的补回
#define RoundRoll(value, shift) ((value << shift) | value >> (32 - shift))
using namespace std;
//----------------------------------sbox---------------------------------
bitset<8> get_sbox_result(bitset<8> input)
{
	bitset<8> result;
	int first = 8 * input[7] + 4 * input[6] + 2 * input[5] + input[4];
	int second = 8 * input[3] + 4 * input[2] + 2 * input[1] + input[0];
	result = TBL_SBOX[first][second];
	return result;
}
//----------------------------------sbox---------------------------------

//----------------------------------L置换---------------------------------
bitset<32> get_lchange_result(bitset<32> input)
{
	bitset<32> shift_2 = input << 2 | input >> 30;
	bitset<32> shift_10 = input << 10 | input >> 22;
	bitset<32> shift_18 = input << 18 | input >> 14;
	bitset<32> shift_24 = input << 24 | input >> 8;
	bitset<32>result = input ^ shift_2 ^ shift_10 ^ shift_18 ^ shift_24;
	return result;
}

//----------------------------------L置换---------------------------------


//----------------------------------T函数---------------------------------
bitset<32> get_Tfunc_result(bitset<32> input)
{
	bitset<8> set1;
	bitset<8> set2;
	bitset<8> set3;
	bitset<8> set4;
	bitset<32> Lresult = get_lchange_result(input);
	for (int i = 0; i < 8; i++)
	{
		set1[i] = Lresult[i];
	}
	for (int i = 8; i < 16; i++)
	{
		set2[i-8] = Lresult[i];
	}
	for (int i = 16; i < 24; i++)
	{
		set3[i-16] = Lresult[i];
	}
	for (int i = 24; i < 32; i++)
	{
		set4[i-24] = Lresult[i];
	}
	set1 = get_sbox_result(set1);
	set2 = get_sbox_result(set2);
	set3 = get_sbox_result(set3);
	set4 = get_sbox_result(set4);
	bitset<32> result;
	for (int i = 0; i < 8; i++)
	{
		result[i] = set1[i];
	}
	for (int i = 0; i < 8; i++)
	{
		result[8 + i] = set2[i];
	}
	for (int i = 0; i < 8; i++)
	{
		result[16 + i] = set3[i];
	}
	for (int i = 0; i < 8; i++)
	{
		result[24 + i] = set4[i];
	}
	return result;
}
//----------------------------------T函数---------------------------------



//----------------------------------L置换-密钥---------------------------------
bitset<32> get_key_lchange_result(bitset<32> input)
{
	bitset<32> shift_13 = input << 13 | input >> 19;
	bitset<32> shift_23 = input << 23 | input >> 9;
	bitset<32>result = input ^shift_13 ^ shift_23;
	return result;
}
//----------------------------------L置换-密钥---------------------------------


//----------------------------------查表T函数---------------------------------
bitset<32> Tfunc_table(bitset<32> input)
{
	bitset<32> set1;
	bitset<32> set2;
	bitset<32> set3;
	bitset<32> set4;
	int index1, index2, index3, index4; index1 = index2 = index3 = index4 = 0;
	for (int i = 31; i > 23; i--)
	{
		index1 = index1 + input[i] * pow(2, i - 24);
	}
	for (int i = 23; i > 15; i--)
	{
		index2 = index2 + input[i] * pow(2, i - 16);
	}
	for (int i = 15; i > 7; i--)
	{
		index3 = index3 + input[i] * pow(2, i - 8);
	}
	for (int i = 7; i >=0; i--)
	{
		index4 = index4 + input[i] * pow(2, i);
	}
	set1 = Table0[index1];
	set2 = Table1[index2];
	set3 = Table2[index3];
	set4 = Table3[index4];
	bitset<32> result = set1 ^ set2 ^ set3 ^ set4;
	return result;
}

//----------------------------------查表T函数---------------------------------



//----------------------------------轮密钥生成---------------------------------
bitset<32>* gen_round_key(bitset<128> input)
{
	bitset<32> MK0, MK1, MK2, MK3, K0, K1, K2, K3, TempK0, TempK1, TempK2, TempK3, TempK4, CKI_Temp, Temp, Temp_T_Result;
	bitset<32>* result = (bitset<32>*)malloc(32 * sizeof(bitset<32>));
	for (int i = 0; i < 32; i++)
	{
		MK0[i] = input[i];
	}
	for (int i = 32; i < 64; i++)
	{
		MK1[i-32] = input[i];
	}
	for (int i = 64; i < 96; i++)
	{
		MK2[i-64] = input[i];
	}
	for (int i = 96; i < 128; i++)
	{
		MK3[i-96] = input[i];
	}
	K0 = FK0 ^ MK0;
	K1 = FK1 ^ MK1;
	K2 = FK2 ^ MK2;
	K3 = FK3 ^ MK3;
	TempK0 = K0;
	TempK1 = K1;
	TempK2 = K2;
	TempK3 = K3;
	for (int i = 0; i < 32; i++)
	{
		CKI_Temp = CKI[i];
		Temp = TempK1 ^ TempK2 ^ TempK3 ^ CKI_Temp;
		Temp_T_Result = get_key_lchange_result(Temp);
		TempK4 = Temp_T_Result ^ TempK0;
		*(result + i) = TempK4;//储存结果
		TempK0 = TempK1;//更新各个计算中间值
		TempK1 = TempK2;
		TempK2 = TempK3;
		TempK3 = TempK4;
	}
	return result;
}
//----------------------------------轮密钥生成---------------------------------



//----------------------------------32轮加密查表优化版本循环展开---------------------------------
bitset<128> SM4Encrypt_table_vision(bitset<128> plaintext, bitset<128> key)//每次加密都要生成新密钥版本
{
	bitset<32>  X0, X1, X2, X3, TempX0, TfunInput, TfuncResult, 
			    X00, X11, X22, X33, TempX00, TfunInput1, TfuncResult1, 
				X000, X111, X222, X333, TempX000, TfunInput11, TfuncResult11, 
				X0000, X1111, X2222, X3333, TempX0000, TfunInput111, TfuncResult111;

	bitset<128> CipherText;
	bitset<32>* RoundKey = gen_round_key(key);
	//明文分组
	for (int i = 0; i < 32; i++)
	{
		X0[i] = plaintext[i];
	}
	for (int i = 32; i < 64; i++)
	{
		X1[i - 32] = plaintext[i];
	}
	for (int i = 64; i < 96; i++)
	{
		X2[i - 64] = plaintext[i];
	}
	for (int i = 96; i < 128; i++)
	{
		X3[i - 96] = plaintext[i];
	}
	//32轮加密开始
	for (int i = 0; i < 8; i++)
	{
		TfunInput = X1 ^ X2 ^ X3 ^ *(RoundKey + i);
		TfuncResult = Tfunc_table(TfunInput);
		TempX0 = X0 ^ TfuncResult;
		X00 = X1;
		X11 = X2;
		X22 = X3;
		X33 = TempX0;
		TfunInput1 = X11 ^ X22 ^ X33 ^ *(RoundKey + i + 1);
		TfuncResult1 = Tfunc_table(TfunInput1);
		TempX00 = X00 ^ TfuncResult1;
		X000 = X11;
		X111 = X22;
		X222 = X33;
		X333 = TempX00;
		TfuncResult11= X111 ^ X222 ^ X333 ^ *(RoundKey + i + 2);
		TfuncResult11 = Tfunc_table(TfunInput11);
		TempX000 = X000 ^ TfuncResult11;
		X0000 = X111;
		X1111 = X222;
		X2222 = X333;
		TfunInput111 = X1111 ^ X2222 ^ X3333 ^ *(RoundKey + i + 3);
		TfuncResult111 = Tfunc_table(TfunInput111);
		TempX0000 = X0000 ^ TfuncResult11;
		X0 = X1111;
		X1 = X2222;
		X2 = X3333;
		X3 = TempX0000;
	}
	//32轮加密结束，开始反序结果
	for (int i = 0; i < 32; i++)
	{
		CipherText[i] = X33[i];
	}
	for (int i = 32; i < 64; i++)
	{
		CipherText[i] = X22[i - 32];
	}
	for (int i = 64; i < 96; i++)
	{
		CipherText[i] = X11[i - 64];
	}
	for (int i = 96; i < 128; i++)
	{
		CipherText[i] = X00[i - 96];
	}
	return CipherText;
}
//----------------------------------32轮加密查表优化版本---------------------------------


//----------------------------------32轮加密查表普通版本---------------------------------
bitset<128> SM4Encrypt_round_vision(bitset<128> plaintext, bitset<128> key)//每次加密都要生成新密钥版本
{
	bitset<32> X0, X1, X2, X3, TempX0, TfunInput, TfuncResult;
	bitset<128> CipherText;
	bitset<32>* RoundKey = gen_round_key(key);
	//明文分组
	for (int i = 0; i < 32; i++)
	{
		X0[i] = plaintext[i];
	}
	for (int i = 32; i < 64; i++)
	{
		X1[i - 32] = plaintext[i];
	}
	for (int i = 64; i < 96; i++)
	{
		X2[i - 64] = plaintext[i];
	}
	for (int i = 96; i < 128; i++)
	{
		X3[i - 96] = plaintext[i];
	}
	//32轮加密开始
	auto startTime = std::chrono::system_clock::now();
	for (int i = 0; i < 32; i++)
	{
		
		TfunInput = X1 ^ X2 ^ X3 ^ *(RoundKey + i);
		auto startTime = std::chrono::system_clock::now();
		TfuncResult = get_Tfunc_result(TfunInput);
		auto endTime = std::chrono::system_clock::now();
		timesuper+= std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
		TempX0 = X0 ^ TfuncResult;
		X0 = X1;
		X1 = X2;
		X2 = X3;
		X3 = TempX0;
	}
	auto endTime = std::chrono::system_clock::now();
	supertime+= std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
	//32轮加密结束，开始反序结果
	for (int i = 0; i < 32; i++)
	{
		CipherText[i] = X3[i];
	}
	for (int i = 32; i < 64; i++)
	{
		CipherText[i] = X2[i - 32];
	}
	for (int i = 64; i < 96; i++)
	{
		CipherText[i] = X1[i - 64];
	}
	for (int i = 96; i < 128; i++)
	{
		CipherText[i] = X0[i - 96];
	}
	return CipherText;
}
//----------------------------------32轮加密查表普通版本---------------------------------

//----------------------------------32轮加密查表一次轮密钥生成版本---------------------------------
bitset<128> SM4Encrypt_table_one_vision(bitset<128> plaintext, bitset<128> key,bitset<32> *RoundKey)
{
	bitset<32> X0, X1, X2, X3, TempX0, TfunInput, TfuncResult;
	bitset<128> CipherText;
	//bitset<32>* RoundKey = gen_round_key(key);
	//明文分组
	for (int i = 0; i < 32; i++)
	{
		X0[i] = plaintext[i];
	}
	for (int i = 32; i < 64; i++)
	{
		X1[i - 32] = plaintext[i];
	}
	for (int i = 64; i < 96; i++)
	{
		X2[i - 64] = plaintext[i];
	}
	for (int i = 96; i < 128; i++)
	{
		X3[i - 96] = plaintext[i];
	}
	//32轮加密开始
	for (int i = 0; i < 32; i++)
	{
		TfunInput = X1 ^ X2 ^ X3 ^ *(RoundKey + i);
		TfuncResult = Tfunc_table(TfunInput);
		TempX0 = X0 ^ TfuncResult;
		X0 = X1;
		X1 = X2;
		X2 = X3;
		X3 = TempX0;
	}
	//32轮加密结束，开始反序结果
	for (int i = 0; i < 32; i++)
	{
		CipherText[i] = X3[i];
	}
	for (int i = 32; i < 64; i++)
	{
		CipherText[i] = X2[i - 32];
	}
	for (int i = 64; i < 96; i++)
	{
		CipherText[i] = X1[i - 64];
	}
	for (int i = 96; i < 128; i++)
	{
		CipherText[i] = X0[i - 96];
	}
	return CipherText;
}