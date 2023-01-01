#include <Arduino.h>
#include <ESPUltralightTimers.h>

int func1Count = 0;
int func2Count = 0;
int func3Count = 0;
int func4Count = 0;

long func1Projection = 0;
long func2Projection = 0;
long func3Projection = 0;
long func4Projection = 0;

void func1()
{
  Serial.print("Func 1: ");
  Serial.print(millis());
  Serial.print(" Diff: ");
  Serial.print(millis() - func1Projection);
  Serial.print(" : ");
  Serial.print(func1Count++);
  Serial.print(" : Projection: ");
  func1Projection = millis() + 23*1000;
  Serial.println(func1Projection);
  setTimer(20, &func1);
}

void func2()
{
  Serial.print("Func 2: ");
  Serial.print(millis());
  Serial.print(" Diff: ");
  Serial.print(millis() - func2Projection);
  Serial.print(" : ");
  Serial.print(func2Count++);
  Serial.print(" : Projection: ");
  func2Projection = millis() + 47*1000;
  Serial.println(func2Projection);
  setTimer(47, &func2);
}

void func3()
{
  Serial.print("Func 3: ");
  Serial.print(millis());
  Serial.print(" Diff: ");
  Serial.print(millis() - func3Projection);
  Serial.print(" : ");
  Serial.print(func3Count++);
  Serial.print(" : Projection: ");
  func3Projection = millis() + 6*1000;
  Serial.println(func3Projection);
  setTimer(6, &func3);  
}

void func4()
{
  Serial.print("Func 4: ");
  Serial.print(millis());
  Serial.print(" Diff: ");
  Serial.print(millis() - func4Projection);
  Serial.print(" : ");
  Serial.print(func4Count++);
  Serial.print(" : Projection: ");
  func4Projection = millis() + 63*1000;
  Serial.println(func4Projection);
  setTimer(63, &func4);  
}

void setup() {
  Serial.begin(115200);
  Serial.println("Init Timers");
  initTimers();

  Serial.println("Begin Timer test");

  setTimer(20, &func1);
  setTimer(30, &func2);
  setTimer(40, &func3);
  setTimer(5, &func4);
}

void loop() {
  delay(100);
}