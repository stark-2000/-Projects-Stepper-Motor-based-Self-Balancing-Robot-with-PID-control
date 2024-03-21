#include <AccelStepper.h>

//Define pin connections
// const int dirPin = D1;
// const int stepPin = D2;

const int dirPin = 3;
const int stepPin = 2;

//Define motor interface type
#define motorInterfaceType 1

//Creates an instance
AccelStepper myStepper(motorInterfaceType, stepPin, dirPin);

//Range of Stepper Speed - 30 to 40,000
void setup() {
  myStepper.setMaxSpeed(30000.0);
	myStepper.setSpeed(30000.0);
}

void loop() {
  myStepper.runSpeed();
}