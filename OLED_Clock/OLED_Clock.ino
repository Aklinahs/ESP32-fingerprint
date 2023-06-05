#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
RTC_DS1307 RTC;
char days[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  Serial.begin(115200);

  if (!RTC.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(1000);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30, 20);
  // Display static text
  display.println("RTC");
  display.display();
  delay(3000);
  display.clearDisplay();
}

void loop() {
  DateTime now = RTC.now();

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print(now.day());
  display.print('/');
  display.print(now.month());
  display.print('/');
  display.print(now.year());
  display.println(days[now.dayOfTheWeek()]);
  display.println(' ');
  display.setCursor(0, 40);
  if (now.hour() < 10)
    display.print('0');
  display.print(now.hour());
  display.print(':');
  if (now.minute() < 10)
    display.print('0');
  display.print(now.minute());
  display.print(':');
  if (now.second() < 10)
    display.print('0');
  display.println(now.second());
  display.display();
}