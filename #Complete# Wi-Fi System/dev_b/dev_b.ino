#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial
HTTPClient http;

const char* ssid="Toey";  //user ไวไฟ
const char* password="tttttttttt";  //รหัสไวไฟ
String key="6282449510203392";  //key
String message;
String id="1";

unsigned long previousMillis = 0;
static const long interval = 1000; 

const int buttonPin[2] = {0,D1};      
int buttonState[2]; 
int lastButtonState[2]; 

int count_log;
int detect;


void connect_serv(){
    if((WiFi.status() == WL_CONNECTED)) {
    http.begin("www.espert.io", 80, "/MySmartphone/send?key="+key+"&message="+message+"");
        int httpCode = http.GET();
        if(httpCode) {
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
            
            if(httpCode == 200) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
            }
        } else {
            USE_SERIAL.print("[HTTP] GET... failed, no connection or no HTTP server\n");
        }
    }
}

void setup() {
  Serial.begin(9600);
  USE_SERIAL.begin(9600);
   WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  pinMode(D1,INPUT);
  pinMode(D6,OUTPUT);
}



void loop() {
buttonState[1] = digitalRead(buttonPin[1]);
if (buttonState[1] != lastButtonState[1]) {
    if (buttonState[1] == HIGH) {
   detect=1;
   digitalWrite(D6,HIGH);
   message="Node_"+id+"_Detect_!";
   Serial.println(message);
   connect_serv();
    }
   delay(50);
    lastButtonState[1] = buttonState[1]; 
  }
          unsigned long currentMillis = millis();
if (currentMillis - previousMillis >= interval) {
  previousMillis = currentMillis;
  if(detect==1){
    count_log+=1;
  }
if(count_log==10 && detect==1){
  digitalWrite(D6,LOW);
  count_log=0;
  detect=0;
  }
  }
}
