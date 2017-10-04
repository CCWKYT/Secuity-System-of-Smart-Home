#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WifiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

void setup() {

Serial.begin(115200);
for (uint8_t t = 4; t > 0; t--) {
Serial.printf("[SETUP] WAIT %d...\n", t);
Serial.flush();
delay(1000);
}
WiFiMulti.addAP("tomm9999", "026166435"); // ssid , password
randomSeed(50);
}
void loop() {
if ((WiFiMulti.run() == WL_CONNECTED)) {
HTTPClient http;
int temp = random(1,20);
String url = "http://192.168.1.42/nodemcu/esp8266mysql/add.php?temp="+String(temp);
Serial.println(url);
http.begin(url); //HTTP

int httpCode = http.GET();
if (httpCode > 0) {
Serial.printf("[HTTP] GET... code: %d\n", httpCode);
if (httpCode == HTTP_CODE_OK) {
String payload = http.getString();
Serial.println(payload);
}
} else {
Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
}
http.end();
}
delay(3000);
}
