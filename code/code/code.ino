//WIFI library
#include <WiFi.h>
#include <WebServer.h>
#include <AutoConnect.h>

//OLED library
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//Fingerprint Scanner Device Token for Each Department
const char *device_token  = "04-001-004";

//Status Check Variables
int portalStatus = 0;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//sets up the necessary objects for using the AutoConnect library with an instance of the WebServer class.
WebServer Server;
AutoConnect Portal(Server);
AutoConnectConfig Config;

void rootPage() {
  String  content =
    "<html>"
    "<head>"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
    "<script type=\"text/javascript\">"
    "setTimeout(\"location.reload()\", 5000);"
    "</script>"
    "</head>"
    "<body>"
    "<h2 align=\"center\" style=\"color:black;margin:20px;\">FINGERPRINT SCANNER WIFI SETUP</h2>"

    "<p></p><p style=\"padding-top:15px;text-align:center\">" AUTOCONNECT_LINK(COG_24) "</p>"
    "</body>"
    "</html>";
  Server.send(200, "text/html", content);
}

void printOLED(String text, int time){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println(text);
  display.display();
  delay(time);
}

void setup() {
  Serial.begin(115200);

  //Test OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // infinity loop
  }

  delay(2000);

  printOLED("Hellow", 1000);

  connectToWiFi();

}

void loop() {
  // put your main code here, to run repeatedly:

}

///http://172.217.28.1/_ac

void connectToWiFi() {

  printOLED("Wifi", 1000);

  Config.autoReconnect = true; //the library will automatically attempt to reconnect to a previously configured WiFi network if the connection is lost.
  Config.apid = "FingerPrint";
  Config.psk = "12345678";
  Config.hostName = device_token;
  Config.portalTimeout = 2000; //captive portal will be active before it times out. If the user does not connect to a WiFi network within this timeout period, the captive portal will close.
  Config.retainPortal = false; //captive portal page will be cleared after the device successfully connects to the Wi-Fi network.
  Portal.config(Config);
  Server.on("/", rootPage);

  Serial.println("Creating portal and trying to connect...");

//AutoConnect portal has successfully connected to a WiFi network.
  if (Portal.begin()) {
    printOLED("Conected", 1000);
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
    Serial.println(WiFi.getHostname());
    portalStatus = 1;

//If the ESP32 is in AP mode, disconnects the soft AP and disables the AP mode.
  if (WiFi.getMode() & WIFI_AP) {
      printOLED("AP turnoffed", 1000);
      WiFi.softAPdisconnect(true);
      WiFi.enableAP(false);
    }
  }

// failed connection attempt
  if (portalStatus == 0) {
    printOLED("no wifi", 1000);
    Config.portalTimeout = 120000;
    Portal.config(Config);
    if (Portal.begin()) {
      portalStatus = 1;
      Serial.println("WiFi connected: " + WiFi.localIP().toString());
      Serial.println(WiFi.getHostname());

      if (WiFi.getMode() & WIFI_AP) {
        WiFi.softAPdisconnect(true);
        WiFi.enableAP(false);
      }
    }

  }

  delay(1000);
}
