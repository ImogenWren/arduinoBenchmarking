#include "trackRam.h"



trackRAM::trackRAM(){

}



trackRAM::begin(){

}



// Gets the total free memory between the stack & the heap
int trackRAM::freeMemory() {
  extern int __heap_start, *__brkval;
  int v;
  freeRAM = (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
  return freeRAM;
}


void trackRAM::printStats(const char *context) {
  char buffer[128];
  sprintf(buffer, "%10s RAM (total): %4i, (used): %4i, (free): %4i, (max): %4i, (stacksize): %4i", context, startStack, usedMem, freeRam, maxStack, stackSize);
  Serial.println(buffer);
}