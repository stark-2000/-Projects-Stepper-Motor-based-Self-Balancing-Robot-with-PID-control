//IMU Interface:
#include <SoftwareSerial.h>
int RXPin = 6; //Connect TX of GPS to Pin 2
int TXPin = 7; //Connect RX of GPS to Pin 3
SoftwareSerial gpsSerial(RXPin, TXPin);

//Stepper Interface:
//Defines pins numbers
const int dirPin1 = 3;
const int stepPin1 = 2;

const int dirPin2 = 5;
const int stepPin2 = 4;


void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);

  //Stepper Initialisation:
  Serial.println("Intialising Stepper Motor"); 
  pinMode(stepPin1,OUTPUT);
  pinMode(dirPin1,OUTPUT);

  pinMode(stepPin2,OUTPUT);
  pinMode(dirPin2,OUTPUT);

  digitalWrite(dirPin1,HIGH); //Enables the motor to move in a particular direction
  digitalWrite(dirPin2,LOW);
}


int start_time = millis();
void loop() {
  run_stepper(100, stepPin1);
  run_stepper(100, stepPin2);

  if (gpsSerial.available() > 0)
  {
    // int imu_val = map(int(gpsSerial.read()), 90, -90, 0, 180);
    // Serial.println(imu_val);
    // delay(500);

    Serial.println(gpsSerial.read());
    // float val = gpsSerial.read();
    // Serial.println(int(val));
  }
}


int run_stepper(int intervalBetweenSteps, int stepPin){
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(5); //this is the pulse width - trigger
  digitalWrite(stepPin, LOW);
  delayMicroseconds(intervalBetweenSteps);
}

int stop_stepper(int stepPin){
  digitalWrite(stepPin, LOW);
}
