#include "misc.h"
#include "ButtonManager.h"
#include "Globals.h"
#include "RadioManager.h"

#define imageMask 0x01000000

void drawImage(const uint32_t &image, MicroBit &uBit) {
  for (int i = 0; i < 25; ++i)
    uBit.display.image.setPixelValue(i % 5, i / 5,
                                     (bool)(image & (imageMask >> i)) * 255);
}

void changeState(enum states state) {
  uBitState = state;
  switch (state) {
    case ST_PROXIMITY: {
      uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM,
                             RadioManager::proximityHandler);
      ButtonManager::listenAllButtons(ButtonManager::proximityHandler);
      break;
    }
    case ST_GROUP: {
      uBit.messageBus.ignore(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM,
                             RadioManager::proximityHandler);
      ButtonManager::listenAllButtons(ButtonManager::groupHandler);
      break;
    }
    case ST_VOTING: {
      uBit.messageBus.ignore(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM,
                             RadioManager::proximityHandler);
      ButtonManager::listenAllButtons(ButtonManager::votingHandler);
      break;
    }

    default:
      break;
  }
}
