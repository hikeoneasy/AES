#ifndef __KEYGEN_H_
#define __KEYGEN_H_


#include "S_box.h"

#define keysize 16
#define round 10



static byte Rcon[10] = { 0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36 };
void RotWord(byte state[4]);
void SubWord(byte state[4]);
void Key_schedule(byte state[keysize], int now_round);
#endif

