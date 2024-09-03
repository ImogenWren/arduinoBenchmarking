/* arduinoBenchmarking Example

 Example of various benchmarking functions that can be used to aid debugging and characterise the useage of arduino/AVR hardware
 during runtime

 https://docs.arduino.cc/learn/programming/memory-guide/
 https://oscarliang.com/check-ram-memory-usage-arduino-optimization/

*/

/*
Sketch uses 4406 bytes (1%) of program storage space. Maximum is 253952 bytes.
Global variables use 340 bytes (4%) of dynamic memory, leaving 7852 bytes for local variables. Maximum is 8192 bytes.
*/


// Below code added from https://arduino.stackexchange.com/questions/65351/how-to-find-out-the-maximum-used-stack-space
#include <util/atomic.h>

#define BOARD_TYPE MEGA

#include "trackRAM.h"



ISR(TIMER0_COMPA_vect) {
  if (SP < min_sp)
    min_sp = SP;
}

int startStack;
int maxStack;

static inline size_t max_stack_size() {
  size_t min_sp_copy;
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    min_sp_copy = min_sp;
  }
  maxStack = RAMEND - min_sp_copy;
  return maxStack;
}





int usedMem;
int usedMemory() {
  usedMem = startStack - freeRam;
  return usedMem;
}






void setup() {
  startStack = freeMemory();  // update global variable freeRam
  max_stack_size();
  stack_size();
  usedMemory();
  TIMSK0 |= _BV(OCIE0A);  // enable TIMER0_COMPA interrupt
  Serial.begin(115200);
  Serial.println("Arduino Benchmarking Example");
  Serial.print("Total SRAM: ");
  Serial.println(TOTAL_SRAM_BYTES);
  Serial.print("Global Vars Use: ");
  Serial.println(TOTAL_SRAM_BYTES - startStack);
  Serial.print("Stack Size: ");
  Serial.println(stack_size());
}

char nameString[8] = { "Imogen" };

int intArray[] = { 1, 2, 3 };

void addToArray(int newVal) {
  int arraySize = sizeof(intArray) / sizeof(intArray[0]);
  intArray[arraySize - 1] = newVal;
}

void printArray(const int localArray[]) {
  int arraySize = sizeof(intArray) / sizeof(intArray[0]);
  getRAMstats("printArray");
  for (int i = 0; i < arraySize; i++) {
    Serial.print(localArray[i]);
    Serial.print(", ");
  }
  Serial.println();
}



void spareFunction(const char *charString) {
  Serial.println(charString);
}

void getRAMstats(const char *context) {
  freeMemory();
  stack_size();
  max_stack_size();
  usedMemory();
  printStats(context);
}

int32_t nestedRAMStats() {
  int32_t memoryHog = 1;
  getRAMstats("Nested");
  return memoryHog;
}

int32_t DoublenestedRAMStats() {
  int32_t memoryHog = 1;
  nestedRAMStats();
  return memoryHog;
}

void loop() {
  getRAMstats("loop");
  delay(2000);
  nestedRAMStats();

  // spareFunction(nameString);
  // addToArray(random());
  // printArray(intArray);
}
