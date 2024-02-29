#include <Servo.h>

Servo myservo;

#define Left 2      // left sensor
#define Right 3     // right sensor
#define Forward 4   // front sensor
#define LM1 6       // left motor
#define LM2 7       // left motor
#define RM1 8       // right motor
#define RM2 9       // right motor
#define ENA1 5      // enable pin for motor 13
#define ENA2 11     // enable pin for motor 2
#define pump 10
//#define modeSwitch 13 // switch to toggle between manual and automatic modes

bool AutoMode = false;
  int fire = false ;
  char mode ;

void forward() {
  analogWrite(ENA1, 100);
  analogWrite(ENA2, 100);
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
}

void backward() {
  analogWrite(ENA1, 100);
  analogWrite(ENA2, 100);
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
}

void right() {
  analogWrite(ENA1, 100);
  analogWrite(ENA2, 80);
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);


}

void left() {
  analogWrite(ENA1, 80);
  analogWrite(ENA2, 100);
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
}

void stop() {
  analogWrite(ENA1, 0);
  analogWrite(ENA2, 0);
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
}

void TurnOnPump() {
   digitalWrite(pump, HIGH);
bool x = digitalRead(pump);
  
  if (x==HIGH){
    Serial.println("mmmmmmmmmmmmmmmmmm");
  }
  // digitalWrite(pump, HIGH);
  //delay(500);

  for (int i = 50; i <= 130; i++) {
    myservo.write(i);
    delay(10);
  }
  for (int i = 130; i >= 50; i--) {
    myservo.write(i);
    delay(10);
  }
  for (int i = 50; i <= 130; i++) {
    myservo.write(i);
    delay(10);
  }
  for (int i = 130; i >= 50; i--) {
    myservo.write(i);
    delay(10);
  }
  
  //digitalWrite(pump, LOW);
  myservo.write(90);
  fire = false;
}

void setup() {
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Forward, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT );
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(ENA1, OUTPUT);
   pinMode(ENA2, OUTPUT);

  //pinMode(modeSwitch, INPUT_PULLUP); // Set modeSwitch pin as INPUT_PULLUP
  
  myservo.attach(12);
  myservo.write(90);

  Serial.begin(9600);
}

// void ManualMode() {
//  // if (Serial.available()) {
//     char command = Serial.read();
//     switch (command) {
//       case 'F':
//         forward();
//         break;
//       case 'B':
//         backward();
//         break;
//       case 'R':
//         right();
//         break;
//       case 'L':
//         left();
//         break;
//       case 'S':
//         stop();
//         break;
//       case 'P':
//         TurnOnPump();
//         break;
//     }
//   }

//}

void AutonomousMode() {
  int leftValue = digitalRead(Left);
  int rightValue = digitalRead(Right);
  int forwardValue = digitalRead(Forward);
  Serial.println("automode is onnnnnn");

  if (forwardValue == 0 && rightValue == 1 && leftValue == 1) {
    forward();
    fire = true ;
    delay(300);
    Serial.print("iam in the cursed function !!!!!!!!!!!!!");
  }
  else if (leftValue == 0 && rightValue == 1 && forwardValue == 1) {
  left();
  delay(300);
    Serial.print("INSIDE LEFT !!!!!!!!!!!!!");

  }
  else if (leftValue == 1 && rightValue == 0 && forwardValue == 1) {
  right();
  delay(300);

  }
  else if (forwardValue == 1 && rightValue == 1 && leftValue == 1) {
    stop();
    // TurnOnPump();
  }
  while(fire){
    stop();
    TurnOnPump() ;
  }
}



void loop() {
  if (Serial.available()) {
     mode = Serial.read();
    // if (mode == 'M') {
    //   AutoMode = false;
    if (mode == 'F' || mode=='R' || mode == 'B' ||  mode == 'L' ||  mode == 'S' || mode == 'P' ) {
      switch (mode) {
        case 'F':
          forward();
          break;
        case 'B':
          backward();
          break;
        case 'R':
          right();
          break;
        case 'L':
          left();
          break;
        case 'S':
          stop();
          break;
        case 'P':
          TurnOnPump();
          break;
          }
} // Set manual mode
    else if (mode == 'A') {
      AutoMode = true;  // Set automatic mode
    }
  }

  if (AutoMode) {
    AutonomousMode();
  }
  //  else {
  //   ManualMode();
  // }
  
}

