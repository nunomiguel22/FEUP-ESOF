#include "ButtonManager.h"

#include "../radio/RadioManager.h"
#include "Globals.h"
#include "misc.h"

const char group_name2[] = "tiger";

void ButtonManager::groupHandler(MicroBitEvent e) {
  if (e.value == MICROBIT_BUTTON_EVT_DOWN) {
    if (e.source == MICROBIT_ID_BUTTON_AB) {
      changeState(ST_PROXIMITY);
      return;
    }

    if (e.source == MICROBIT_ID_BUTTON_A)
      --radioGroup;
    else if (e.source == MICROBIT_ID_BUTTON_B)
      ++radioGroup;

    radioGroup = clamp(radioGroup, (uint8_t)0, (uint8_t)9);
    uBit.radio.setGroup(radioGroup);
  }
}
void ButtonManager::proximityHandler(MicroBitEvent e) {
  if (e.value == MICROBIT_BUTTON_EVT_HOLD && e.source == MICROBIT_ID_BUTTON_AB)
    changeState(ST_GROUP);

  if (e.value == MICROBIT_BUTTON_EVT_HOLD &&
      e.source == MICROBIT_ID_BUTTON_A)
    changeState(ST_VOTING);
}

void ButtonManager::votingHandler(MicroBitEvent e) {
  if (e.value == MICROBIT_BUTTON_EVT_HOLD && e.source == MICROBIT_ID_BUTTON_AB)
    changeState(ST_PROXIMITY);

  if (e.value == MICROBIT_BUTTON_EVT_CLICK) {
    if (e.source == MICROBIT_ID_BUTTON_A) RadioManager::sendVote("Y");
    if (e.source == MICROBIT_ID_BUTTON_B) RadioManager::sendVote("N");
  }
}

void ButtonManager::listenAllButtons(void (*handler)(MicroBitEvent e)) {
  static void (*onButtonHandler)(MicroBitEvent e) = NULL;

  if (onButtonHandler != NULL) {
    uBit.messageBus.ignore(MICROBIT_ID_BUTTON_A, MICROBIT_EVT_ANY,
                           onButtonHandler);
    uBit.messageBus.ignore(MICROBIT_ID_BUTTON_B, MICROBIT_EVT_ANY,
                           onButtonHandler);
    uBit.messageBus.ignore(MICROBIT_ID_BUTTON_AB, MICROBIT_EVT_ANY,
                           onButtonHandler);
  }

  onButtonHandler = handler;
  uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_EVT_ANY, handler);
  uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_EVT_ANY, handler);
  uBit.messageBus.listen(MICROBIT_ID_BUTTON_AB, MICROBIT_EVT_ANY, handler);
}
