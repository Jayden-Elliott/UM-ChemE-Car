#include <SoftwareSerial.h>
using namespace std;


void setup() {
    Serial.begin(9600);
}

void loop() {
    Serial.println(String(millis()) + "," + String(analogRead(A0)));
    delay(10);
}
