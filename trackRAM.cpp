#include "trackRam.h"



trackRAM::trackRAM() {
}



int trackRAM::begin() {
  int init_heap_start = trackRAM::heapStart();  // Must be called at start to understand static data
  int currentStackSize = trackRAM::stackSize();
  int currentHeapSize = trackRAM::heapSize();
  int currentFreeRAM = trackRAM::freeMemory();
  static_data = total_mem - (currentFreeRAM + currentStackSize + currentHeapSize);
  int dynamic_mem = currentFreeRAM + currentStackSize;
  int calculated_memory = currentStackSize + currentHeapSize + currentFreeRAM + static_data;
#if PRINT_OPENING_STATS == true
  Serial.print(F("total_mem: "));
  Serial.println(total_mem);
  Serial.print(F("heap_start: "));
  Serial.println(init_heap_start);
  Serial.print(F("stack_size: "));
  Serial.println(currentStackSize);
  Serial.print(F("heap_size: "));
  Serial.println(currentHeapSize);
  Serial.print(F("free_ram: "));
  Serial.println(currentFreeRAM);
  Serial.print(F("Calculating static_data (should match compiler output!): "));
  Serial.println(static_data);  // These should be the same?
  Serial.print(F("Calculating dynamic_mem (should match compiler output!): "));
  Serial.println(dynamic_mem);  // These should be the same?
  Serial.print(F("Calculating memory: "));
  Serial.println(calculated_memory);  // Should Equal total_mem
  //trackRAM::printStats("begin");
#endif
  trackRAM::printStats("begin");
  return static_data;
}



void trackRAM::printStats(const char *context) {
  char buffer[128];
  sprintf(buffer, "%10s RAM (total): %4i, (free): %4i, (stack,max): %4i,%4i, (heap,max): %4i,%4i, (static): %4i", context, total_mem, free_RAM, stack_size, max_stack, heap_size, max_heap, static_data);
  Serial.println(buffer);
}


void trackRAM::getStats() {
  int currentStack = trackRAM::stackSize();
  int currentHeap = trackRAM::heapSize();
  if (currentStack > max_stack) max_stack = currentStack;
  if (currentHeap > max_heap) max_heap = currentHeap;
  trackRAM::freeMemory();
}


void trackRAM::getPrintStats(const char *context) {
  trackRAM::getStats();
  trackRAM::printStats(context);
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
  heap_start;
  // Print the address of the start of the heap
  //Serial.print(F("Start of heap: "));
  heap_start = (uintptr_t)&__malloc_heap_start;
  //Serial.println(heap_start);
  return heap_start;
}