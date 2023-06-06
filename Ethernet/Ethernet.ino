//Ethernet Module Library
#include <EthernetENC.h>
#include <EthernetClient.h>

int wifiOrEthernetStatus;

//Creating Ethernet NTP Client Objects
EthernetUDP ethernet_UDP;
unsigned int localPort = 8888;


//Ethernet Module Setting Up
byte mac[] = { 0xDE, 0xDE, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);
IPAddress timeSrvr(216, 239, 35, 0); //Google NTP Client Server for Ethernet
EthernetClient client;


void setup() {

  Serial.begin(115200);
  delay(1000);

  Ethernet.init(5);
  Serial.println("Trying to Connect Ethernet");
  Ethernet.begin(mac, ip);

  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet Hardware was not found.  Sorry, can't run without hardware..");
    wifiOrEthernetStatus = 1;
  }
  if (Ethernet.hardwareStatus() != EthernetNoHardware) {
    Serial.println("Ethernet Hardware Found..");
  }

  delay(5000);
  
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
    wifiOrEthernetStatus = 1; // 1 for WiFi 0 for Ethernet
  }
  if (Ethernet.linkStatus() == LinkON) {
    Serial.println("Ethernet cable is connected.");

    wifiOrEthernetStatus = 0;
    //Start UDP
    ethernet_UDP.begin(localPort);
    Serial.println("Ethernet UDP Start....");

  }
  if (wifiOrEthernetStatus == 1) {
    //Execute Connect to WiFi Function
    Serial.println("CONECING TO WIFI.");
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
