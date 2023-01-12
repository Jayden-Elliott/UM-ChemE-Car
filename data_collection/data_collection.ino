#include <SoftwareSerial.h>
using namespace std;

int i = 0;

void setup() {
    Serial.begin(9600);
    pinMode(7, OUTPUT);
    digitalWrite(7, LOW);
}

void loop() {
    Serial.println(String(millis()) + "," + String(analogRead(A0)));
    delay(10);
}