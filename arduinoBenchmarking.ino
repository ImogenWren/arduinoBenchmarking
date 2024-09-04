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

trackRAM ram;


//ISR(TIMER0_COMPA_vect) {
//  if (SP < min_sp)
//    min_sp = SP;
//}

int startStack;
int maxStack;

/*
//static inline size_t max_stack_size() {
//  size_t min_sp_copy;
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    min_sp_copy = min_sp;
  }
  maxStack = RAMEND - min_sp_copy;
  return maxStack;
}

*/


/*
int usedMem;
int usedMemory() {
  usedMem = startStack - freeRam;
  return usedMem;
}
*/





void setup() {
  Serial.begin(115200);
  Serial.println("\nArduino Benchmarking Example");
  ram.begin();
}







void loop() {
  ram.getPrintStats("loop");
  delay(5000);
  // getRAMstats("loop");
  // delay(2000);
  ///nestedRAMStats();
  //int *ptr = malloc(8);
  uint8_t* ptr = (uint8_t*)malloc(8);
  for (int i = 0; i < 8; i++) {
    ptr[i] = i;  // Fill with some data
  }

  Serial.println("Contents of the allocated memory:");
  for (int i = 0; i < 8; i++) {
    Serial.print(ptr[i]);
    Serial.print(" ");
  }

  // spareFunction(nameString);
  // addToArray(random());
  // printArray(intArray);
}
