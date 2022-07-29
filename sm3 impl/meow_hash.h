#pragma once
using namespace std;
#include<iostream>
#include<cstdio>
#include<bitset>
#include<chrono>
#include<random>
#include<cstdlib>
using std::string;
using std::random_device;
using std::default_random_engine;
struct normal_node
{
	normal_node* left_child;
	normal_node* right_child;
	string sm3_input;
};
uint32_t IV[8] = { 0x7380166f,0x4914b2b9,0x172442d7,0xda8a0600,0xa96f30bc,0x163138aa,0xe38dee4d,0xb0fb0e4e };//常量IV
uint32_t length_extension_example_known_hash_result[8] = { 0x66C7F0F4 ,0x62EEEDD9 ,0xD1F2D46B,0xDC10E4E2,0x4167C487,0x5CF2F7A2,0x297DA02B,0x8F4BA8E0 };
uint32_t Tj015 = 0x79cc4519;//常量Tj 0-15的取值
uint32_t Tj1663 = 0x7a879d8a;//常量Tj 16-63的取值
uint32_t SM3_hash_result[8];
uint32_t SM3_length_extension_attack_result[8];
unsigned long long MODNUM = 4294967296;//2的32次方
unsigned int after_padding_length = 0;//填充后消息长度，单位是字节
#define FFj015(x,y,z) x^y^z//FFj函数0-15
#define FFj1663(x,y,z) (x&y)|(x&z)|(y&z)//FFj函数16-63
#define GGj015(x,y,z) x^y^z//GGj函数0-15
#define GGj1663(x,y,z) (x&y)|(~x&z)//GGj函数1663
#define P0(x) x^((x<<9)|(x>>23))^((x<<17)|(x>>15))//P0函数
#define P1(x) x^((x<<15)|(x>>17))^((x<<23)|(x>>9))//P1函数
#define MERAGE4(one,two,three,four)	(((uint32_t)one << 24) | ((uint32_t)two << 16) | ((uint16_t)three << 8) | four)//四个uint8合并成一个uint32
#define round_shift_left(x,n) x<<n|x>>32-n//向左循环移位
#define CHECK_PASS 1
#define CHECK_FAIL 0
#define RESULT_FOUND 1
#define RESULT_NOT_FOUND 0
