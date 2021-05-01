#pragma once
#include "MicroBit.h"

namespace ButtonManager {
void votingHandler(MicroBitEvent e);
void groupHandler(MicroBitEvent e);
void proximityHandler(MicroBitEvent e);
void listenAllButtons(void (*handler)(MicroBitEvent e));
}  // namespace ButtonManager
