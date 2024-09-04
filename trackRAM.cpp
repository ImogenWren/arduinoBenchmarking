#include "trackRam.h"



trackRAM::trackRAM() {
}



int trackRAM::begin() {
  int init_heap_start = trackRAM::heapStart();
  int currentStackSize = trackRAM::stackSize();
  int currentHeapSize = trackRAM::heapSize();
  int currentFreeRAM = trackRAM::freeMemory();
  static_data = total_mem - (currentFreeRAM + currentStackSize + currentHeapSize);
  int dynamic_mem = currentFreeRAM + currentStackSize;
  Serial.print("total_mem: ");
  Serial.println(total_mem);
  Serial.print("heap_start: ");
  Serial.println(init_heap_start);
  Serial.print("stack_size: ");
  Serial.println(currentStackSize);
  Serial.print("heap_size: ");
  Serial.println(currentHeapSize);
  Serial.print("free_ram: ");
  Serial.println(currentFreeRAM);
  Serial.print("Calculating static_data (should match compiler output!): ");
  Serial.println(static_data);  // These should be the same?
  Serial.print("Calculating dynamic_mem (should match compiler output!): ");
  Serial.println(dynamic_mem);  // These should be the same?
  int calculated_memory = currentStackSize + currentHeapSize + currentFreeRAM + static_data;
  Serial.print("Calculating memory: ");
  Serial.println(calculated_memory);  // These should be the same?


  return static_data;
}

void trackRAM::printStats(const char *context) {
  char buffer[128];
  // sprintf(buffer, "%10s RAM (total): %4i, (used): %4i, (free): %4i, (max): %4i, (stacksize): %4i", context, totalMem, startStack, usedMem, freeRam, maxStack, stackSize);
  Serial.println(buffer);
}


// Gets the total free memory between the stack & the heap
int trackRAM::freeMemory() {
  extern int __heap_start, *__brkval;
  int v;
  free_RAM = (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
  return free_RAM;
}


int trackRAM::heapSize() {
  extern int *__brkval;
  //  int32_t heap_size;
  // Check if heap is used
  if (__brkval == 0) {
    //Serial.print(F("Heap has not been used yet (ptr): "));
    heap_size = 0;
  } else {
    //Serial.print(F("Current end of heap (ptr): "));
    heap_size = (uint32_t)__brkval - heap_start;
  }
  //Serial.println((uintptr_t)__brkval);
  //Serial.print(F("Heap Size: "));
  //Serial.println(heap_size);
  // Serial.print("test: ");
  // Serial.println(__brkval - &__heap_start);
  return heap_size;
}

inline size_t trackRAM::stackSize() {
  stack_size = RAMEND - SP;
  return stack_size;
}




int trackRAM::heapStart() {
  uintptr_t heap_start;
  // Print the address of the start of the heap
  //Serial.print(F("Start of heap: "));
  heap_start = (uintptr_t)&__malloc_heap_start;
  //Serial.println(heap_start);
  return heap_start;
}