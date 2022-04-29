const unsigned char SBox[256] = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

const unsigned char roundConstant[10] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };

typedef unsigned int word;
typedef unsigned char byte;

void btow(byte A[4], word B[1]) {
	B[0] = (A[0] << 24) + (A[1] << 16) + (A[2] << 8) + A[3];
}

void wtob(byte A[4], word B) {
	A[0] = (B >> 24) & 0XFF;
	A[1] = (B >> 16) & 0XFF;
	A[2] = (B >> 8) & 0XFF;
	A[3] = B & 0XFF;
}


void AddRoundKey(word state[4], byte roundKey[16])
{
	word W_roundKey[4];
	for (int i = 0; i < 4; i++) {
		btow(&roundKey[4 * i], &W_roundKey[i]);
		state[i] ^= W_roundKey[i];
	}


	/*for (int i = 0; i < 16; i++) {
		state[i] ^= roundKey[i];
	}*/
}

void SubBytes(unsigned char state[16])
{
	for (int i = 0; i < 16; i++) {
		state[i] = SBox[state[i]];
	}
}

void ShiftRows(word state[4])
{
	byte k[16];
	for (int i = 0; i < 4; i++) {
		wtob(&k[i * 4], state[i]);
	}

	byte tmp[16];
	tmp[0] = k[0];
	tmp[1] = k[5];
	tmp[2] = k[10];
	tmp[3] = k[15];

	tmp[4] = k[4];
	tmp[5] = k[9];
	tmp[6] = k[14];
	tmp[7] = k[3];

	tmp[8] = k[8];
	tmp[9] = k[13];
	tmp[10] = k[2];
	tmp[11] = k[7];

	tmp[12] = k[12];
	tmp[13] = k[1];
	tmp[14] = k[6];
	tmp[15] = k[11];

	for (int i = 0; i < 4; i++) {
		btow(&tmp[4 * i], &state[i]);
	}

	/*unsigned char k[16];

	k[0] = state[0];
	k[1] = state[5];
	k[2] = state[10];
	k[3] = state[15];

	k[4] = state[4];
	k[5] = state[9];
	k[6] = state[14];
	k[7] = state[3];

	k[8] = state[8];
	k[9] = state[13];
	k[10] = state[2];
	k[11] = state[7];

	k[12] = state[12];
	k[13] = state[1];
	k[14] = state[6];
	k[15] = state[11];

	for (int i = 0; i < 16; i++) {
		state[i] = k[i];
	}*/
}

//void MixColumns(unsigned char state[16])
//{
//	unsigned char k[4];
//
//	unsigned char m[16] = { 0x02, 0x03, 0x01, 0x01,
//					0x01, 0x02, 0x03, 0x01,
//					0x01, 0x01, 0x02, 0x03,
//					0x03, 0x01, 0x01, 0x02 };
//
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 4; j++) {
//			k[j] = mix(state[i * 4 + 0], m[j * 4 + 0]);
//			k[j] ^= mix(state[i * 4 + 1], m[j * 4 + 1]);
//			k[j] ^= mix(state[i * 4 + 2], m[j * 4 + 2]);
//			k[j] ^= mix(state[i * 4 + 3], m[j * 4 + 3]);
//		}
//
//		state[i * 4 + 0] = k[0];
//		state[i * 4 + 1] = k[1];
//		state[i * 4 + 2] = k[2];
//		state[i * 4 + 3] = k[3];
//	}
//}
//
//int mix(unsigned char x, unsigned char y)
//{
//	unsigned char a = 0, i, j;
//
//	for (i = 0; i < 8; i++) {
//		if (y & 0x01) {
//			a ^= x;
//		}
//
//		j = x & 0x80;
//		x <<= 0x01;
//
//		if (j) {
//			x ^= 0x1B;
//		}
//
//		y >>= 0x01;
//	}
//	return a;
//}

byte t2(byte x) {
	x = (x << 1) ^ ((x >> 7) ^ 0x1b);
	return x;
}

byte t3(byte x) {
	x = t2(x) ^ x;
	return x;
}

word Te0(byte x) {
	word w;
	
	w = (t2(SBox[x]) << 24) + (SBox[x] << 16) + (SBox[x] << 8) + t3(SBox[x]);

	return w;
}

word Te1(byte x) {
	word w;

	w = (t3(SBox[x]) << 24) + (t2(SBox[x]) << 16) + (SBox[x] << 8) + SBox[x];

	return w;
}

word Te2(byte x) {
	word w;

	w = ((SBox[x] << 24) + (t3(SBox[x]) << 16) + (t2(SBox[x]) << 8) + SBox[x]);

	return w;
}

word Te3(byte x) {
	word w;

	w = ((SBox[x] << 24) + (SBox[x] << 16) + (t3(SBox[x]) << 8) + t2(SBox[x]));

	return w;
}



void subMix(word state[4]) {
	for (int i = 0; i < 4; i++) {
		state[i] = Te0((state[i] >> 24) & 0xff);
		state[i] = state[i] ^ Te1((state[i] >> 16) & 0xff);
		state[i] = state[i] ^ Te2((state[i] >> 8) & 0xff);
		state[i] = state[i] ^ Te3(state[i] & 0xff);
	}
}



void KeyExpansion(unsigned char roundKey[11][16], const unsigned char masterKey[16]) //AES - 128 KeyExpansion ����
{
	//constant - ���
	for (int i = 0; i < 16; i++) {
		roundKey[0][i] = masterKey[i];
	}

	unsigned char b[4] = { 0, }, shift_b[4] = { 0, };

	b[0] = masterKey[12];
	b[1] = masterKey[13];
	b[2] = masterKey[14];
	b[3] = masterKey[15];

	for (int i = 0; i < 10; i++) {
		shift_b[0] = b[1];
		shift_b[1] = b[2];
		shift_b[2] = b[3];
		shift_b[3] = b[0];

		for (int k = 0; k < 4; k++) {
			b[k] = SBox[shift_b[k]];
		}

		b[0] ^= roundConstant[i];

		for (int j = 0; j < 13; j += 4) {
			b[0] ^= roundKey[i][j];
			b[1] ^= roundKey[i][j + 1];
			b[2] ^= roundKey[i][j + 2];
			b[3] ^= roundKey[i][j + 3];

			roundKey[i + 1][j] = b[0];
			roundKey[i + 1][j + 1] = b[1];
			roundKey[i + 1][j + 2] = b[2];
			roundKey[i + 1][j + 3] = b[3];
		}
	}

}

#include <stdio.h>
void AES(word plainText[], unsigned char key[], word cipher[]) {

	unsigned char roundKey[11][16] = { 0, };
	byte state[16] = { 0, };
	KeyExpansion(roundKey, key);

	AddRoundKey(plainText, roundKey[0]);

	for (int i = 1; i < 10; i++) {
		/*SubBytes(plainText);*/
		ShiftRows(plainText);
		/*MixColumns(plainText);*/
		subMix(plainText);
		AddRoundKey(plainText, roundKey[i]);
	}

	for (int i = 0; i < 4; i++) {
		wtob(&state[4*i], plainText[i]);
	}

	SubBytes(state);

	for (int i = 0; i < 4; i++) {
		btow(&state[4 * i], &plainText[i]);
	}

	ShiftRows(plainText);
	AddRoundKey(plainText, roundKey[10]);
	for (int i = 0; i < 4; i++) {
		cipher[i] = plainText[i];
	}
}
int main()
{
	/*unsigned char plainText[16] = { 0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34 };*/
	word plainText[4] = {0x6a84867c,0xd77e12ad,0x07ea1be8,0x95c53fa3};
	unsigned char key[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }; //������ Ű
	/*unsigned int roundKey[11][16] = { 0, };*/
	word cipher[4] = { 0, };

	/*KeyExpansion(roundKey, key);*/

	/*AddRoundKey(plainText, roundKey[0]);*/

	AES(plainText, key, cipher);
	
	printf("%x", cipher[0]);

	/*for (int i = 1; i < 10; i++) {
		SubBytes(plainText);
		ShiftRows(plainText);
		MixColumns(plainText);
		AddRoundKey(plainText, roundKey[i]);
	}

	SubBytes(plainText);
	ShiftRows(plainText);
	AddRoundKey(plainText, roundKey[10]);

	for (int i = 0; i < 16; i++) {
		printf("%02x ", plainText[i]);
	}*/
}