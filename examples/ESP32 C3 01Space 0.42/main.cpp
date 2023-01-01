#include <Arduino.h>
#include <ESPUltralightTimers.h>
#include <U8g2lib.h>
#include <string>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
#define LED_COUNT 1
#define LED_PIN 2
#define SDA_PIN 5
#define SCL_PIN 6

uint8_t lineStuff = 0; 
uint8_t diff = 1;
std::string boxMsg;

U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); 

void u8g2_prepare(void) 
{
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void drawText(const char *text)
{
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(0, 10, text);	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
}

void u8g2_line(uint8_t a, const char *text)
{
  u8g2.drawStr( 0, 0, text);
  u8g2.drawLine(1+a, 10, 40, 55);
  u8g2.drawLine(1+a*2, 10, 60, 55);
  u8g2.drawLine(1+a*3, 10, 80, 55);
  u8g2.drawLine(1+a*4, 10, 100, 55);
}

void u8g2_string(uint8_t a) 
{
  u8g2.setFontDirection(0);
  u8g2.drawStr(30+a,31, " 0");
  u8g2.setFontDirection(1);
  u8g2.drawStr(30,31+a, " 90");
  u8g2.setFontDirection(2);
  u8g2.drawStr(30-a,31, " 180");
  u8g2.setFontDirection(3);
  u8g2.drawStr(30,31-a, " 270");
}

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
  boxMsg = "Func1";
  lineStuff = 3;
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
  boxMsg = "Func2";
  lineStuff = 3;
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
  Wire.begin(SDA_PIN, SCL_PIN);
  u8g2.begin();
  Serial.println("Init Timers");
  lineStuff = 3;
  initTimers();

  boxMsg = "Begin";

  Serial.println("Begin Timer test");

  u8g2_prepare();

  setTimer(20, &func1);
  setTimer(30, &func2);
  //setTimer(40, &func3);
  //setTimer(5, &func4);
}

void loop() 
{
  Serial.println("Begin Timer test 33");
  delay(100);
  u8g2.clearBuffer();

  if (lineStuff > 2 && lineStuff < 60)
  {
    u8g2_line(lineStuff, boxMsg.c_str());
    u8g2.sendBuffer();
    lineStuff+=diff;
  }
  else
  {
    u8g2.clearBuffer();
    u8g2.sendBuffer();
  }
}