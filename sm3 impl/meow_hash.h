#pragma once
unsigned char inv_S[256] = {
		0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
		0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
		0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
		0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
		0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
		0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
		0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
		0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
		0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
		0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
		0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
		0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
		0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
		0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
		0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
		0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};
unsigned char S[256] = {
		0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
		0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
		0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
		0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
		0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
		0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
		0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
		0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
		0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
		0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
		0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
		0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
		0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
		0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
		0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
		0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};
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
#include<string>
#include<stdio.h>
uint8_t GF2 = 0x1B;
#define LOAD32H(x, y) \
  do { (x) = ((uint32_t)((y)[0] & 0xff)<<24) | ((uint32_t)((y)[1] & 0xff)<<16) | \
             ((uint32_t)((y)[2] & 0xff)<<8)  | ((uint32_t)((y)[3] & 0xff));} while(0)

// uint32_t x -> uint8_t y[4]
#define STORE32H(x, y) \
  do { (y)[0] = (uint8_t)(((x)>>24) & 0xff); (y)[1] = (uint8_t)(((x)>>16) & 0xff);   \
       (y)[2] = (uint8_t)(((x)>>8) & 0xff); (y)[3] = (uint8_t)((x) & 0xff); } while(0)
#define ROF32(x, n)  (((x) << (n)) | ((x) >> (32-(n))))
// uint32_t x循环右移n位
#define ROR32(x, n)  (((x) >> (n)) | ((x) << (32-(n))))
uint8_t HashOutput[16] = { 0x73,0x64,0x75,0x5f,0x63,0x73,0x74,0x5f,
						0x32,0x30,0x32,0x32,0x30,0x36,0x31,0x30 };//sdu_cst_20220610
uint8_t Lane1[16] = { 0x29, 0x6b, 0xd6, 0xeb, 0x2c, 0xa9, 0x3, 0x21, 0xbb, 0xef, 0x5f, 0x5f, 0x4c, 0xfc, 0x10, 0xec };
uint8_t Lane2[16] = { 0xbe, 0xd4, 0xed, 0x51, 0x6, 0x45, 0x4d, 0x99, 0x25, 0x8e, 0x51, 0x65, 0x53, 0x5, 0x5c, 0x33 };
uint8_t Lane3[16] = { 0xec, 0x3f, 0x54, 0x16, 0xa7, 0x22, 0xcd, 0xcc, 0x8f, 0x60, 0xd4, 0xf3, 0x4e, 0x4a, 0x60, 0x3d };
uint8_t Lane4[16] = { 0xcb, 0xee, 0x2f, 0x68, 0x16, 0x75, 0x93, 0x6d, 0x35, 0x33, 0xf4, 0xd, 0x4c, 0xe6, 0x5, 0x39 };
uint8_t Lane5[16] = { 0x21, 0x10, 0x73, 0x11, 0x8b, 0xd0, 0xa1, 0x5a, 0x50, 0x63, 0x91, 0x32, 0xd8, 0xf6, 0xa8, 0xe9 };
uint8_t Lane6[16] = { 0xf9, 0x80, 0x72, 0x40, 0x8d, 0x6e, 0x79, 0xec, 0xa1, 0x2b, 0x72, 0x36, 0x92, 0x67, 0xb6, 0x76 };
uint8_t Lane7[16] = { 0x35, 0x2a, 0xea, 0xdd, 0xf3, 0x5, 0x31, 0x4e, 0x9, 0xf0, 0xcf, 0xb, 0x35, 0xc9, 0xb0, 0xb9 };
uint8_t HashInput[32] = { 0x5a ,0x68, 0x61, 0x6e, 0x67, 0x48, 0x61, 0x6f,
						0x59, 0x61, 0x6e, 0x67, 0x32, 0x30, 0x32, 0x30,
						0x30, 0x30, 0x34, 0x36, 0x30, 0x30, 0x39, 0x38,
						0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };//ZhangHaoYang202000460098 padded
uint8_t LengthBlock[32] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
uint8_t InitKey[128] = { 0x99, 0x25, 0xae, 0xb4, 0x3b, 0x8f, 0xf2, 0xad, 0xb6, 0xa4, 0x97, 0x3b, 0x4, 0x26, 0x76, 0x66,
0x98, 0xf8, 0xab, 0x8, 0x2d, 0xb8, 0x96, 0x95, 0xf4, 0x97, 0xb3, 0xd0, 0x74, 0x57, 0xd2, 0x7c,
0x1d, 0xb3, 0xb6, 0x9, 0x26, 0xe2, 0x6e, 0x2a, 0xa0, 0x60, 0xa1, 0xd9, 0xee, 0xd, 0xaf, 0x20,
0x3c, 0x24, 0xf2, 0x6c, 0xdd, 0x71, 0xb3, 0x9b, 0xae, 0xe9, 0x8c, 0x48, 0x8f, 0x27, 0x54, 0xbe,
0x6e, 0xa1, 0xdc, 0x98, 0x87, 0x6b, 0x65, 0x2, 0x3c, 0xb9, 0xaf, 0x11, 0xcf, 0x1, 0x1, 0x4a,
0xd9, 0x9b, 0x42, 0xa0, 0x2f, 0xeb, 0x36, 0xb, 0xd3, 0x41, 0x9f, 0x8f, 0x95, 0x16, 0xce, 0x41,
0x3f, 0x24, 0x8c, 0x9c, 0xc1, 0xa1, 0x5, 0x92, 0x9c, 0x9c, 0x7d, 0x78, 0xad, 0x42, 0x9d, 0x84,
0x90, 0xbf, 0xe7, 0x40, 0x9e, 0xa2, 0x30, 0x41, 0x90, 0x70, 0x1f, 0xf6, 0x73, 0xaf, 0xc0, 0xbf, };
uint8_t GMul(uint8_t u, uint8_t v)
{
	uint8_t p = 0;

	for (int i = 0; i < 8; ++i)
	{
		if (u & 0x01)
		{    //
			p ^= v;
		}

		int flag = (v & 0x80);
		v <<= 1;
		if (flag)
		{
			v ^= 0x1B; /* x^8 + x^4 + x^3 + x + 1 */
		}

		u >>= 1;
	}

	return p;
}
uint8_t* invSubBytes(uint8_t(*state)[4]) {
	/* i: row, j: col */
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			state[i][j] = inv_S[state[i][j]];
		}
	}
	uint8_t* result = (uint8_t*)malloc(16 * sizeof(uint8_t));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[4 * i + j] = state[i][j];
		}
	}
	return result;
}
uint8_t* subBytes(uint8_t(*state)[4]) {
	/* i: row, j: col */
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			state[i][j] = S[state[i][j]]; //直接使用原始字节作为S盒数据下标
		}
	}
	uint8_t* result = (uint8_t*)malloc(16 * sizeof(uint8_t));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[4 * i + j] = state[i][j];
		}
	}
	return result;

}
uint8_t* Iv_S(uint8_t* input)
{
	uint8_t temp[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp[i][j] = input[4 * i + j];
		}
	}
	return invSubBytes(temp);
}
uint8_t* SBOX(uint8_t* input)
{
	uint8_t temp[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp[i][j] = input[4 * i + j];
		}
	}
	return subBytes(temp);
}
uint8_t* invMixColumns(uint8_t(*state)[4])
{
	uint8_t tmp[4][4];
	uint8_t M[4][4] = { {0x0E, 0x0B, 0x0D, 0x09},
					   {0x09, 0x0E, 0x0B, 0x0D},
					   {0x0D, 0x09, 0x0E, 0x0B},
					   {0x0B, 0x0D, 0x09, 0x0E} };  //使用列混合矩阵的逆矩阵
	uint8_t* result = (uint8_t*)malloc(16 * sizeof(uint8_t));
	/* copy state[4][4] to tmp[4][4] */
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			tmp[i][j] = state[i][j];
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			state[i][j] = GMul(M[i][0], tmp[0][j]) ^ GMul(M[i][1], tmp[1][j])
				^ GMul(M[i][2], tmp[2][j]) ^ GMul(M[i][3], tmp[3][j]);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[4 * i + j] = state[i][j];
		}
	}
	return result;
}
uint8_t* Iv_MixColums(uint8_t* input)
{
	uint8_t temp[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp[i][j] = input[4 * i + j];
		}
	}
	return invMixColumns(temp);
}
uint8_t* mixColumns(uint8_t(*state)[4]) {
	uint8_t tmp[4][4];
	uint8_t M[4][4] = { {0x02, 0x03, 0x01, 0x01},
					   {0x01, 0x02, 0x03, 0x01},
					   {0x01, 0x01, 0x02, 0x03},
					   {0x03, 0x01, 0x01, 0x02} };

	/* copy state[4][4] to tmp[4][4] */
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			tmp[i][j] = state[i][j];
		}
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {  //伽罗华域加法和乘法
			state[i][j] = GMul(M[i][0], tmp[0][j]) ^ GMul(M[i][1], tmp[1][j])
				^ GMul(M[i][2], tmp[2][j]) ^ GMul(M[i][3], tmp[3][j]);
		}
	}
	uint8_t* result = (uint8_t*)malloc(16 * sizeof(uint8_t));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[4 * i + j] = state[i][j];
		}
	}
	return result;

}
uint8_t* MixColumns(uint8_t* input)
{
	uint8_t temp[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp[i][j] = input[4 * i + j];
		}
	}
	return mixColumns(temp);
}
uint8_t* invShiftRows(uint8_t(*state)[4]) {
	uint32_t block[4] = { 0 };

	/* i: row */
	for (int i = 0; i < 4; ++i) {
		LOAD32H(block[i], state[i]);
		block[i] = ROR32(block[i], 8 * i);
		STORE32H(block[i], state[i]);
	}
	uint8_t* result = (uint8_t*)malloc(16 * sizeof(uint8_t));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[4 * i + j] = state[i][j];
		}
	}
	return result;
}
uint8_t* Iv_ShiftRows(uint8_t* input)
{
	uint8_t temp[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp[i][j] = input[4 * i + j];
		}
	}
	return invShiftRows(temp);
}
uint8_t* shiftRows(uint8_t(*state)[4]) {
	uint32_t block[4] = { 0 };

	/* i: row */
	for (int i = 0; i < 4; ++i) {
		//便于行循环移位，先把一行4字节拼成uint_32结构，移位后再转成独立的4个字节uint8_t
		LOAD32H(block[i], state[i]);
		block[i] = ROF32(block[i], 8 * i);
		STORE32H(block[i], state[i]);
	}
	uint8_t* result = (uint8_t*)malloc(16 * sizeof(uint8_t));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[4 * i + j] = state[i][j];
		}
	}
	return result;
}
uint8_t* shiftrows(uint8_t* input)
{
	uint8_t temp[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp[i][j] = input[4 * i + j];
		}
	}
	return shiftRows(temp);
}
uint8_t multiply_by_2(uint8_t input)
{
	if (input >= 128)
	{
		uint8_t temp = (input << 1) ^ GF2;
		return temp;
	}
	else
	{
		return input << 1;
	}
}
uint8_t multiply_by_3(uint8_t input)
{
	uint8_t temp = multiply_by_2(input);
	return temp ^ input;
}
uint8_t* aes(uint8_t* input)
{
	uint8_t* t1 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	t1 = Iv_ShiftRows(input);
	t1 = Iv_S(t1);
	t1 = Iv_MixColums(t1);
	return t1;
}//aes过程
uint8_t* iv_aes(uint8_t* input)
{
	uint8_t* t1 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	t1 = MixColumns(input);
	t1 = SBOX(t1);
	t1 = shiftrows(t1);
	return t1;
}//逆aes过程
uint8_t* xor_normal(uint8_t* input1, uint8_t* input2)
{
	uint8_t* result = (uint8_t*)malloc(16 * sizeof(uint8_t));
	for (int i = 0; i < 16; i++)
	{
		result[i] = input1[i] ^ input2[i];
	}
	return result;
}
uint8_t* xor_message(uint8_t* input1, uint8_t* message_block, int start)
{
	uint8_t* temp = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* result = (uint8_t*)malloc(16 * sizeof(uint8_t));
	for (int i = start; i < start + 16; i++)
	{
		temp[i - start] = message_block[i];
	}
	result = xor_normal(temp, input1);
	return result;
}
uint8_t* add_normal(uint8_t* input1, uint8_t* input2)
{
	uint8_t* res;
	__m128i temp1 = _mm_set_epi8(input1[0], input1[1], input1[2], input1[3], input1[4], input1[5], input1[6], input1[7], input1[8], input1[9], input1[10], input1[11], input1[12], input1[13], input1[14], input1[15]);
	__m128i temp2 = _mm_set_epi8(input2[0], input2[1], input2[2], input2[3], input2[4], input2[5], input2[6], input2[7], input2[8], input2[9], input2[10], input2[11], input2[12], input2[13], input2[14], input2[15]);
	__m128i temp3 = _mm_add_epi64(temp1, temp2);
	res = (uint8_t*)&temp3;
	return res;
}
uint8_t* add_normal_inverse(uint8_t* input1, uint8_t* input2)
{
	uint8_t* res;
	__m128i temp1 = _mm_set_epi8(input1[0], input1[1], input1[2], input1[3], input1[4], input1[5], input1[6], input1[7], input1[8], input1[9], input1[10], input1[11], input1[12], input1[13], input1[14], input1[15]);
	__m128i temp2 = _mm_set_epi8(input2[0], input2[1], input2[2], input2[3], input2[4], input2[5], input2[6], input2[7], input2[8], input2[9], input2[10], input2[11], input2[12], input2[13], input2[14], input2[15]);
	__m128i temp3 = _mm_sub_epi64(temp1, temp2);
	res = (uint8_t*)&temp3;
	return res;
}
uint8_t* AbsorptionFunction(uint8_t* MessageBlock, uint8_t* Lanes)
{

	uint8_t* L0 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L1 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L2 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L3 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L4 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L5 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L6 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L7 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L0 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L1 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L2 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L3 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L4 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L5 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L6 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L7 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* result = (uint8_t*)malloc(128 * sizeof(uint8_t));
	for (int i = 0; i < 16; i++)
		L0[i] = Lanes[i];
	for (int i = 0; i < 16; i++)
		L1[i] = Lanes[i + 16];
	for (int i = 0; i < 16; i++)
		L2[i] = Lanes[i + 32];
	for (int i = 0; i < 16; i++)
		L3[i] = Lanes[i + 48];
	for (int i = 0; i < 16; i++)
		L4[i] = Lanes[i + 64];
	for (int i = 0; i < 16; i++)
		L5[i] = Lanes[i + 80];
	for (int i = 0; i < 16; i++)
		L6[i] = Lanes[i + 96];
	for (int i = 0; i < 16; i++)
		L7[i] = Lanes[i + 112];

	_L7 = L7;
	_L6 = xor_message(L6, MessageBlock, 0x0f);
	_L5 = L5;
	_L4 = xor_message(L4, MessageBlock, 0x00);
	_L4 = aes(_L4);
	_L4 = xor_normal(_L4, L1);
	_L3 = L3;
	_L2 = xor_message(L2, MessageBlock, 0x01);
	_L1 = xor_message(L1, MessageBlock, 0x10);
	_L0 = aes(L0);
	_L0 = xor_normal(_L0, L4);
	for (int i = 0; i < 16; i++)
		result[i] = _L0[i];
	for (int i = 0; i < 16; i++)
		result[i + 16] = _L1[i];
	for (int i = 0; i < 16; i++)
		result[i + 32] = _L2[i];
	for (int i = 0; i < 16; i++)
		result[i + 48] = _L3[i];
	for (int i = 0; i < 16; i++)
		result[i + 64] = _L4[i];
	for (int i = 0; i < 16; i++)
		result[i + 80] = _L5[i];
	for (int i = 0; i < 16; i++)
		result[i + 96] = _L6[i];
	for (int i = 0; i < 16; i++)
		result[i + 112] = _L7[i];

	return result;
}
uint8_t* IvAbsorptionFunction(uint8_t* MessageBlock, uint8_t* Lanes)
{
	uint8_t* L0 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L1 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L2 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L3 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L4 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L5 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L6 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L7 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L0 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L1 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L2 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L3 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L4 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L5 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L6 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L7 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* result = (uint8_t*)malloc(128 * sizeof(uint8_t));
	for (int i = 0; i < 16; i++)
		_L0[i] = Lanes[i];
	for (int i = 0; i < 16; i++)
		_L1[i] = Lanes[i + 16];
	for (int i = 0; i < 16; i++)
		_L2[i] = Lanes[i + 32];
	for (int i = 0; i < 16; i++)
		_L3[i] = Lanes[i + 48];
	for (int i = 0; i < 16; i++)
		_L4[i] = Lanes[i + 64];
	for (int i = 0; i < 16; i++)
		_L5[i] = Lanes[i + 80];
	for (int i = 0; i < 16; i++)
		_L6[i] = Lanes[i + 96];
	for (int i = 0; i < 16; i++)
		_L7[i] = Lanes[i + 112];
	L7 = _L7;
	L5 = _L5;
	L6 = xor_message(_L6, MessageBlock, 0x0f);
	L3 = _L3;
	L2 = xor_message(_L2, MessageBlock, 0x01);
	L1 = xor_message(_L1, MessageBlock, 0x10);
	L4 = xor_normal(_L4, L1);
	L4 = iv_aes(L4);
	L4 = xor_message(L4, MessageBlock, 0x00);
	L0 = xor_normal(_L0, L4);
	L0 = iv_aes(L0);
	for (int i = 0; i < 16; i++)
		result[i] = L0[i];
	for (int i = 0; i < 16; i++)
		result[i + 16] = L1[i];
	for (int i = 0; i < 16; i++)
		result[i + 32] = L2[i];
	for (int i = 0; i < 16; i++)
		result[i + 48] = L3[i];
	for (int i = 0; i < 16; i++)
		result[i + 64] = L4[i];
	for (int i = 0; i < 16; i++)
		result[i + 80] = L5[i];
	for (int i = 0; i < 16; i++)
		result[i + 96] = L6[i];
	for (int i = 0; i < 16; i++)
		result[i + 112] = L7[i];

	return result;
}
uint8_t* Finalization12(uint8_t* Lanes)
{
	uint8_t* L0 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L1 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L2 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L3 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L4 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L5 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L6 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L7 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L0 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L1 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L2 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L3 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L4 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L5 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L6 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L7 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* temp = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* result = (uint8_t*)malloc(128 * sizeof(uint8_t));
	for (int i = 0; i < 16; i++)
		L0[i] = Lanes[i];
	for (int i = 0; i < 16; i++)
		L1[i] = Lanes[i + 16];
	for (int i = 0; i < 16; i++)
		L2[i] = Lanes[i + 32];
	for (int i = 0; i < 16; i++)
		L3[i] = Lanes[i + 48];
	for (int i = 0; i < 16; i++)
		L4[i] = Lanes[i + 64];
	for (int i = 0; i < 16; i++)
		L5[i] = Lanes[i + 80];
	for (int i = 0; i < 16; i++)
		L6[i] = Lanes[i + 96];
	for (int i = 0; i < 16; i++)
		L7[i] = Lanes[i + 112];
	_L7 = L7;
	_L6 = L6;
	_L3 = L3;
	_L2 = L2;
	_L5 = xor_normal(L5, L6);
	_L4 = xor_normal(L4, L6);
	_L4 = aes(_L4);
	temp = xor_normal(L1, L5);
	_L4 = xor_normal(temp, _L4);
	_L1 = xor_normal(L1, L5);
	_L1 = xor_normal(_L1, L2);
	_L0 = aes(L0);
	_L0 = xor_normal(_L0, L4);
	for (int i = 0; i < 16; i++)
		result[i] = _L0[i];
	for (int i = 0; i < 16; i++)
		result[i + 16] = _L1[i];
	for (int i = 0; i < 16; i++)
		result[i + 32] = _L2[i];
	for (int i = 0; i < 16; i++)
		result[i + 48] = _L3[i];
	for (int i = 0; i < 16; i++)
		result[i + 64] = _L4[i];
	for (int i = 0; i < 16; i++)
		result[i + 80] = _L5[i];
	for (int i = 0; i < 16; i++)
		result[i + 96] = _L6[i];
	for (int i = 0; i < 16; i++)
		result[i + 112] = _L7[i];
	return result;
}
uint8_t* IvFinalization12(uint8_t* Lanes)
{
	uint8_t* L0 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L1 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L2 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L3 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L4 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L5 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L6 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L7 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L0 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L1 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L2 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L3 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L4 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L5 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L6 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L7 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* result = (uint8_t*)malloc(128 * sizeof(uint8_t));
	for (int i = 0; i < 16; i++)
		_L0[i] = Lanes[i];
	for (int i = 0; i < 16; i++)
		_L1[i] = Lanes[i + 16];
	for (int i = 0; i < 16; i++)
		_L2[i] = Lanes[i + 32];
	for (int i = 0; i < 16; i++)
		_L3[i] = Lanes[i + 48];
	for (int i = 0; i < 16; i++)
		_L4[i] = Lanes[i + 64];
	for (int i = 0; i < 16; i++)
		_L5[i] = Lanes[i + 80];
	for (int i = 0; i < 16; i++)
		_L6[i] = Lanes[i + 96];
	for (int i = 0; i < 16; i++)
		_L7[i] = Lanes[i + 112];
	L7 = _L7;
	L6 = _L6;
	L5 = xor_normal(_L5, _L6);
	L3 = _L3;
	L2 = _L2;
	L1 = xor_normal(_L1, _L2);
	L1 = xor_normal(L1, L5);
	L4 = xor_normal(L1, L5);
	L4 = xor_normal(L4, _L4);
	L4 = iv_aes(L4);
	L4 = xor_normal(L4, L6);
	L0 = xor_normal(_L0, L4);
	L0 = iv_aes(L0);
	for (int i = 0; i < 16; i++)
		result[i] = L0[i];
	for (int i = 0; i < 16; i++)
		result[i + 16] = L1[i];
	for (int i = 0; i < 16; i++)
		result[i + 32] = L2[i];
	for (int i = 0; i < 16; i++)
		result[i + 48] = L3[i];
	for (int i = 0; i < 16; i++)
		result[i + 64] = L4[i];
	for (int i = 0; i < 16; i++)
		result[i + 80] = L5[i];
	for (int i = 0; i < 16; i++)
		result[i + 96] = L6[i];
	for (int i = 0; i < 16; i++)
		result[i + 112] = L7[i];
	return result;
}
uint8_t* Finalization_last(uint8_t* Lanes)
{
	uint8_t* L0 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L1 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L2 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L3 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L4 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L5 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L6 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L7 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L0 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L1 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L2 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L3 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L4 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L5 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L6 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L7 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* result = (uint8_t*)malloc(128 * sizeof(uint8_t));
	for (int i = 0; i < 16; i++)
		L0[i] = Lanes[i];
	for (int i = 0; i < 16; i++)
		L1[i] = Lanes[i + 16];
	for (int i = 0; i < 16; i++)
		L2[i] = Lanes[i + 32];
	for (int i = 0; i < 16; i++)
		L3[i] = Lanes[i + 48];
	for (int i = 0; i < 16; i++)
		L4[i] = Lanes[i + 64];
	for (int i = 0; i < 16; i++)
		L5[i] = Lanes[i + 80];
	for (int i = 0; i < 16; i++)
		L6[i] = Lanes[i + 96];
	for (int i = 0; i < 16; i++)
		L7[i] = Lanes[i + 112];
	_L7 = L7;
	_L6 = L6;
	_L5 = xor_normal(L5, L7);
	_L4 = xor_normal(L4, L6);
	_L4 = xor_normal(_L4, _L5);
	_L3 = L3;
	_L2 = L2;
	_L1 = L1;
	_L0 = xor_normal(L0, L2);
	_L0 = xor_normal(_L0, L1);
	_L0 = xor_normal(_L0, _L4);
	for (int i = 0; i < 16; i++)
		result[i] = _L0[i];
	for (int i = 0; i < 16; i++)
		result[i + 16] = _L1[i];
	for (int i = 0; i < 16; i++)
		result[i + 32] = _L2[i];
	for (int i = 0; i < 16; i++)
		result[i + 48] = _L3[i];
	for (int i = 0; i < 16; i++)
		result[i + 64] = _L4[i];
	for (int i = 0; i < 16; i++)
		result[i + 80] = _L5[i];
	for (int i = 0; i < 16; i++)
		result[i + 96] = _L6[i];
	for (int i = 0; i < 16; i++)
		result[i + 112] = _L7[i];
	return result;
}
uint8_t* IvFinalization_last(uint8_t* Lanes)
{
	uint8_t* L0 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L1 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L2 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L3 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L4 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L5 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L6 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L7 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L0 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L1 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L2 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L3 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L4 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L5 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L6 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L7 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* result = (uint8_t*)malloc(128 * sizeof(uint8_t));
	for (int i = 0; i < 16; i++)
		_L0[i] = Lanes[i];
	for (int i = 0; i < 16; i++)
		_L1[i] = Lanes[i + 16];
	for (int i = 0; i < 16; i++)
		_L2[i] = Lanes[i + 32];
	for (int i = 0; i < 16; i++)
		_L3[i] = Lanes[i + 48];
	for (int i = 0; i < 16; i++)
		_L4[i] = Lanes[i + 64];
	for (int i = 0; i < 16; i++)
		_L5[i] = Lanes[i + 80];
	for (int i = 0; i < 16; i++)
		_L6[i] = Lanes[i + 96];
	for (int i = 0; i < 16; i++)
		_L7[i] = Lanes[i + 112];
	L7 = _L7;
	L6 = _L6;
	L5 = xor_normal(_L5, _L7);
	L3 = _L3;
	L2 = _L2;
	L1 = _L1;
	L4 = xor_normal(_L5, _L4);
	L4 = xor_normal(L4, _L6);
	L0 = xor_normal(_L0, _L4);
	L0 = xor_normal(L0, _L1);
	L0 = xor_normal(L0, _L2);
	for (int i = 0; i < 16; i++)
		result[i] = L0[i];
	for (int i = 0; i < 16; i++)
		result[i + 16] = L1[i];
	for (int i = 0; i < 16; i++)
		result[i + 32] = L2[i];
	for (int i = 0; i < 16; i++)
		result[i + 48] = L3[i];
	for (int i = 0; i < 16; i++)
		result[i + 64] = L4[i];
	for (int i = 0; i < 16; i++)
		result[i + 80] = L5[i];
	for (int i = 0; i < 16; i++)
		result[i + 96] = L6[i];
	for (int i = 0; i < 16; i++)
		result[i + 112] = L7[i];
	return result;
}
uint8_t* Shift_Left_One(uint8_t* Lanes)
{
	uint8_t* L0 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L1 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L2 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L3 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L4 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L5 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L6 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L7 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L0 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L1 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L2 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L3 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L4 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L5 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L6 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L7 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* result = (uint8_t*)malloc(128 * sizeof(uint8_t));
	for (int i = 0; i < 16; i++)
		L0[i] = Lanes[i];
	for (int i = 0; i < 16; i++)
		L1[i] = Lanes[i + 16];
	for (int i = 0; i < 16; i++)
		L2[i] = Lanes[i + 32];
	for (int i = 0; i < 16; i++)
		L3[i] = Lanes[i + 48];
	for (int i = 0; i < 16; i++)
		L4[i] = Lanes[i + 64];
	for (int i = 0; i < 16; i++)
		L5[i] = Lanes[i + 80];
	for (int i = 0; i < 16; i++)
		L6[i] = Lanes[i + 96];
	for (int i = 0; i < 16; i++)
		L7[i] = Lanes[i + 112];
	_L0 = L1;
	_L1 = L2;
	_L2 = L3;
	_L3 = L4;
	_L4 = L5;
	_L5 = L6;
	_L6 = L7;
	_L7 = L0;
	for (int i = 0; i < 16; i++)
		result[i] = _L0[i];
	for (int i = 0; i < 16; i++)
		result[i + 16] = _L1[i];
	for (int i = 0; i < 16; i++)
		result[i + 32] = _L2[i];
	for (int i = 0; i < 16; i++)
		result[i + 48] = _L3[i];
	for (int i = 0; i < 16; i++)
		result[i + 64] = _L4[i];
	for (int i = 0; i < 16; i++)
		result[i + 80] = _L5[i];
	for (int i = 0; i < 16; i++)
		result[i + 96] = _L6[i];
	for (int i = 0; i < 16; i++)
		result[i + 112] = _L7[i];
	return result;
}
uint8_t* IvShift_left_One(uint8_t* Lanes)
{
	uint8_t* L0 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L1 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L2 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L3 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L4 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L5 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L6 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* L7 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L0 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L1 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L2 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L3 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L4 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L5 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L6 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* _L7 = (uint8_t*)malloc(16 * sizeof(uint8_t));
	uint8_t* result = (uint8_t*)malloc(128 * sizeof(uint8_t));
	for (int i = 0; i < 16; i++)
		_L0[i] = Lanes[i];
	for (int i = 0; i < 16; i++)
		_L1[i] = Lanes[i + 16];
	for (int i = 0; i < 16; i++)
		_L2[i] = Lanes[i + 32];
	for (int i = 0; i < 16; i++)
		_L3[i] = Lanes[i + 48];
	for (int i = 0; i < 16; i++)
		_L4[i] = Lanes[i + 64];
	for (int i = 0; i < 16; i++)
		_L5[i] = Lanes[i + 80];
	for (int i = 0; i < 16; i++)
		_L6[i] = Lanes[i + 96];
	for (int i = 0; i < 16; i++)
		_L7[i] = Lanes[i + 112];
	L1 = _L0;
	L2 = _L1;
	L3 = _L2;
	L4 = _L3;
	L5 = _L4;
	L6 = _L5;
	L7 = _L6;
	L0 = _L7;
	for (int i = 0; i < 16; i++)
		result[i] = L0[i];
	for (int i = 0; i < 16; i++)
		result[i + 16] = L1[i];
	for (int i = 0; i < 16; i++)
		result[i + 32] = L2[i];
	for (int i = 0; i < 16; i++)
		result[i + 48] = L3[i];
	for (int i = 0; i < 16; i++)
		result[i + 64] = L4[i];
	for (int i = 0; i < 16; i++)
		result[i + 80] = L5[i];
	for (int i = 0; i < 16; i++)
		result[i + 96] = L6[i];
	for (int i = 0; i < 16; i++)
		result[i + 112] = L7[i];
	return result;
}
void print128(uint8_t* input)
{
	for (int i = 0; i < 128; i++)
	{
		printf("0x%x, ", input[i]);
		if (i > 0 && (i + 1) % 16 == 0)
			printf("\n");
	}
	printf("\n");
}
uint8_t* IvMeowHash()
{
	uint8_t* temp = (uint8_t*)malloc(128 * sizeof(uint8_t));
	for (int i = 0; i < 16; i++)
		temp[i] = HashOutput[i];
	for (int i = 0; i < 16; i++)
		temp[i + 16] = Lane1[i];
	for (int i = 0; i < 16; i++)
		temp[i + 32] = Lane2[i];
	for (int i = 0; i < 16; i++)
		temp[i + 48] = Lane3[i];
	for (int i = 0; i < 16; i++)
		temp[i + 64] = Lane4[i];
	for (int i = 0; i < 16; i++)
		temp[i + 80] = Lane5[i];
	for (int i = 0; i < 16; i++)
		temp[i + 96] = Lane6[i];
	for (int i = 0; i < 16; i++)
		temp[i + 112] = Lane7[i];
	print128(temp);
	temp = IvFinalization_last(temp);
	print128(temp);
	for (int i = 0; i < 12; i++)
	{
		temp = IvFinalization12(temp);
		temp = IvShift_left_One(temp);
		print128(temp);
	}
	temp = IvAbsorptionFunction(LengthBlock, temp);
	print128(temp);
	temp = IvShift_left_One(temp);
	temp = IvAbsorptionFunction(HashInput, temp);
	print128(temp);
	return temp;

}
uint8_t* MeowHash()
{
	print128(InitKey);
	uint8_t* temp = (uint8_t*)malloc(128 * sizeof(uint8_t));
	temp = AbsorptionFunction(HashInput, InitKey);
	temp = Shift_Left_One(temp);
	print128(temp);
	temp = AbsorptionFunction(LengthBlock, temp);
	temp = Shift_Left_One(temp);
	print128(temp);
	for (int i = 0; i < 12; i++)
	{
		temp = Finalization12(temp);
		if (i == 11)
			break;
		temp = Shift_Left_One(temp);
	}
	temp = Finalization_last(temp);
	print128(temp);
	return temp;
}