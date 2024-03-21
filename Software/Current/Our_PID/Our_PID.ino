//////////////////////////////////////////////////////////////////
//PID Interface:
#include <PID_v1.h> //From https://github.com/br3ttb/Arduino-PID-Library/blob/master/PID_v1.h

/*********Tune these 4 values for your BOT*********/

double setpoint= 88; //set the value when the bot is perpendicular to ground using serial monitor. 

//Read the project documentation on circuitdigest.com to learn how to set these values
double Kp = 21; //Set this first
double Kd = 0.8; //Set this secound
double Ki = 140; //Finally set this 

/******End of values setting*********/

double input, output;
PID pid(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//IMU Interface:
#include <SoftwareSerial.h>
int RXPin = 6; //Connect TX of GPS to Pin 2
int TXPin = 7; //Connect RX of GPS to Pin 3
SoftwareSerial nanoSerial(RXPin, TXPin);

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//Stepper Interface:
//Defines pins numbers
const int dirPin1 = 3;
const int stepPin1 = 2;

const int dirPin2 = 5;
const int stepPin2 = 4;

//////////////////////////////////////////////////////////////////


void setup() {
  Serial.begin(9600);

  Serial.println("Intialising IMU Serial interface..."); 
  nanoSerial.begin(9600);

  //Stepper Initialisation:
  Serial.println("Intialising Stepper Motor..."); 
  pinMode(stepPin1,OUTPUT);
  pinMode(dirPin1,OUTPUT);
  pinMode(stepPin2,OUTPUT);
  pinMode(dirPin2,OUTPUT);
}


void loop() {
  // int data = nanoSerial.read();
  while (nanoSerial.available() > 0){
    // input = data * 180/M_PI + 180;
    input = nanoSerial.read();
    
    //no mpu data - performing PID calculations and output to motors     
    pid.Compute();   

    //Print the value of Input and Output on serial monitor to check how it is working.
    Serial.print(input); Serial.print(" =>"); Serial.println(output);

    if (input>60 && input<110){//If the Bot is falling 
      if (output>0){ //Falling towards front 
        int speed = map(output, 0, 255, 40000, 100);
        Forward(speed); //Rotate the wheels forward 
      }

      else if (output<0){ //Falling towards back
        int speed = map(output, 0, 255, 40000, 100);
        Reverse(speed); //Rotate the wheels backward 
      }
    }

    else //If Bot not falling
      Stop(); //Hold the wheels still

  }
}



void Forward(int intervalBetweenSteps){
  digitalWrite(dirPin1,HIGH);
  digitalWrite(dirPin2,LOW);

  digitalWrite(stepPin1, HIGH);
  delayMicroseconds(5); //this is the pulse width - trigger
  digitalWrite(stepPin1, LOW);
  delayMicroseconds(intervalBetweenSteps);

  digitalWrite(stepPin2, HIGH);
  delayMicroseconds(5); //this is the pulse width - trigger
  digitalWrite(stepPin2, LOW);
  delayMicroseconds(intervalBetweenSteps);
}


void Reverse(int intervalBetweenSteps){
  digitalWrite(dirPin1,LOW);
  digitalWrite(dirPin2,HIGH);

  digitalWrite(stepPin1, HIGH);
  delayMicroseconds(5); //this is the pulse width - trigger
  digitalWrite(stepPin1, LOW);
  delayMicroseconds(intervalBetweenSteps * -1);

  digitalWrite(stepPin2, HIGH);
  delayMicroseconds(5); //this is the pulse width - trigger
  digitalWrite(stepPin2, LOW);
  delayMicroseconds(intervalBetweenSteps * -1);
}


void Stop(){
  digitalWrite(stepPin1, LOW);
  digitalWrite(stepPin2, LOW);
}






