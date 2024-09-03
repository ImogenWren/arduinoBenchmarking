/*  trackRAM.h

_Library for tracking RAM usage for Arduino AVR Microcontrollers_


*/



#pragma once

#if BOARD_TYPE == MEGA
#define TOTAL_SRAM_BYTES 8192
#elif BOARD_TYPE == UNO
#define TOTAL_SRAM_BYTES 2000
#endif



class trackRAM{

public:
// Constructor
trackRAM();
// Methods
begin(); // Must be called at startup

// Global Method, call in nested functions to track mem usage at that point in runtime
void getMEMstats(const char *context);

// Get & Calculate Methods
// Gets the total free memory between the stack & the heap, returns freeRAM
int freeMemory();
// Gets the Size of the Stack
static inline size_t stack_size();

// Reporting Methods
void printStats(const char *context = "n/a");

// Testing Methods
// Adds up the staticData, freeRAM, stackSize -> should equal totalMem + (heap?) (heap size is unknown however we can infer useage)
void checkWorking();  


// Pointer Methods -> Look under the hood and track variables manually
void printHeapStats();


// Var
int totalMem = TOTAL_SRAM_BYTES;  // NOTE totalMem value relys on user input for timebeing, there does not seem to be a programatic way to get this value
int staticData;   // The difference between the freeRAM at bootup and totalMem, 
int globalVars;    // trying to get the size of the static data directly to compare with the report from the compiler, even if we have to backtrack to get this
int freeRAM; // the last updated free ram between top of stack & bottom of heap
int stackSize;  // the last updated size of the stack by measuring the difference between RAMEND and SP (Stack Pointer)

static inline size_t stack_size() {
  stackSize = RAMEND - SP;
  return stackSize;
}


private:

volatile size_t min_sp = RAMEND;


};