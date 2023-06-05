#include <WiFi.h>
#include <WebServer.h>
#include <AutoConnect.h>

//Fingerprint Scanner Device Token for Each Department
const char *device_token  = "04-001-004";

//Status Check Variables
int portalStatus = 0;

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

void setup() {
  Serial.begin(115200);
  connectToWiFi();

}

void loop() {
  // put your main code here, to run repeatedly:

}

///http://172.217.28.1/_ac

void connectToWiFi() {

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
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
    Serial.println(WiFi.getHostname());
    portalStatus = 1;

//If the ESP32 is in AP mode, disconnects the soft AP and disables the AP mode.
  if (WiFi.getMode() & WIFI_AP) {
      WiFi.softAPdisconnect(true);
      WiFi.enableAP(false);
    }
  }

// failed connection attempt
  if (portalStatus == 0) {
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
