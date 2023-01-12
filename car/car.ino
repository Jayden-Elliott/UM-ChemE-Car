#include <SoftwareSerial.h>
using namespace std;

int last_10[10] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
int rolling_index = 0;
int start_time = 0;
int highest = 0;
int lowest = 1023;
bool peaked = false;
bool bottomed = false;
double speed = 0.64;  // in m/s
double min_mass = 0.1;
double max_mass = 0.3;
double min_dist = 10;  // in m
double max_dist = 30;  // in m
double rxn_time;

void setup() {
    Serial.begin(9600);
    pinMode(7, OUTPUT);
    digitalWrite(7, LOW);
    Serial.println("time,time_since_start,value,average");
}

void loop() {
    int val = analogRead(A0);
    Serial.println(String(millis()) + "," + String(val));
    last_10[rolling_index] = val;
    rolling_index = (rolling_index + 1) % 10;
    int avg = 0;
    for (int x : last_10) {
        avg += x / 10;
    }

    if (!peaked) {
        if (avg > highest) {
            highest = avg;
        } else if (highest > 500 && avg < highest - 30) {
            peaked = true;
            Serial.println("Peak time: " + String(millis()) + ", Peak avg: " + String(val) + ", Highest avg: " + String(highest));
        }
    } else if (!bottomed) {
        if (avg < lowest) {
            lowest = avg;
        } else if (lowest < highest - 50 && avg > lowest + 15) {
            bottomed = true;
            highest = 0;
            start_time = millis();
            Serial.println("Bottom time: " + String(millis()) + ", Bottom avg: " + String(val));
        }
    } else if (millis() - start_time >= 400) {
        if (avg > highest) {
            highest = avg;
        } else if (highest > lowest + 10 && avg < highest - 5) {
            rxn_time = (double)(millis() - start_time);
            Serial.println("End time: " + String(millis()) + ", End avg: " + String(val));
            Serial.println("Time to peak: " + String(rxn_time));
            double mass = (1 / sqrt(rxn_time) - 0.0306) / 0.3276;
            Serial.println("Mass: " + String(mass));
            double distance = min_dist + (max_dist - min_dist) * (mass - min_mass) / (max_mass - min_mass);
            if (distance < min_dist) {
                distance = min_dist;
            }
            if (distance > max_dist) {
                distance = max_dist;
            }
            Serial.println("Distance: " + String(distance));
            double time = distance / speed * 1000;
            Serial.println("Time: " + String(time) + "ms");
            delay(5000);
            Serial.println("Starting");
            digitalWrite(7, HIGH);
            delay(time);
            Serial.println("Stopping");
            digitalWrite(7, LOW);
            delay(999999);
        }
    }
}