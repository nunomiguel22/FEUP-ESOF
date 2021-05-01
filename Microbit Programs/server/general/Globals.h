#pragma once
#include "MicroBit.h"

enum states { ST_VOTING, ST_GROUP, ST_PROXIMITY };

// Macros
#define checkMark 0b0000000001000101010001000
#define xMark 0b1000101010001000101010001

extern MicroBit uBit;
extern enum states uBitState;
extern uint8_t radioGroup;
extern int microbitID;

// TEMPORARY
extern unsigned int friend_seen;
