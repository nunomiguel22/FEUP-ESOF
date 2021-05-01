#pragma once
#include "MicroBit.h"

namespace RadioManager {
void init(int transmitPower);
void proximityHandler(MicroBitEvent);
void receiveVotes(MicroBitEvent);
}  // namespace RadioManager
