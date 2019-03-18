
// zoomkat 10-4-10 serial servo test
// type servo position 0 to 180 in serial monitor
// for writeMicroseconds, use a value like 1500
// for IDE 0019 and later
// Powering a servo from the arduino usually DOES NOT WORK.

String readString;
#include <Servo.h> 
Servo myservo;  // create servo object to control a servo 

void setup() {
  Serial.begin(9600);
  myservo.writeMicroseconds(2000); //set initial servo position if desired
  myservo.attach(9);  //the pin for the servo control 
  Serial.println("servo-test-21"); // so I can keep track of what is loaded
}

void loop() {

    myservo.write(180); //for degees 0-180
    delay(2);  
    myservo.write(0); //for degees 0-180
  
}
