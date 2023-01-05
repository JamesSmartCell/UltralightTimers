#include <Arduino.h>
#include <ESPUltralightTimers.h>

long funcCount[5];
long funcProjection[5];
long actionFuncTime[5];

int showFunc = 0;

void updateFuncDetails(int index, long seconds)
{
  actionFuncTime[index] = millis();
  funcProjection[index] = millis() + seconds*1000;
  funcCount[index]++;
  showFunc = index;
}

void func1()
{
  long seconds = 20;
  updateFuncDetails(1, seconds);
  setTimer(seconds, &func1);
}

void func2()
{
  long seconds = 47;
  updateFuncDetails(2, seconds);
  setTimer(seconds, &func2);
}

void func3()
{
  long seconds = 6;
  updateFuncDetails(3, seconds);
  setTimer(seconds, &func3);
}

void func4()
{
  long seconds = 63;
  updateFuncDetails(4, seconds);
  setTimer(seconds, &func4);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Begin Timer test");

  for (int i = 1; i < 5; i++)
  {
    funcProjection[i] = millis() + i*10;
  }

  setTimer(10, &func1);
  setTimer(20, &func2);
  setTimer(30, &func3);
  setTimer(40, &func4);
}

void loop() {
  delay(100);
  // put serial outside of interrupts. Note, sometimes interrupt calls will occur simultaneously
  // only the last one will display but it was called - this is a simple example
  if (showFunc > 0)
  {
    Serial.print("Func ");
    Serial.print(showFunc);
    Serial.print(": ");
    Serial.print(actionFuncTime[showFunc]);
    Serial.print(" : ");
    Serial.print(funcCount[showFunc]);
    Serial.print(" : Projection: ");
    Serial.println(funcProjection[showFunc]);
    showFunc = 0;
  }
}