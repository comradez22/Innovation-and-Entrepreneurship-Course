extern "C"
{



	int SM4_KeyInit(uint8_t* key, SM4_Key* SM4_Round_Key) {

		uint32_t KS[4];
		uint32_t tmp;
		uint8_t* tmp_ptr8 = (uint8_t*)&tmp;
		*SM4_Round_Key = (uint32_t*)malloc(32 * sizeof(uint32_t));
		// 初始化密钥
		for (int i = 0; i < 4; i++) 
		{
			int j = 4 * i;
			KS[i] = (key[j] << 24) | (key[j + 1] << 16) | (key[j + 2] << 8) |
				(key[j + 3]);
			KS[i] = KS[i] ^ FK[i];
		}
		// 32轮变换
		for (int i = 0; i < 32; i++) {

			tmp = KS[1] ^ KS[2] ^ KS[3] ^ CKI[i];
			
			// 线性变换
			(*SM4_Round_Key)[i] = KS[0] ^ tmp ^ RoundRoll(tmp, 13) ^ RoundRoll(tmp, 23);
			// 移位
			KS[0] = KS[1];
			KS[1] = KS[2];
			KS[2] = KS[3];
			KS[3] = (uint32_t)(*SM4_Round_Key+i);
		}
		return 1;
	}
	void SM4_Simd(uint8_t* plaintext, uint8_t* ciphertext, uint32_t* sm4_key)
	{
		__m256i X[4], Temp[4], MaskCode;
		MaskCode = _mm256_set1_epi32(0xFF);
		Temp[0] = _mm256_loadu_si256((const __m256i*)plaintext + 0);
		Temp[1] = _mm256_loadu_si256((const __m256i*)plaintext + 1);
		Temp[2] = _mm256_loadu_si256((const __m256i*)plaintext + 2);
		Temp[3] = _mm256_loadu_si256((const __m256i*)plaintext + 3);
		X[0] = _64_32_32_LO_LO_LO(Temp[0], Temp[1], Temp[2], Temp[3]);
		X[1] = _64_32_32_HI_LO_LO(Temp[0], Temp[1], Temp[2], Temp[3]);
		X[2] = _64_32_32_LO_HI_HI(Temp[0], Temp[1], Temp[2], Temp[3]);
		X[3] = _64_32_32_HI_HI_HI(Temp[0], Temp[1], Temp[2], Temp[3]);
		__m256i vindex = _mm256_setr_epi8(3, 2, 1, 0, 7, 6, 5, 4, 11, 10, 9, 8, 15, 14, 13, 12, 3, 2, 1, 0, 7, 6, 5, 4, 11, 10, 9, 8, 15, 14, 13, 12);
		X[0] = _mm256_shuffle_epi8(X[0], vindex);
		X[1] = _mm256_shuffle_epi8(X[1], vindex);
		X[2] = _mm256_shuffle_epi8(X[2], vindex);
		X[3] = _mm256_shuffle_epi8(X[3], vindex);
		for (int i = 0; i < 32; i++) 
		{
			__m256i k =_mm256_set1_epi32( sm4_key[i]);
			Temp[0] = _mm256_xor_si256(_mm256_xor_si256(X[1], X[2]), _mm256_xor_si256(X[3], k));//T-functionInput
			Temp[1] = _mm256_xor_si256(X[0], _mm256_i32gather_epi32((const int*)Table0, _mm256_and_si256(Temp[0], MaskCode), 4));
			Temp[0] = _mm256_srli_epi32(Temp[0], 8);

			Temp[1] = _mm256_xor_si256(Temp[1], _mm256_i32gather_epi32((const int*)Table1, _mm256_and_si256(Temp[0], MaskCode), 4));
			Temp[0] = _mm256_srli_epi32(Temp[0], 8);

			Temp[1] = _mm256_xor_si256(Temp[1], _mm256_i32gather_epi32((const int*)Table2, _mm256_and_si256(Temp[0], MaskCode), 4));
			Temp[0] = _mm256_srli_epi32(Temp[0], 8);

			Temp[1] = _mm256_xor_si256(Temp[1], _mm256_i32gather_epi32((const int*)Table3, _mm256_and_si256(Temp[0], MaskCode), 4));

			X[0] = X[1];
			X[1] = X[2];
			X[2] = X[3];
			X[3] = Temp[1];
		}
		X[0] = _mm256_shuffle_epi8(X[0], vindex);
		X[1] = _mm256_shuffle_epi8(X[1], vindex);
		X[2] = _mm256_shuffle_epi8(X[2], vindex);
		X[3] = _mm256_shuffle_epi8(X[3], vindex);
		_mm256_storeu_si256((__m256i*)ciphertext + 0,_64_32_32_LO_LO_LO(X[3], X[2], X[1], X[0]));
		_mm256_storeu_si256((__m256i*)ciphertext + 1,_64_32_32_HI_LO_LO(X[3], X[2], X[1], X[0]));
		_mm256_storeu_si256((__m256i*)ciphertext + 2,_64_32_32_LO_HI_HI(X[3], X[2], X[1], X[0]));
		_mm256_storeu_si256((__m256i*)ciphertext + 3,_64_32_32_HI_HI_HI(X[3], X[2], X[1], X[0]));
	}
}


int main()
{
	unsigned char key[16 * 8] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab,
								 0xcd, 0xef, 0xfe, 0xdc, 0xba, 0x98,
								 0x76, 0x54, 0x32, 0x10 };
	// 01 23 45 67 89 ab cd ef fe dc ba 98 76 54 32 10
	// 00 00 ... 00
	unsigned char in[16 * 8] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
								0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
								0x51, 0xa3, 0xb5, 0x97, 0x80, 0xfb, 0x6d, 0xea,
								0xbe, 0xfc, 0x32, 0x44, 0xb6, 0xd4, 0x1f, 0x1c ,
								0x34, 0xf3, 0xb5, 0x6a, 0x31, 0xcd, 0xd2, 0xa3,
								0xf4, 0xda, 0x4f, 0x91, 0x29 ,0x35, 0x31, 0xac ,
								0xfa, 0x45, 0x87, 0xf7, 0x81, 0xb4, 0x3d, 0x5f,
								0x23, 0xf5, 0x2a, 0x91, 0x7f, 0x76, 0x12, 0xf4,
								0x18, 0x35, 0x5f, 0x1a, 0x4f, 0x3a, 0xdc, 0xfe,
								0x5a, 0x3d, 0x1f, 0x35, 0x27, 0x56, 0x88, 0x38,
								0x0a, 0xf3, 0x42, 0xf7, 0x6c, 0x2c, 0x66, 0x6f,
								0x1c, 0x2b, 0x62, 0x6f, 0x19, 0x1a, 0x44, 0xfc ,
								0x1f, 0x5f, 0x22, 0x33, 0xcd, 0x1b, 0xc2, 0x8f,
								0xf3, 0x1c, 0xab, 0x58, 0x38, 0x73, 0xa2, 0x1f ,
								0xb1, 0x45, 0x73, 0xad, 0x80, 0xfb, 0x1f, 0x36,
								0xf1, 0xbc, 0x7a, 0x30, 0x22, 0x5f, 0x1d, 0x3f };
	//1011011111010101010101011101110010100101010011000101110001111101 0100111001001101010001001101110011000101110111011010100101101011 B7D555DCA54C5C7D4E4D44DCC5DDA96B
	//1100011111010100111000011011100010101001111100111101110001111101 1010010011010101000101011101011111011110111101010100010011001100 c7d4e1b8a9f3dc7da4d515d7def544cc
	bitset<128> re("11010110100101011011101110100011001110110010001010110010011100101011111000111010001100101010010100111011101010101010101111101101");
	bitset<128> ke("00110011001000101010111101111011111010111010100010101011001001011011111000011011110011111001010100011101100001110010101111100011");
	bitset<32> *keys = gen_round_key(ke);
	double time = 0;
	//bitset<128> result = SM4Encrypt_round_vision(re, ke);
	//cout << result;
	
	for (int i = 0; i < 10000; i++)
	{
		auto startTime = std::chrono::system_clock::now();
		bitset <128>ci = SM4Encrypt_round_vision(re, ke);
		auto endTime = std::chrono::system_clock::now();
		time += std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
	}
	cout << "normal time:" << time / 10000 << endl;
	time = 0;
	for (int i = 0; i < 10000; i++)
	{
		auto startTime = std::chrono::system_clock::now();
		bitset <128>ci = SM4Encrypt_table_vision(re, ke);
		auto endTime = std::chrono::system_clock::now();
		time += std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
	}
	cout << "table time:" << time / 10000 << endl;
	time = 0;
	for (int i = 0; i < 10000; i++)
	{
		auto startTime = std::chrono::system_clock::now();
		bitset <128>ci = SM4Encrypt_table_one_vision(re, ke, keys);
		auto endTime = std::chrono::system_clock::now();
		time += std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
	}
	cout << "one table time:" << time / 10000 << endl;
	
	/*
	SM4_Key sm4_key;
	int success = SM4_KeyInit(key, &sm4_key);
	for (int i = 0; i < 32; i++)
	{
		cout << sm4_key[i] << endl;
	}
	for (int i = 0; i < 100000; i++)
	{
		auto startTime = std::chrono::system_clock::now();
		SM4_Simd(in, in, sm4_key);
		auto endTime = std::chrono::system_clock::now();
		time += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
	}
	cout << "one table time:" << time / 100000 << endl;
	*/
	time = 0;
	bitset<32> ltest("11000111110101001110000111010100");
	
	for (int i = 0; i < 10000000; i++)
	{
		auto startTime = std::chrono::system_clock::now();
		bitset<32> ltest_result = get_lchange_result(ltest);
		auto endTime = std::chrono::system_clock::now();
		time += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
	}
	cout << "l置换 nano:"<<time / 10000000 << endl;
	bitset<8> stest("11110001");
	time = 0;
	for (int i = 0; i < 10000000; i++)
	{
		auto startTime = std::chrono::system_clock::now();
		bitset<8> stest_result = get_sbox_result(stest);
		auto endTime = std::chrono::system_clock::now();
		time += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
	}
	cout << "sbox nano:"<<time / 10000000 << endl;
	for (int i = 0; i < 10000; i++)
	{
		
		bitset <128>ci = SM4Encrypt_round_vision(re, ke);
		
		
	}
	cout << "32轮加密,microsecond:" << supertime / 10000 << endl;
	cout << "32round Tfunction:" << timesuper / 10000 << endl;
	time = 0;
	for (int i = 0; i < 10000; i++)
	{
		auto startTime = std::chrono::system_clock::now();
		bitset <32>* ci = gen_round_key(ke);
		auto endTime = std::chrono::system_clock::now();
		time += std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
	}
	cout << "轮密钥" << time / 10000 << endl;
}

