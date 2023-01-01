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

#if 0
#define ULTRALIGHT_LOG( format, ... ) printf("ESP Ultralight: "#format"\n",##__VA_ARGS__)
#else
#define ULTRALIGHT_LOG( format, ... ) (void)format
#endif

portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
hw_timer_t ** timer = NULL;
typedef void (*timer_function)(void);
void (*timerSlot[SOC_TIMER_GROUP_TOTAL_TIMERS])();

void timerCallbackFunc(int slot)
{
  //first call the callback
  timer_function thisFunc = timerSlot[slot];
  //mark timeslot empty
  portENTER_CRITICAL(&timerMux);
  timerSlot[slot] = 0;

  hw_timer_t * thisTimer = timer[slot];
  timerAlarmDisable(thisTimer);
  portEXIT_CRITICAL(&timerMux);

  thisFunc();
}

void timerCallback0()
{
  timerCallbackFunc(0);
}
void timerCallback1()
{
  timerCallbackFunc(1);
}
void timerCallback2()
{
  timerCallbackFunc(2);
}
void timerCallback3()
{
  timerCallbackFunc(3);
}

void (*timerCallback[4])() = { timerCallback0, timerCallback1, timerCallback2, timerCallback3 };

void initTimers()
{
  timer = new hw_timer_t*[SOC_TIMER_GROUP_TOTAL_TIMERS];
  for (int i = 0; i < SOC_TIMER_GROUP_TOTAL_TIMERS; i++)
  {
    timer[i] = timerBegin(i, 80, true);
    timerSlot[i] = 0;
  }
}

int getAvailableTimeslot()
{
  for (int i = 0; i < SOC_TIMER_GROUP_TOTAL_TIMERS; i++)
  {
    if (timerSlot[i] == 0)
    {
      return i;
    }
  }

  return -1;
}

void setTimerMillis(long millis, timer_function func)
{
  portENTER_CRITICAL(&timerMux);
  int slot = getAvailableTimeslot();
  if (slot == -1) 
  {
    ULTRALIGHT_LOG("Unable to place timer."); 
    return; 
  }

  //point to callback
  timerSlot[slot] = func;

  //add timer
  hw_timer_t * thisTimer = timer[slot];

  long interruptTime = 1000 * millis;

  timerAttachInterrupt(thisTimer, timerCallback[slot], true);
  timerAlarmWrite(thisTimer, interruptTime, true);
  timerAlarmEnable(thisTimer);
  portEXIT_CRITICAL(&timerMux);
}

void setTimer(long seconds, timer_function func)
{
    setTimerMillis(seconds*1000, func);
}

#endif //__ESPUltralighTimers_h