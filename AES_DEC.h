#ifndef __AESDEC_H_
#define  __AESDEC_H_


#include "KEYGEN.h"


void INV_ADDROUND(byte state[16], byte roundkey[16]);
void INV_SUBBYTE(byte state[16]);
void INV_SHIFTROW(byte state[16]);
byte _xtime(byte x);
byte m04(byte x);
byte m08(byte x);

byte m09(byte x);
byte m0b(byte x);

byte m0d(byte x);
byte m0e(byte x);


void INV_MIXCOLUMS(byte state[16]);
void _ROUND(byte state[16], byte KEY[16]);





#else
#endif