#include "FileManager.h"

FileManager::FileManager(MicroBit &uBit) { this->uBit = &uBit; }

int FileManager::read(const char *key, int &target) {
  if (key == NULL) return -1;

  KeyValuePair *valuePair = uBit->storage.get(key);
  if (valuePair == NULL) return -1;

  memcpy(&target, valuePair->value, sizeof(int));
  delete valuePair;
  return 0;
}

int FileManager::write(const char *key, const int &value) {
  if (key == NULL) return -1;

  uBit->storage.put(key, (uint8_t *)&value, sizeof(int));
  return 0;
}

int FileManager::write(const char *key, const ManagedString &value) {
  return this->write(key, value.toCharArray());
}

int FileManager::write(const char *key, const char *value) {
  if (key == NULL) return -1;

  uBit->storage.put(key, (uint8_t *)&value, sizeof(value) / sizeof(value[0]));
  return 0;
}

int FileManager::remove(const char *key) {
  if (key == NULL) return -1;

  if (uBit->storage.remove(key) == MICROBIT_NO_DATA) return -1;

  return 0;
}

int FileManager::size() { return uBit->storage.size(); }
