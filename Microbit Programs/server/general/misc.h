#pragma once
#include <MicroBit.h>

void drawImage(const uint32_t& image, MicroBit& uBit);

template <typename T>
T clamp(const T& n, const T& lower, const T& upper) {
  return std::max(lower, std::min(n, upper));
}

void changeState(enum states state);
