/*  trackRAM.h

_Library for tracking RAM usage for Arduino AVR Microcontrollers_


*/



#pragma once

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <wProgram.h>
#endif

#include <util/atomic.h>  // Required for ATOMIC_BLOCK
#include <avr/io.h>       // Required for accessing SPH, SPL
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#if BOARD_TYPE == MEGA
#define TOTAL_SRAM_BYTES 8192
#elif BOARD_TYPE == UNO
#define TOTAL_SRAM_BYTES 2000
#endif

#define PRINT_OPENING_STATS false



class trackRAM {

public:
  // Constructor
  trackRAM();
  // Methods
  int begin();  // Must be called at startup

  // Global Method, call in nested functions to track mem usage at that point in runtime
  void getStats();
  void getPrintStats(const char *context);

  // Get & Calculate Methods
  // Gets the total free memory between the stack & the heap, returns free_RAM
  int freeMemory();
  int heapSize();
  inline size_t stackSize();





  // Reporting Methods
  void printStats(const char *context = "n/a");

  // Testing Methods
  // Adds up the staticData, freeRAM, stackSize -> should equal totalMem + (heap?) (heap size is unknown however we can infer useage)
  void checkWorking();


  // Pointer Methods -> Look under the hood and track variables manually
  void printHeapStats();


  // Var
  int total_mem = TOTAL_SRAM_BYTES;  // NOTE totalMem value relys on user input for timebeing, there does not seem to be a programatic way to get this value
  int static_data;                   // The difference between the freeRAM at bootup and totalMem, should be similar to heap_start?
  int free_RAM;                      // the last updated free ram between top of stack & bottom of heap
  int stack_size;                    // the last updated size of the stack by measuring the difference between RAMEND and SP (Stack Pointer)
  int heap_size;

  int max_heap;
  int max_stack;





  //extern int


private:
  int heapStart();       // Get the pointer for the start of the heap
  uintptr_t heap_start;  // pointer for the start of the heap, addresses lower than this are in use by static or global variables

  volatile size_t min_sp = RAMEND;
};