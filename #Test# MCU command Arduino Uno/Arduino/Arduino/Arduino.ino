
#include <SoftwareSerial.h>

SoftwareSerial ArduinoSerial(3, 2); // RX, TX
void setup() {
Serial.begin(115200);
ArduinoSerial.begin(4800);

pinMode(13, OUTPUT);
}
void loop() {
while (ArduinoSerial.available() > 0) {
float val = ArduinoSerial.parseFloat();
if (ArduinoSerial.read() == '\n') {
if (val == 10) {
digitalWrite(13, 1);
} else if (val == 11) {
digitalWrite(13, 0);
}
Serial.println(val);
}
}
delay(100);
}
