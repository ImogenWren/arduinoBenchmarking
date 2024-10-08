/*
BenchTesting

_Just for Testing Individual Concepts_

*/
extern int __heap_start, *__brkval;

void printHeapStats_hex() {
  Serial.println();
  // Print the address of the start of the heap
  Serial.print(F("Start of heap: "));
  Serial.println((uintptr_t)&__malloc_heap_start, HEX);

  // Check if heap is used
  if (__brkval == 0) {
    Serial.println(F("Heap has not been used yet."));
    Serial.println((uintptr_t)__brkval, HEX);
  } else {
    Serial.print(F("Current end of heap (ptr): "));
  }
  Serial.println((uintptr_t)__brkval, HEX);
}




void printHeapStats() {
  uintptr_t heap_start;
  int32_t heap_size;
  // Print the address of the start of the heap
  Serial.print(F("Start of heap: "));
  heap_start = (uintptr_t)&__malloc_heap_start;
  Serial.println(heap_start);

  // Check if heap is used
  if (__brkval == 0) {
    Serial.print(F("Heap has not been used yet (ptr): "));
    heap_size = 0;
  } else {
    Serial.print(F("Current end of heap (ptr): "));
    heap_size = (uint32_t)__brkval - heap_start;
  }
  Serial.println((uintptr_t)__brkval);

  Serial.print(F("Heap Size: "));
  Serial.println(heap_size);
  // Serial.print("test: ");
  // Serial.println(__brkval - &__heap_start);
}

void testHeap() {
  printHeapStats();

  uint8_t* ptr = (uint8_t*)malloc(8);  // not sure I follow what is happening here
  Serial.println(F("\nmalloc(8)"));
  printHeapStats();

  Serial.println(F("Adding Data"));
  // fill allocated heap with some random data
  for (int i = 0; i < 8; i++) {
    ptr[i] = i;  // Fill with some data
  }
  printHeapStats();

  // print the data
  Serial.print(F("ptr: "));
  Serial.print(*ptr);
  //  for (int i = 0; i < 8; i++) {
  //   Serial.print(ptr[i]);
  //   Serial.print(" ");
  //  }
  // After use, always free the dynamically allocated memory
  Serial.println(F("\n\nfree(ptr)"));
  free(ptr);
  printHeapStats();
  //  for (int i = 0; i < 8; i++) {
  //    Serial.print(ptr[i]);
  //    Serial.print(" ");
  //  }
}

void setup() {
  Serial.begin(115200);
  Serial.println(F("\n\nBenchTest"));
  testHeap();

}

void loop() {
    //testHeap();
    delay(6000);
}
