

#include "AES_ENC.h"

void ADDROUND(byte state[16], byte roundkey[16])
{
	for (int i = 0; i < 16; i++)
	{
		state[i] = state[i] ^ roundkey[i];
	}
}
void SUBBYTE(byte state[16])
{
	for (int i = 0; i < 16; i++)
	{
		state[i] = s_box[state[i]];
	}
}
void SHIFTROW(byte state[16])
{
	//	byte col1[4] = { state[0],state[4],state[8],state[12] };
	byte col2[4] = { state[5],state[9],state[13],state[1] };
	byte col3[4] = { state[10],state[14],state[2],state[6] };
	byte col4[4] = { state[15],state[3],state[7],state[11] };
	for (int i = 0; i < 4; i++)
	{
		state[4 * i + 1] = col2[i];
		state[4 * i + 2] = col3[i];
		state[4 * i + 3] = col4[i];
	}

}


byte xtime(byte x)
{
	byte y = ((x << 1) & 0xff) ^ ((x >> 7) * 0x1b);
	return y;
}
byte m02(byte x)
{

	return xtime(x);
}
byte m03(byte x)
{
	byte y = x;
	y = y ^ m02(x);

	return y;
}

void MIXSUB(byte state[4])
{
	byte state2[4] = { state[0],state[1],state[2],state[3] };
	state[0] = m02(state2[0]) ^ m03(state2[1]) ^ state2[2] ^ state2[3];
	state[1] = state2[0] ^ m02(state2[1]) ^ m03(state2[2]) ^ state2[3];
	state[2] = (state2[0]) ^ (state2[1]) ^ m02(state2[2]) ^ m03(state2[3]);
	state[3] = m03(state2[0]) ^ (state2[1]) ^ (state2[2]) ^ m02(state2[3]);
}
void MIXCOLUMS(byte state[16])
{
	byte col1[4] = { state[0],state[1],state[2],state[3] };
	byte col2[4] = { state[4],state[5],state[6],state[7] };
	byte col3[4] = { state[8],state[9],state[10],state[11] };
	byte col4[4] = { state[12],state[13],state[14],state[15] };

	MIXSUB(col1);
	MIXSUB(col2);
	MIXSUB(col3);
	MIXSUB(col4);

	for (int i = 0; i < 4; i++)
	{
		state[i] = col1[i];
		state[i + 4] = col2[i];
		state[i + 8] = col3[i];
		state[i + 12] = col4[i];
	}
}

void ROUND(byte state[16], byte KEY[16])
{
	SUBBYTE(state);

	SHIFTROW(state);

	MIXCOLUMS(state);

	ADDROUND(state, KEY);

}


