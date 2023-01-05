/**
 * ESP Ultralight timers
 * 2023 J Brown github @jamessmartcell twitter @tallydigital
 * j@smarttokenlabs.com
 * 
 * Very lightweight library :-
 * place non-recurring timers with callbacks using the ESP32 interrupts.
 * 
 * Limited by number of hardware timers in each platform: 
 * - ESP32 has 4 timers
 * - ESP32 C3 has 2 timers
 * 
 * Future TODO: allow any number of timers on any hardware by 
 * using a stack which gets resolved by the hardware timers in time order
 */

#ifndef __ESPUltralighTimers_h
#define __ESPUltralighTimers_h

#include <Arduino.h>

typedef void (*timer_function)(void);

void setTimerMillis(long millis, timer_function func);
void setTimer(long seconds, timer_function func);

#endif //__ESPUltralighTimers_h