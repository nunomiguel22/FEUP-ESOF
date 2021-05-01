#include "ButtonManager.h"
#include "Globals.h"
#include "RadioManager.h"
#include "misc.h"

MicroBit uBit;
enum states uBitState = ST_PROXIMITY;
uint8_t radioGroup = 0;

unsigned int friend_seen = 0;
const char group_name[] = "tiger";

void receive(MicroBitEvent) {
  ManagedString s = uBit.radio.datagram.recv();

#ifdef UBITSERIALDEBUG
  int rssi = uBit.radio.getRSSI();
  uBit.serial.send("Data: ");
  uBit.serial.send(s);
  uBit.serial.send("  ");
  uBit.serial.send("RSSI: ");
  uBit.serial.send(rssi);
  uBit.serial.send("\n");
#endif
  uBit.serial.send(s + "\n");
}

int main() {
  // Initialize uBit framework and stack
  uBit.init();

  uBit.serial.send("asd\n");

  // Initialize Radio framework
  RadioManager::init(6);

  // Initialize button and randio listeners
  uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM,
                         receive);

  while (true) {
    uBit.display.scrollAsync("Receiving votes");
    uBit.sleep(100);
  }
}
