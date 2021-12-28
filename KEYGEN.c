#include "KEYGEN.h"




void RotWord(byte state[4])
{
	byte state2[4] = { state[1],state[2],state[3],state[0] };
	for (int i = 0; i < 4; i++)
	{
		state[i] = state2[i];
	}

}
void SubWord(byte state[4])
{
	for (int i = 0; i < 4; i++)
	{
		state[i] = s_box[state[i]];
	}
}
void Key_schedule(byte state[keysize], int now_round)
{


	byte rk0[4] = { state[0],state[1],state[2],state[3] };
	byte rk1[4] = { state[4],state[5],state[6],state[7] };
	byte rk2[4] = { state[8],state[9],state[10],state[11] };
	byte rk3[4] = { state[12],state[13],state[14],state[15] };

	RotWord(rk3);
	SubWord(rk3);
	rk3[0] ^= Rcon[now_round];

	for (int i = 0; i < 4; i++)
	{
		rk0[i] ^= rk3[i];
	}
	for (int i = 0; i < 4; i++)
	{
		rk1[i] ^= rk0[i];
	}
	for (int i = 0; i < 4; i++)
	{
		rk2[i] ^= rk1[i];
	}
	rk3[0] = rk2[0] ^ state[12]; rk3[1] = rk2[1] ^ state[13];
	rk3[2] = rk2[2] ^ state[14]; rk3[3] = rk2[3] ^ state[15];

	for (int i = 0; i < 4; i++)
	{
		state[i] = rk0[i]; state[i + 4] = rk1[i];
		state[i + 8] = rk2[i]; state[i + 12] = rk3[i];
	}
}
