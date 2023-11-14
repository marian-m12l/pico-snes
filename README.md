This program continuously polls a SNES controller (every ~210 us), and prints its status about 60 times per seconds.

It uses PIO and DMA so the CPU is free to work on other tasks, and can directly read the controller's current status in RAM.

Given the pinout:
```
  -----------------        1: VCC       4: Data
 | 1 2 3 4 | 5 6 7 )       2: Clock     7: Ground
  -----------------        3: Latch
```

The controller is expected to be wired as follows:

```
 SNES         Pico
 ------------------
 1 VCC        3V3
 2 Clock      GP13
 3 Latch      GP14
 4 Data       GP15
 7 Ground     GND
```


## Build instructions

```
mkdir build
cd build
cmake ..
make
```
