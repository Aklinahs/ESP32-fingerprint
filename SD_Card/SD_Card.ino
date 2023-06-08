#include "FS.h"
#include "SD.h"
#include "SPI.h"

//Declaring SPI Pins for SD Card Module and Creating a New Class for SD SPI
#define SD_MOSI      13
#define SD_MISO      27
#define SD_SCK       14
#define SD_CS_PIN    15

SPIClass SPISD(HSPI);

void setup(){
  Serial.begin(115200);

    //Initialize SD card. Trying this for two times..
  SPISD.begin(SD_SCK, SD_MISO, SD_MOSI);
  Serial.println("Initializing SD card...");

  if (!SD.begin(SD_CS_PIN, SPISD)) {
    Serial.println("Card Mount Failed");
    delay(1000);
    SPISD.begin(SD_SCK, SD_MISO, SD_MOSI);
    if (!SD.begin(SD_CS_PIN, SPISD)) {
      Serial.println("Card Mount Failed Again");
    } else{
      Serial.println("Card OKKkk");
    }
  } else{
  Serial.println("Card OKK");
  }
  delay(10000);
}

void loop(){

}