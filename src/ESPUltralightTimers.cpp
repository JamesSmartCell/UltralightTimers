#include <ESPUltralightTimers.h>

portMUX_TYPE _ultralightTimerMux = portMUX_INITIALIZER_UNLOCKED;
hw_timer_t ** _ultralightTimer = NULL;
void (*_ultralightCallbackSlot[SOC_TIMER_GROUP_TOTAL_TIMERS])();

void timerCallbackFunc(int slot)
{
  portENTER_CRITICAL(&_ultralightTimerMux);
  timer_function thisFunc = _ultralightCallbackSlot[slot];
  hw_timer_t * thisTimer = _ultralightTimer[slot];
  timerAlarmWrite(thisTimer, 0, true);
  timerStop(thisTimer);
  portEXIT_CRITICAL(&_ultralightTimerMux);

  thisFunc();
}

void IRAM_ATTR timerCallback0()
{
  timerCallbackFunc(0);
}
void IRAM_ATTR timerCallback1()
{
  timerCallbackFunc(1);
}
void IRAM_ATTR timerCallback2()
{
  timerCallbackFunc(2);
}
void IRAM_ATTR timerCallback3()
{
  timerCallbackFunc(3);
}

void (*_ultralightTimerCallback[4])() = { timerCallback0, timerCallback1, timerCallback2, timerCallback3 };

void _ultralightAttachInterrupt(hw_timer_t *timer, int slot)
{
    switch (slot)
    {
      case 0:
        timerAttachInterrupt(timer, &timerCallback0, true);
        break;
      case 1:
        timerAttachInterrupt(timer, &timerCallback1, true);
        break;
      case 2:
        timerAttachInterrupt(timer, &timerCallback2, true);
        break;
      case 3:
        timerAttachInterrupt(timer, &timerCallback3, true);
        break;
    }
}

void initTimers()
{
  _ultralightTimer = new hw_timer_t*[SOC_TIMER_GROUP_TOTAL_TIMERS];
  memset(_ultralightTimer, 0, sizeof(hw_timer_t*) * SOC_TIMER_GROUP_TOTAL_TIMERS);
}

int checkTimerAvailability()
{
  if (_ultralightTimer == 0) { initTimers(); } 

  portENTER_CRITICAL(&_ultralightTimerMux);
  for (int i = 0; i < SOC_TIMER_GROUP_TOTAL_TIMERS; i++) 
  {
    hw_timer_t* thisTmr = _ultralightTimer[i];
    if (thisTmr == 0 || (timerAlarmRead(thisTmr) & 0xFFFFFFFF) == 0)
    {
      portEXIT_CRITICAL(&_ultralightTimerMux);
      return i;
    }
  }

  portEXIT_CRITICAL(&_ultralightTimerMux);
  return -1;
}

void setTimerMillis(long millis, timer_function func)
{
  int slot = checkTimerAvailability();
  if (slot == -1) return;
  hw_timer_t* tmr = _ultralightTimer[slot];

  _ultralightCallbackSlot[slot] = func;

  long interruptTime = 1000 * millis;

  if (tmr == 0)
  {
    tmr = timerBegin(slot, 80, true);
    _ultralightAttachInterrupt(tmr, slot);
    timerAlarmWrite(tmr, interruptTime, true);
    timerAlarmEnable(tmr);
    _ultralightTimer[slot] = tmr;
  } 
  else
  {
    timerAlarmWrite(tmr, interruptTime, true);
    timerStart(tmr);
  }
}

void setTimer(long seconds, timer_function func)
{
  setTimerMillis(seconds*1000, func);
}