#include <Servo.h>

Servo myservo;

#define Left 2      // left sensor
#define Right 3     // right sensor
#define Forward 4   // front sensor
#define LM1 6       // left motor
#define LM2 7       // left motor
#define RM1 8       // right motor
#define RM2 9       // right motor
#define ENA1 5      // enable pin for motor 1
#define ENA2 11     // enable pin for motor 2
#define pump 10

bool AutoMode = true;

void setup() {
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Forward, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);

  Serial.begin(9600); 
}

void loop() {
  if (Serial.available()) { 
    char command = Serial.read(); 
    if (command == 'A') {
      AutoMode = true;
    } else if (command == 'M') {
      AutoMode = false;
    }
  }
  
  if (AutoMode) {
    AutonomousMode();
  } else {
    ManualMode();
  }
  delay(100);
}

void ManualMode() {
  //  manual mode 
}

void AutonomousMode() {
  int leftValue = digitalRead(Left);
  int rightValue = digitalRead(Right);
  int forwardValue = digitalRead(Forward);

  if(forwardValue == HIGH){
    analogWrite(ENA1, 128);
    analogWrite(ENA2, 128);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
  }
  if(leftValue == HIGH){
    analogWrite(ENA1, 255);
    analogWrite(ENA2, 255);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
  }
  if(rightValue == HIGH){
    analogWrite(ENA1, 255);
    analogWrite(ENA2, 255);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
  }
  if(forwardValue == HIGH && rightValue == HIGH && leftValue == HIGH){
    analogWrite(ENA1, 0);
    analogWrite(ENA2, 0);
    digitalWrite(RM1,LOW);
    digitalWrite(RM2,LOW);
    digitalWrite(LM1,LOW);
    digitalWrite(LM2,LOW);
    TurnOnPump();
  }
}

void TurnOnPump() {
  // Code to turn on the pump
}
