///////FINAL WORKING CODE//////////////////

//Defines pins numbers
const int dirPin1 = 3;
const int stepPin1 = 2;

const int dirPin2 = 5;
const int stepPin2 = 4;

int customDelay; //Defines variables
int intervalBetweenSteps = 200;
 
void setup() {
  //Sets the three pins as Outputs
  pinMode(stepPin1,OUTPUT);
  pinMode(dirPin1,OUTPUT);

  pinMode(stepPin2,OUTPUT);
  pinMode(dirPin2,OUTPUT);

  digitalWrite(dirPin1,HIGH); //Enables the motor to move in a particular direction
  digitalWrite(dirPin2,LOW);

  Serial.begin(9600);
}

//Range of Stepper Speed - 100 to 30,000
void loop() {
  //intervalBetweenSteps = speedUp(); //Gets custom delay values from the custom speedUp function
  
  int current_time = 0;
  int start_time = millis();

  while(current_time - start_time < 20000)
  {
    run_stepper(100, stepPin1);
    run_stepper(100, stepPin2);

    current_time = millis();
  }

  stop_stepper(stepPin1);
  stop_stepper(stepPin2);

  delay(5000);
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


//Function for reading the Potentiometer
int speedUp() {
  int customDelay = analogRead(A0); //Reads the potentiometer
  Serial.println(customDelay);
  int newCustom = map(customDelay, 0, 1020, 9000, 12000); //Converts the read values of the potentiometer from 0 to 1023 into desired delay values
  Serial.println(newCustom);
  return newCustom;  
}

