#include <SoftwareSerial.h>
using namespace std;

int value_buffer[120];
int time_buffer[120];
float slope_buffer[120];
int window_size = 120;
float value_avg = 0;
float slope_avg = 0;
int index = 0;
float biggest_slope = 0;
int valve_open_time = 0;

// Calibration Coefficients
float a = -284.99;
float b = -52.662;
float c = 1.1882;
float min_mass = 1.5;  // g
float max_mass = 3.5;  // g
float speed = 0.319;  // m/s

int PHOTORESISTOR_PIN = A0;
int VALVE_PIN = 2;
int RELAY_PIN = 3;

void setup() {
    Serial.begin(9600);
    pinMode(VALVE_PIN, INPUT);  // valve
    pinMode(RELAY_PIN, OUTPUT);  // relay
    digitalWrite(3, LOW);

    // fill array with values
    while (index < window_size) {
        value_buffer[index] = analogRead(PHOTORESISTOR_PIN);
        time_buffer[index] = millis();
        slope_buffer[index] = 0;
        index++;
        delay(10);
    }
    index = 0;

    for (int i = 0; i < window_size; i++) {
        // value_avg += value_buffer[i];
        slope_avg += slope_buffer[i];
    }
    // value_avg /= window_size;
    slope_avg /= window_size;
    Serial.println("Starting recording data");
}

void loop() {
    if (digitalRead(VALVE_PIN) != HIGH && valve_open_time == 0) {
        return;
    }

    if (valve_open_time == 0) {
        valve_open_time = millis();
        Serial.println("Valve Opened");
    }

    long loop_start_time = millis();
    int value = analogRead(PHOTORESISTOR_PIN);
    long time = millis();
    float slope = (float(value) - float(value_buffer[index])) / (float(time) - float(time_buffer[index])) * 1000.0;

    // value_avg += float(value - value_buffer[index]) / window_size;
    slope_avg += (slope - slope_buffer[index]) / window_size;
    value_buffer[index] = value;
    time_buffer[index] = time;
    slope_buffer[index] = slope;

    if (value < 950) {
        if (slope_avg < biggest_slope) {
            biggest_slope = slope_avg;
        }

        if ((abs(slope_avg) < 0.08 && loop_start_time - valve_open_time > 25000) || loop_start_time - valve_open_time > 60000) {
            Serial.println("Stopped recording data");
            time_car();
        }
    }

    // Serial.println(String(time) + "," + String(value) + "," + String(slope) + "," + String(slope_avg) + "," + String(biggest_slope) + "," + String(value_avg));
    Serial.println(String(time) + "," + String(value));

    /* String str = "";
    for (int i = 0; i < 50; ++i) {
      str += String(slope_buffer[i]) + " ";
    }
    Serial.println(str); */

    index = (index + 1) % window_size;
    // Serial.println(index);
    if (millis() - loop_start_time < 11) {
      delay(11 - (millis() - loop_start_time));
    }
}

void time_car() {
    float x = biggest_slope / 1000;
    float mass = a * x * x + b * x + c;
    float distance = 15 + (mass - min_mass) / (max_mass - min_mass) * 15;
    long time = long(distance / speed * 1000);  // ms
    Serial.println("Biggest Slope: " + String(biggest_slope));
    Serial.println("Mass: " + String(mass));
    Serial.println("Distance: " + String(distance));
    Serial.println("Time: " + String(time) + "ms");

    digitalWrite(RELAY_PIN, HIGH);
    delay(time);
    digitalWrite(RELAY_PIN, LOW);
    delay(999999);
}