# ESPUltralightTimers  [![PlatformIO Registry](https://badges.registry.platformio.org/packages/jamessmartcell/library/ESPUltralightTimers.svg)](https://registry.platformio.org/libraries/jamessmartcell/ESPUltralightTimers)

ESP32 Ultralight Timers

Very lightweight library :-
Place non-recurring timers with callbacks using the ESP32 interrupts.

Limited by number of hardware timers in each platform: 
- ESP32 has 4 timers
- ESP32 C3 has 2 timers

Future TODO: allow any number of timers on any hardware by using a stack which gets resolved by the hardware timers in time order

Usage:

```
void func1() {
  Serial.println("Hello from func1");
  setTimer(30, &func1); //call func1 again in 30 seconds
}

void func2() {
  Serial.println("Hi from func2");
}

void setup() {
  ...
  initTimers();
  ...
  
  setTimer(20, &func1);
  setTimerMillis(5560, &func2);
  ...
}
```