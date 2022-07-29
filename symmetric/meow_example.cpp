#include<iostream>

#include "meow_hash.h"
using namespace std;

int main()
{
	uint8_t test[16] = { 0xc9,0xe5,0xfd,0x2b,0x7a,0xf2,0x78,0x6e,0x63,0x9c,0x26,0x67,0xb0,0xa7,0x82,0xe5 };
	uint8_t test1[32] = { 0xc9,0xe5,0xfd,0x2b,0x7a,0xf2,0x78,0x6e,0x63,0x9c,0x26,0x67,0xb0,0xa7,0x82,0xe5 ,
						0xc9,0xe5,0xfd,0x2b,0x7a,0xf2,0x78,0x6e,0x63,0x9c,0x26,0x67,0xb0,0xa7,0x82,0xe5 };
	uint8_t test2[128];
	uint8_t* res;
	/*for (int i = 0; i < 128; i++)
	{
		test2[i] = rand() % 0xff;
	}
	printf("test2:\n");
	for (int i = 0; i < 128; i++)
	{
		printf("0x%x, ", test2[i]);
		if (i > 0 && (i + 1) % 16 == 0)
			printf("\n");
	}
	printf("\n");*/

	/*res = Finalization_last(test2);
	printf("Finalization_last:\n");
	for (int i = 0; i < 128; i++)
	{
		printf("%x ", res[i]);
		if (i > 0 && (i + 1) % 16 == 0)
			printf("\n");
	}
	printf("\n");
	res = IvFinalization_last(res);
	printf("Inverse Finalization last:\n");
	for (int i = 0; i < 128; i++)
	{
		printf("%x ", res[i]);
		if (i > 0 && (i + 1) % 16 == 0)
			printf("\n");
	}
	res = Shift_Left_One(res);
	printf("shift:\n\n");
	printf("\n");
	for (int i = 0; i < 128; i++)
	{
		printf("%x ", res[i]);
		if (i > 0 && (i + 1) % 16 == 0)
			printf("\n");
	}
	res = IvShift_left_One(res);
	printf("\n");
	printf("Ivshift:\n\n");
	for (int i = 0; i < 128; i++)
	{
		printf("%x ", res[i]);
		if (i > 0 && (i + 1) % 16 == 0)
			printf("\n");
	}*/
	//res=IvMeowHash();
	res = MeowHash();
	uint8_t* result = (uint8_t*)malloc(16 * sizeof(uint8_t));
	/*for (int i = 0; i < 16; i++)
	{
		result[i] = res[i];
		printf("%x ", result[i]);
	}*/
	print128(res);
}
