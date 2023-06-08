#include <SPI.h>

#include <FS.h>
#include <SD.h>

#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

// JPEG decoder library
#include <JPEGDecoder.h>

//Declaring SPI Pins for SD Card Module and Creating a New Class for SD SPI
#define SD_MOSI      13
#define SD_MISO      27
#define SD_SCK       14
#define SD_CS_PIN    15
SPIClass SPISD(HSPI);

void setup() {
    Serial.begin(115200);  //Initialize SD card. Trying this for two times..

  SPISD.begin(SD_SCK, SD_MISO, SD_MOSI);
  Serial.println("Initializing SD card...");

  // Set all chip selects high to avoid bus contention during initialisation of each peripheral
  
  digitalWrite(2, HIGH); // TFT screen chip select
  digitalWrite(15, HIGH); // SD card chips select, must use GPIO 5 (ESP32 SS)

  tft.begin();

  if (!SD.begin(SD_CS_PIN, SPISD)) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);

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

  delay(1000);

  tft.fillRect(0,35, 160,128, TFT_WHITE);

  delay(50000);



}
