#include <WiFi.h>
#include <WebServer.h>

#include <time.h>
#include <HTTPUpdate.h>
#include <AutoConnect.h>
#include <HTTPClient.h>

//Timer Library
#include <SimpleTimer.h>

//NTP Client and RTC Libraries
#include <NTPClient.h>
#include <WiFiUdp.h>

WebServer Server;

AutoConnect Portal(Server);
AutoConnectConfig Config;

//Creating WiFi NTP Client Objects
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

time_t prevDisplay = 0;
SimpleTimer timer;

//Declaring Web Link as a String (Link = URL + PostData)
String Link;

//Fingerprint Scanner Device Token for Each Department
const char *device_token  = "04-001-444";

//Declaring URL (Computer IP or Server Domain) as a String
int    HTTP_PORT   = 80;
String HTTP_METHOD = "GET";
String httpString = "http://";
char WebHostName[] = "www.botz-svr3.com";
String WebPathName   = "/CrewMate_HRM/deviceManagement_getAllData";


String URL = httpString + WebHostName + ":" + HTTP_PORT + WebPathName;

//Declaring PostData as a String (Fingerprint ID & Token Number will be Sent to Server by Using this Variable)
String PostData;

String FirmwareURL = "http://botz-svr3.com/CrewMate_HRM/FirmwareServlet//opt/CrewMate/Device_Firmware/";
String FirmwareExtension = ".bin";

//Setting Up Variables
int FingerID = 0;
int t1;
int t2;
int rssi;
int signalStength;

//Status Check Variables
int portalStatus = 0;

bool device_Mode = false; //0 for Enrollment 1 for Attendace
bool firstConnect = false;

uint8_t id;
unsigned long previousMillis = 0;

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
  //Config.title = "CM-FSv2 Portal";
  Config.autoReconnect = true;
  Config.apid = "FingerPrint";
  Config.psk = "12345678";
  Config.hostName = device_token;

  Config.portalTimeout = 2000;
  Config.retainPortal = false;
  Portal.config(Config);
  Server.on("/", rootPage);

  Serial.println("Creating portal and trying to connect...");

  if (Portal.begin()) {
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
    //connectedToWiFiMsg();
    portalStatus = 1;

  Serial.println(WiFi.getHostname());

  if (WiFi.getMode() & WIFI_AP) {
      WiFi.softAPdisconnect(true);
      WiFi.enableAP(false);
    }
  }

  if (portalStatus == 0) {
    //hotspotIcon();
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
