//Timer Library
#include <SimpleTimer.h>

//Setting Up Variables
int t1;
int t2;

//Creating Timer Object
SimpleTimer timer;

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  //Setting Up Timers
  Serial.println("Check");
  timer.setInterval(5000L, CheckMode); //Check the Mode for every 5 Sec
  t1 = timer.setInterval(2000L, ChecktoAddID); //Check the Website for every 2 Sec for a new Fingerprint ID
  t2 = timer.setInterval(2000L, ChecktoDeleteID); //Check the Website for every 2 Sec to Delete Fingerprint ID

}

void loop() {
  // put your main code here, to run repeatedly:
  timer.run();
}

void CheckMode() {
  Serial.println("Check Mode");
}

void ChecktoAddID() {
  Serial.println("Check to Add ID");
}

void ChecktoDeleteID() {
  Serial.println("Check to Delete ID");
}
