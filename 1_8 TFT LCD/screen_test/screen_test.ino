#include <SPI.h>

#include <FS.h>
#include <SD.h>

#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

// JPEG decoder library
#include <JPEGDecoder.h>

void setup() {
  Serial.begin(115200);  //Initialize SD card. Trying this for two times..

  // Set all chip selects high to avoid bus contention during initialisation of each peripheral
  
  digitalWrite(2, HIGH); // TFT screen chip select

  tft.begin();

  Serial.println("initialisation done.");
}

//####################################################################################################
// Main loop
//####################################################################################################
void loop() {

  tft.setRotation(1);  // portrait



  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_WHITE,0xf3c0);
  tft.drawString("    CrewMate    ", 2, 5, 4);
  delay(1000);
  
  tft.setTextColor(TFT_BLACK);
  tft.drawString("Model - CM-FSv3", 25, 35, 2);
  delay(1000);

  tft.setTextColor(TFT_BLUE);
  tft.drawString("Firmware - 3.3", 40, 53, 1);

  tft.setTextColor(TFT_YELLOW, TFT_RED);
  tft.drawString(" ERROR - RTC N/A ", 17, 75, 2);
  delay(1000);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.drawString("                           ", 0, 75, 2);
  tft.setTextColor(TFT_DARKGREEN);
  tft.drawString("RTC-OK", 60, 75, 2);

  tft.setTextColor(TFT_YELLOW, TFT_RED);
  tft.drawString(" ERROR - SD N/A ", 17, 90, 2);
  delay(1000);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.drawString("                           ", 0, 90, 2);
  tft.setTextColor(TFT_DARKGREEN);
  tft.drawString("SD-OK(SDSC)", 60, 90, 2);

  delay(50000);



}
