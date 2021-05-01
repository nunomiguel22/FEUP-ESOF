#pragma once
#include "MicroBit.h"

namespace ButtonManager {
void groupHandler(MicroBitEvent e);
void proximityHandler(MicroBitEvent e);
void listenAllButtons(void (*handler)(MicroBitEvent e));
}  // namespace ButtonManager
