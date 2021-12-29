#include "AES_DEC.h"

void INV_ADDROUND(byte state[16], byte roundkey[16])
{
	//fast ver
	state[0] ^= roundkey[0]; state[8] ^= roundkey[8];
	state[1] ^= roundkey[1]; state[9] ^= roundkey[9];
	state[2] ^= roundkey[2]; state[10] ^= roundkey[10];
	state[3] ^= roundkey[3]; state[11] ^= roundkey[11];
	state[4] ^= roundkey[4]; state[12] ^= roundkey[12];
	state[5] ^= roundkey[5]; state[13] ^= roundkey[13];
	state[6] ^= roundkey[6]; state[14] ^= roundkey[14];
	state[7] ^= roundkey[7]; state[15] ^= roundkey[15];

}
void INV_SUBBYTE(byte state[16])
{
	//fast ver
	state[0] = inv_s_box[state[0]]; state[1] = inv_s_box[state[1]];
	state[2] = inv_s_box[state[2]]; state[3] = inv_s_box[state[3]];
	state[4] = inv_s_box[state[4]]; state[5] = inv_s_box[state[5]];
	state[6] = inv_s_box[state[6]]; state[7] = inv_s_box[state[7]];
	state[8] = inv_s_box[state[8]]; state[9] = inv_s_box[state[9]];
	state[10] = inv_s_box[state[10]]; state[11] = inv_s_box[state[11]];
	state[12] = inv_s_box[state[12]]; state[13] = inv_s_box[state[13]];
	state[14] = inv_s_box[state[14]]; state[15] = inv_s_box[state[15]];
}
void INV_SHIFTROW(byte state[16])
{
	//fast ver
	byte tmp[16] = { 0, };
	memcpy(tmp, state, 16 * sizeof(byte));
	state[1] = tmp[13]; state[5] = tmp[1];
	state[9] = tmp[5]; state[13] = tmp[9];
	
	state[2] = tmp[10]; state[6] = tmp[14];
	state[10] = tmp[2]; state[14] = tmp[6];
	
	state[3] = tmp[7]; state[7] = tmp[11];
	state[11] = tmp[15]; state[15] = tmp[3];


}

byte _xtime(byte x)
{
	byte y = ((x << 1) & 0xff) ^ ((x >> 7) * 0x1b);
	return y;
}

byte m04(byte x)
{
	return _xtime(_xtime(x)) ;
}

byte m08(byte x)
{
	return _xtime(m04(x));
}
byte m09(byte x)
{
	return m08(x) ^ x;
}
byte m0b(byte x)
{
	return m08(x) ^ (_xtime(x) ^ x);
}
byte m0d(byte x)
{
	return m08(x) ^ m04(x) ^ x;
}
byte m0e(byte x)
{
	return m08(x) ^ m04(x) ^ _xtime(x);
}

void INV_MIXCOLUMS(byte state[16])
{
	byte tmp[16] = { 0, };
	memcpy(tmp, state, sizeof(byte) * 16);
	//fast ver
	state[0] = m0e(tmp[0]) ^ m0b(tmp[1]) ^ m0d(tmp[2]) ^ m09(tmp[3]);
	state[1] = m09(tmp[0]) ^ m0e(tmp[1]) ^ m0b(tmp[2]) ^ m0d(tmp[3]);
	state[2] = m0d(tmp[0]) ^ m09(tmp[1]) ^ m0e(tmp[2]) ^ m0b(tmp[3]);
	state[3] = m0b(tmp[0]) ^ m0d(tmp[1]) ^ m09(tmp[2]) ^ m0e(tmp[3]);
				   				 			   				 
	state[4] = m0e(tmp[4]) ^ m0b(tmp[5]) ^ m0d(tmp[6]) ^ m09(tmp[7]);
	state[5] = m09(tmp[4]) ^ m0e(tmp[5]) ^ m0b(tmp[6]) ^ m0d(tmp[7]);
	state[6] = m0d(tmp[4]) ^ m09(tmp[5]) ^ m0e(tmp[6]) ^ m0b(tmp[7]);
	state[7] = m0b(tmp[4]) ^ m0d(tmp[5]) ^ m09(tmp[6]) ^ m0e(tmp[7]);
				   				 			   
	state[8] = m0e(tmp[8]) ^ m0b(tmp[9]) ^ m0d(tmp[10]) ^ m09(tmp[11]);
	state[9] = m09(tmp[8]) ^ m0e(tmp[9]) ^ m0b(tmp[10]) ^ m0d(tmp[11]);
	state[10] = m0d(tmp[8]) ^ m09(tmp[9]) ^ m0e(tmp[10]) ^ m0b(tmp[11]);
	state[11] = m0b(tmp[8]) ^ m0d(tmp[9]) ^ m09(tmp[10]) ^ m0e(tmp[11]);
					
	state[12] = m0e(tmp[12]) ^ m0b(tmp[13]) ^ m0d(tmp[14]) ^ m09(tmp[15]);
	state[13] = m09(tmp[12]) ^ m0e(tmp[13]) ^ m0b(tmp[14]) ^ m0d(tmp[15]);
	state[14] = m0d(tmp[12]) ^ m09(tmp[13]) ^ m0e(tmp[14]) ^ m0b(tmp[15]);
	state[15] = m0b(tmp[12]) ^ m0d(tmp[13]) ^ m09(tmp[14]) ^ m0e(tmp[15]);


}
void _ROUND(byte state[16], byte KEY[16])
{

	INV_SHIFTROW(state);
	

	INV_SUBBYTE(state);
	


	
	INV_ADDROUND(state, KEY);
	
	
	INV_MIXCOLUMS(state);
	

}

void AES_DEC(byte state[16], byte KEY[16])
{
	
	INV_ADDROUND(state, KEY);
	
	for (int i = round-1; i > 0; i--)
	{
		INV_KEY_schedule(KEY, i);
		
		_ROUND(state, KEY);
	}
	INV_KEY_schedule(KEY, 0);
	
	INV_SHIFTROW(state);

	
	INV_SUBBYTE(state);

	
	INV_ADDROUND(state, KEY);

	
}