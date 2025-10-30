#include <Arduino.h>
#include <SoftwareSerial.h>
#include "CarInfo.cpp"

#define PHOTORESISTOR_PIN_IN A0
#define VALVE_SWITCH_PIN_IN A1 //7
#define MULTIMETER_PIN_OUT 4
#define VALVE_PIN_LIMIT 1015
#define RELAY_PIN_OUT 2

bool measureData();
void data_setup();
void data_loop();
void moveCar();
void wait();
void printDataSummary();
void printCarMove();
float calcDistance(float time_of_biggest_slope);
float calcCarTime(float distance);