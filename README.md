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
#include <ESPUltralightTimers.h>
...

void func1() {
  digitalWrite(RELAY_1, HIGH);
  setTimerMillis(1500, &func2); //call func2 in 1.5 seconds
}

void func2() {
  digitalWrite(RELAY_1, LOW);
  setTimer(20, &func1); //call func1 again in 20 seconds
}

bool showMessage = false;

void func3() {
  showMessage = true;
}

void setup() {
  ...
  setTimer(20, &func1);
  setTimer(50, &func3);
  ...
}

void loop() {
  if (showMessage) { //NB: Don't put serial in the interrupt callbacks - sometimes it works, sometimes it doesn't.
    Serial.println("Hello World");
    showMessage = false;
  }
}
```

