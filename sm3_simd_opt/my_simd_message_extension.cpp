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
#include<iostream>
using namespace std;
__m256i round_shift_left(__m256i input, int length)
{
	length = length % 32;
	__m256i temp1, temp2, temp3, temp4;
	__m256i mask = _mm256_set1_epi32(0xffffffff);
	temp2 = _mm256_and_si256(mask, _mm256_slli_epi32(input, length));
	temp3 = _mm256_srli_epi32(_mm256_and_si256(mask, input), 32 - length);
	temp4 = _mm256_or_si256(temp2, temp3);
	return temp4;
}
__m512i round_shift_left_512(__m512i input, int length)
{
	length = length % 32;
	__m256i temp1, temp2, temp3, temp4;
	__m256i mask = _mm512_set1_epi64(0xffffffff);
	temp2 = _mm512_and_si512(mask, _mm512_slli_epi64(input, length));
	temp3 = _mm512_srli_epi64(_mm512_and_si512(mask, input), 32 - length);
	temp4 = _mm512_or_si512(temp2, temp3);
	return temp4;
}
__m256i P0(__m256i input)
{
	__m256i temp1 = round_shift_left(input, 9);
	__m256i temp2 = round_shift_left(input, 17);
	__m256i temp3 = _mm256_xor_epi32(temp1, temp2);
	__m256i temp4 = _mm256_xor_epi32(temp3, input);
	return temp4;
}
__m256i P1(__m256i input)
{
	__m256i temp1 = round_shift_left(input, 15);
	__m256i temp2 = round_shift_left(input, 23);
	__m256i temp3 = _mm256_xor_epi32(temp1, temp2);
	__m256i temp4 = _mm256_xor_epi32(temp3, input);
	return temp4;
}
void message_extension(unsigned int *input_block)//输入4096bit 即8个分组,同时对8个分组进行消息扩展
{
	unsigned int* W1 = (unsigned int*)malloc(68 * sizeof(unsigned int));
	unsigned int* W2 = (unsigned int*)malloc(68 * sizeof(unsigned int));
	unsigned int* W3 = (unsigned int*)malloc(68 * sizeof(unsigned int));
	unsigned int* W4 = (unsigned int*)malloc(68 * sizeof(unsigned int));
	unsigned int* W5 = (unsigned int*)malloc(68 * sizeof(unsigned int));
	unsigned int* W6 = (unsigned int*)malloc(68 * sizeof(unsigned int));
	unsigned int* W7 = (unsigned int*)malloc(68 * sizeof(unsigned int));
	unsigned int* W8 = (unsigned int*)malloc(68 * sizeof(unsigned int));
	unsigned int* W11 = (unsigned int*)malloc(64 * sizeof(unsigned int));
	unsigned int* W22 = (unsigned int*)malloc(64 * sizeof(unsigned int));
	unsigned int* W33 = (unsigned int*)malloc(64 * sizeof(unsigned int));
	unsigned int* W44 = (unsigned int*)malloc(64 * sizeof(unsigned int));
	unsigned int* W55 = (unsigned int*)malloc(64 * sizeof(unsigned int));
	unsigned int* W66 = (unsigned int*)malloc(64 * sizeof(unsigned int));
	unsigned int* W77 = (unsigned int*)malloc(64 * sizeof(unsigned int));
	unsigned int* W88 = (unsigned int*)malloc(64 * sizeof(unsigned int));
	__m256i block1;
	__m256i block2;
	__m256i block3;
	__m256i block4;
	__m256i block5;
	__m256i block6;
	__m256i block7;
	__m256i temp1;
	__m256i temp2;
	__m256i temp3;
	__m256i temp4;
	__m256i temp5;
	__m256i temp6;
	for (int i = 0; i < 16; i++)
	{
		W1[i] = input_block[i];
	}
	for (int i = 16; i < 32; i++)
	{
		W2[i - 16] = input_block[i];
	}
	for (int i = 32; i < 48; i++)
	{
		W1[i - 32] = input_block[i];
	}
	for (int i = 48; i < 64; i++)
	{
		W1[i - 48] = input_block[i];
	}
	for (int i = 64; i < 80; i++)
	{
		W1[i - 64] = input_block[i];
	}
	for (int i = 80; i < 98; i++)
	{
		W1[i - 80] = input_block[i];
	}
	for (int i = 96; i < 112; i++)
	{
		W1[i - 96] = input_block[i];
	}
	for (int i = 112; i < 128; i++)
	{
		W1[i - 112] = input_block[i];
	}


	for (int i = 16; i < 68; i++)
	{
		block1 = _mm256_set_epi32(W1[i - 16], W2[i - 16], W3[i - 16], W4[i - 16], W5[i - 16], W6[i - 16], W7[i - 16], W8[i - 16]);
		block2 = _mm256_set_epi32(W1[i - 9], W2[i - 9], W3[i - 9], W4[i - 9], W5[i - 9], W6[i - 9], W7[i - 9], W8[i - 9]);
		block3 = _mm256_set_epi32(W1[i - 3], W2[i - 3], W3[i - 3], W4[i - 3], W5[i - 3], W6[i - 3], W7[i - 3], W8[i - 3]);
		block3 = round_shift_left(block3, 15);
		block4 = _mm256_set_epi32(W1[i - 13], W2[i - 13], W3[i - 13], W4[i - 13], W5[i - 13], W6[i - 13], W7[i - 13], W8[i - 13]);
		block4 = round_shift_left(block4, 7);
		block5 = _mm256_set_epi32(W1[i - 6], W2[i - 6], W3[i - 6], W4[i - 6], W5[i - 6], W6[i - 6], W7[i - 6], W8[i - 6]);
		temp1= _mm256_xor_epi32(block4, block5);//j-13和j-6异或结果
		temp2 = _mm256_xor_epi32(block1, block2);
		temp3 = _mm256_xor_epi32(temp2, block3);
		temp4 = P0(block3);//P0结果
		temp5 = _mm256_xor_epi32(temp1, temp4);//一个结果，存有8组W1-W8的结果
		unsigned int* ptr = (unsigned int*)&temp5;
		W1[i] = *(ptr);
		W2[i] = *(ptr + 1);
		W3[i] = *(ptr + 2);
		W4[i] = *(ptr + 3);
		W5[i] = *(ptr + 4);
		W6[i] = *(ptr + 5);
		W7[i] = *(ptr + 6);
		W8[i] = *(ptr + 7);
	}
	for (int i = 0; i < 64; i++)
	{
		block6 = _mm256_set_epi32(W1[i], W2[i], W3[i], W4[i], W5[i], W6[i], W7[i], W8[i]);
		block7 = _mm256_set_epi32(W1[i + 4], W2[i + 4], W3[i + 4], W4[i + 4], W5[i + 4], W6[i + 4], W7[i + 4], W8[i + 4]);
		temp6 = _mm256_xor_epi32(block6, block7);
		unsigned int* ptr = (unsigned int*)&temp6;
		W11[i] = *(ptr);
		W22[i] = *(ptr + 1);
		W33[i] = *(ptr + 2);
		W44[i] = *(ptr + 3);
		W55[i] = *(ptr + 4);
		W66[i] = *(ptr + 5);
		W77[i] = *(ptr + 6);
		W88[i] = *(ptr + 7);
	}
}
void CF(unsigned int* W, unsigned int* W_1,unsigned int *Vi)//输入八组消息的W,W',以及Vi 长度分别是17408bit，16384bit，2048bit
{
	unsigned int* A = (unsigned int*)malloc(8 * sizeof(unsigned int));
	unsigned int* B = (unsigned int*)malloc(8 * sizeof(unsigned int));
	unsigned int* C = (unsigned int*)malloc(8 * sizeof(unsigned int));
	unsigned int* D = (unsigned int*)malloc(8 * sizeof(unsigned int));
	unsigned int* E = (unsigned int*)malloc(8 * sizeof(unsigned int));
	unsigned int* F = (unsigned int*)malloc(8 * sizeof(unsigned int));
	unsigned int* G = (unsigned int*)malloc(8 * sizeof(unsigned int));
	unsigned int* H = (unsigned int*)malloc(8 * sizeof(unsigned int));
	for (int i = 0; i < 8; i++)//将上一轮Vi对A-H进行赋值
	{
		A[i] = Vi[8 * i + 0];
		B[i] = Vi[8 * i + 1];
		C[i] = Vi[8 * i + 2];
		D[i] = Vi[8 * i + 3];
		E[i] = Vi[8 * i + 4];
		F[i] = Vi[8 * i + 5];
		G[i] = Vi[8 * i + 6];
		H[i] = Vi[8 * i + 7];
	}
	__m512i block1;
	__m512i block2;
	__m512i block3;
	__m512i block4;
	__m512i block5;
	__m512i block6;
	__m512i block7;
	__m512i block8;
	__m512i SS1s;
	__m512i SS2s;
	__m512i TT1s;
	__m512i TT2s;
	__m512i temp1;
	__m512i temp2;
	__m512i temp3;
	__m512i temp4;
	__m512i temp5;
	__m512i temp6;
	__m512i temp7;
	__m512i temp8;
	__m512i temp9;
	__m512i temp10;
	__m512i Ti015;
	__m512 Ti1663;
	block1 = _mm512_set_epi64(A[0], A[1], A[2], A[3], A[4], A[5], A[6], A[7]);
	block2 = _mm512_set_epi64(B[0], B[1], B[2], B[3], B[4], B[5], B[6], B[7]);
	block3 = _mm512_set_epi64(C[0], C[1], C[2], C[3], C[4], C[5], C[6], C[7]);
	block4 = _mm512_set_epi64(D[0], D[1], D[2], D[3], D[4], D[5], D[6], D[7]);
	block5 = _mm512_set_epi64(E[0], E[1], E[2], E[3], E[4], E[5], E[6], E[7]);
	block6 = _mm512_set_epi64(F[0], F[1], F[2], F[3], F[4], F[5], F[6], F[7]);
	block7 = _mm512_set_epi64(G[0], G[1], G[2], G[3], G[4], G[5], G[6], G[7]);
	block8 = _mm512_set_epi64(H[0], H[1], H[2], H[3], H[4], H[5], H[6], H[7]);
	Ti015 = _mm512_set1_epi64(0x79cc4519);
	Ti1663 = _mm512_set1_epi64(0x7a879d8a);
	for (int i = 0; i < 64; i++)
	{
		temp1 = round_shift_left_512(block1, 12);
		if (i <= 15)
			temp2 = round_shift_left_512(Ti015, i % 32);
		else
			temp2 = round_shift_left_512(Ti1663, i % 32);
		temp3 = _mm512_add_epi64(temp1, block5);
		
	}
}
