
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int servoPos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(6);  // attaches the servo on pin # to the servo object
  myservo.write(pos); 
  Serial.begin(9600);
  Serial.setTimeout(20);
  
}

void loop() {
  if(Serial.available()){
    pos = Serial.parseInt();
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    Serial.println("Gone to: " + String(pos));
  }
}
