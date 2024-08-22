/* arduinoBenchmarking Example

 Example of various benchmarking functions that can be used to aid debugging and characterise the useage of arduino/AVR hardware
 during runtime

*/


// Below code added from https://arduino.stackexchange.com/questions/65351/how-to-find-out-the-maximum-used-stack-space
#include <util/atomic.h>

volatile size_t min_sp = RAMEND;

ISR(TIMER0_COMPA_vect){
    if (SP < min_sp)
        min_sp = SP;
}

static inline size_t max_stack_size(){
    size_t min_sp_copy;
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        min_sp_copy = min_sp;
    }
    return RAMEND - min_sp_copy;
}

int freeRam;

int freeMemory() {
  extern int __heap_start, *__brkval;
  int v;
  freeRam = (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
  return freeRam;
}

static inline size_t stack_size()
{
    return RAMEND - SP;
}

void printStats() {
  char buffer[64];
  sprintf(buffer, "RAM (free): %i", freeRam)
};

void setup() {
  TIMSK0 |= _BV(OCIE0A);  // enable TIMER0_COMPA interrupt
  Serial.begin(115200);
  Serial.println("Arduino Benchmarking Examples");
}

void loop() {
  freeMemory();  // update global variable freeRam
  delay(2000);
  printStats();
}
