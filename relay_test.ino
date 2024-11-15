#include <SoftwareSerial.h>
using namespace std;

void setup() {
    Serial.begin(9600);
    pinMode(VALVE_PIN, INPUT);  // valve
    pinMode(RELAY_PIN, OUTPUT);  // relay
    digitalWrite(3, LOW);
}

void loop() {
    delay(10000);
    digitalWrite(RELAY_PIN, HIGH);
    delay(10000);
    digitalWrite(RELAY_PIN, LOW);
}