#include "MicroBit.h"

class FileManager {
 private:
  MicroBit *uBit;

 public:
  FileManager(MicroBit &uBit);

  /**
   * Reads an int with 'key' and saves it to 'target'
   * Returns -1 if key was not found, 0 on success
   */
  int read(const char *key, int &target);
  /**
   * Writes an integer 'value' with 'key' to flash memory
   * Returns -1 on failure, 0 on success
   */
  int write(const char *key, const int &value);
  /**
   * Writes an integer 'value' with 'key' to flash memory
   * Returns -1 on failure, 0 on success
   */
  int write(const char *key, const ManagedString &value);
  /**
   * Writes a string 'value' with 'key' to flash memory
   * Returns -1 on failure, 0 on success
   */
  int write(const char *key, const char *value);
  /**
   * Removes the value with 'key' from flash memory
   * Returns -1 on failure, 0 on success
   */
  int remove(const char *key);
  /**
   * Returns the number of keys in flash memory
   */
  int size();
};
