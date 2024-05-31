//scanning networks
#include <ESP8266WiFi.h>
#include <stdlib.h>
#include "scan.h"

int8_t __found;

void initScan(int8_t *found) {
  __found = WiFi.scanNetworks(false, true);
  *found = __found;
}

AccessPoint *scan() {
  AccessPoint *networks = (AccessPoint *)calloc(__found, sizeof(AccessPoint));
  for (int i = 0; i < __found; ++i) {
    // Print SSID and RSSI for each network found
    Serial.print(i + 1);  //Sr. No
    Serial.print(": ");
    Serial.print(WiFi.SSID(i));  //SSID
    networks[i].ssid = WiFi.SSID(i);
    Serial.print(" (");
    Serial.print(WiFi.RSSI(i));  //Signal Strength
    networks[i].power = WiFi.RSSI(i);
    Serial.print(") MAC:");
    Serial.print(WiFi.BSSIDstr(i));
    networks[i].mac = (WiFi.BSSID(i));
    Serial.print((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " Unsecured " : " Secured ");
    networks[i].secured = !(WiFi.encryptionType(i) == ENC_TYPE_NONE);
    networks[i].channel = WiFi.channel(i);
    Serial.println(WiFi.channel());
    delay(10);
  }
  return networks;
}