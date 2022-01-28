//comment comment2

void setup(){
Serial.begin(9600);
Serial.println("CLEARDATA");
Serial.println("LABEL,Date,Time,Data");
Serial.println("RESETTIMER");
pinMode(7, OUTPUT);

}
 int timer = 0;

 int a = 0;
 int max = 0;
 int counter = 0;
 int stopcar = 0;
 int starttime = 0;
 int mincount = 0; 
 int maxcount = 0; 
 int minfind = 1200;
 int maxfind = 0;
void loop(){
int sensorValue = analogRead(A0);
int minprev = sensorValue;
if (minfind > minprev){
  minfind = minprev; 
  mincount = 0;
  digitalWrite(7, HIGH);
  
}
else{
  mincount++;
}

if (mincount > 120){
  digitalWrite(7, LOW);
  if (1010 <= sensorValue){
    maxfind = sensorValue; 
    timer = 9999;
   
  }
Serial.print(","); Serial.println("SCROLLDATA_20");

}
int timer = 0;

int a = 0;
int max = 0;
int counter = 0;
int stopcar = 0;
int starttime = 0;
int mincount = 0;
int maxcount = 0;
int minfind = 1200;
int maxfind = 0;
void loop() {
    int sensorValue = analogRead(A0);
    int minprev = sensorValue;
    if (minfind > minprev) {
        minfind = minprev;
        mincount = 0;
        digitalWrite(7, HIGH);

    } else {
        mincount++;
    }

    if (mincount > 120) {
        digitalWrite(7, LOW);
        if (1010 <= sensorValue) {
            maxfind = sensorValue;
            timer = 9999;
        }
        Serial.print(",");
        Serial.println("SCROLLDATA_20");
    }

    Serial.print("DATA,DATE,TIME,");
    Serial.print(sensorValue);

    Serial.print(",");
    Serial.println(timer++);

    // Serial.println(sensorValue);
    // Serial.println(timer);
    delay(1000);
}
