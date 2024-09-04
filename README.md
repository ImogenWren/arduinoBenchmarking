# arduinoBenchmarking
_Benchmarking and hardware tracking functions library & examples_

## Typical Output
_begin() method with debugging_ <br>
```
Arduino Benchmarking Example
total_mem: 8192
heap_start: 514
stack_size: 133
heap_size: 0
free_ram: 7537
Calculating static_data (should match compiler output!): 522
Calculating dynamic_mem (should match compiler output!): 7670
Calculating memory: 8192
```
_printStats() method_ <br>
```
 begin RAM (total): 8192, (free): 7537, (stack):  133, (heap):    0, (static):  522

```
*Stats taken before F() macro char strings. <br>

After F() macro char strings <br>
```
Arduino Benchmarking Example
total_mem: 8192
heap_start: 514
stack_size: 133
heap_size: 0
free_ram: 7731
Calculating static_data (should match compiler output!): 328
Calculating dynamic_mem (should match compiler output!): 7864
Calculating memory: 8192
     begin RAM (total): 8192, (free): 7731, (stack):  133, (heap):    0, (static):  328
```

*Note Match of returned values to compiler message*
```
Sketch uses 3658 bytes (1%) of program storage space. Maximum is 253952 bytes.
Global variables use 322 bytes (3%) of dynamic memory, leaving 7870 bytes for local variables. Maximum is 8192 bytes.
```
- 7870 free (compiler)
- 7731 free (trackRAM)
- 133 stack_size (trackRAM)
- 7864 (total trackRAM)
- 6 bytes unaccounted for






![image](https://github.com/user-attachments/assets/ca94cae9-0d5b-49c9-b8af-9f587fe4d79e)


 ![image](https://github.com/user-attachments/assets/25e1f7df-f98f-440f-b7f0-23ebde38b3a1)

