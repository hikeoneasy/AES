#ifndef __AESENC_H_
#define  __AESENC_H_
#include "KEYGEN.h"

void ADDROUND(byte state[16], byte roundkey[16]);
void SUBBYTE(byte state[16]);
void SHIFTROW(byte state[16]);
byte xtime(byte x);
byte m02(byte x);
byte m03(byte x);
void MIXSUB(byte state[4]);
void MIXCOLUMS(byte state[16]);
void ROUND(byte state[16], byte KEY[16]);


#endif