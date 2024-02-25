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

// Function prototype
void TurnOnPump();

void setup() {
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Forward, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);
  myservo.attach(13);
  myservo.write(90);

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

  if (forwardValue == HIGH) {
    // Move forward if no obstacle ahead
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    analogWrite(ENA1, 180);
    digitalWrite(LM1,LOW);
    digitalWrite(LM2, HIGH);
    analogWrite(ENA2, 180);
    delay(200);
  }  
  if (leftValue == HIGH) {
    // Turn left if obstacle detected on the left
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    analogWrite(ENA1, 255);
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    analogWrite(ENA2, 255);
    delay(300);
  } 
  if (rightValue == HIGH) {
    // Turn right if obstacle detected on the right
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2,LOW);
    analogWrite(ENA1, 255);
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    analogWrite(ENA2, 255);
    delay(300);
  }
  if (forwardValue == HIGH && rightValue == HIGH && leftValue == HIGH) {
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
  digitalWrite(pump,HIGH);
  delay(500); //to give the pump chance to startup

  for(int i = 50; i <= 130 ; i++){
    myservo.write(i);
    delay(10);
  }
  for(int i = 130; i >= 50 ; i--){
    myservo.write(i);
    delay(10);                        //so that servo makes 2 cycles
  }
  for(int i = 50; i <= 130 ; i++){
    myservo.write(i);
    delay(10);
  }
  for(int i = 130; i >= 50 ; i--){
    myservo.write(i);
    delay(10);
  }

  digitalWrite(pump,LOW);
  myservo.write(90);
}
