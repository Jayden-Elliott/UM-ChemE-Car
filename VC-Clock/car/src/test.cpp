#include <Arduino.h>
#include <SoftwareSerial.h>
#include <math.h>

#define PIN 2

double initalTime;
double lowDelay;
double highDelay;
double t;

double del = 5000;

void changeDelay();

void setup() {
    Serial.begin(9600);
    pinMode(PIN, OUTPUT);
    
    initalTime = millis();
    t = initalTime;
}

//REQUIRES: Create a sin wave with respect to time
//MODIFY: lowDelay, highDelay
void changeDelay(){
  double amp = millis()/1000;
  double value = 5*sin(amp) + 10;
  Serial.print(value);
  Serial.print(" ");
  Serial.println(amp);
  highDelay = value;
}

int changed = 0;
void loop(){
//   digitalWrite(P1, HIGH);
//   digitalWrite(P2, HIGH); 
//   digitalWrite(P3, LOW); 
//   digitalWrite(P4, LOW); 
//   delayMicroseconds(del); 

//   digitalWrite(P1, LOW);
//   digitalWrite(P2, HIGH); 
//   digitalWrite(P3, HIGH); 
//   digitalWrite(P4, LOW); 
//   delayMicroseconds(del);

//   digitalWrite(P1, LOW);
//   digitalWrite(P2, LOW); 
//   digitalWrite(P3, HIGH); 
//   digitalWrite(P4, HIGH); 
//   delayMicroseconds(del);

//   digitalWrite(P1, HIGH);
//   digitalWrite(P2, LOW); 
//   digitalWrite(P3, LOW); 
//   digitalWrite(P4, HIGH); 
//   delayMicroseconds(del);



  // digitalWrite(P4, LOW); 
  // digitalWrite(P3, LOW); 
  // digitalWrite(P2, LOW); 
  // digitalWrite(P1, LOW); 



  // t = millis() % 20;
  // changeDelay();
  // Serial.print(t);
  // Serial.print(" ");
  // Serial.println(highDelay);

  if (t < highDelay){

    if (changed == 0){
      changed = 1;
      changeDelay();
    }
    digitalWrite(PIN, HIGH);
  }
  else {
    digitalWrite(PIN, LOW);
    if (changed == 1){
      changed = 0;
    }
  }

  

}


