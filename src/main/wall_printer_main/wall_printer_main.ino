#include <AccelStepper.h>
#include <Servo.h>

// Arduino Mega board
// RAMPS 1.4 SHIELD

#define L_STEP_PIN 4
#define L_DIR_PIN 11
#define L_ENABLE_PIN 38

#define R_STEP_PIN 5
#define R_DIR_PIN 12
#define R_ENABLE_PIN 56

#define SERVO_PIN 6

AccelStepper stepperL(AccelStepper::DRIVER, L_STEP_PIN, L_DIR_PIN);
AccelStepper stepperR(AccelStepper::DRIVER, R_STEP_PIN, R_DIR_PIN);

Servo sprayServo;  // create servo object to control a servo; twelve servo objects can be created on most boards

int servoPos = 150; // start at 0 so can isn't being sprayed!

boolean motorsActive = false;
boolean sprayComplete = false;

void setup() {

  Serial.begin(9600);
  Serial.println("  REC> Connection ready");

  pinMode(L_ENABLE_PIN , OUTPUT);
  digitalWrite(L_ENABLE_PIN , LOW);

  pinMode(R_ENABLE_PIN , OUTPUT);
  digitalWrite(R_ENABLE_PIN , LOW);
  
  stepperL.setMaxSpeed(3200);//1100
  stepperL.setAcceleration(3200);

  stepperR.setMaxSpeed(3200);//1100
  stepperR.setAcceleration(3200);

  sprayServo.write(servoPos);
  sprayServo.attach(6);
}

String command;

void loop() {

  if(Serial.available() > 0)
  {
    char c = Serial.read();

    if (c == '\n')
    {
//      Serial.println("COMMAND SENT: " + command);
      sprayComplete = false;
      parseCommand(command);
      command = "";
    }
    else
    {
      command += c;
    }
  }

  stepperL.run();
  stepperR.run();
  
  if (stepperL.distanceToGo() == 0 &&  stepperR.distanceToGo() == 0 && motorsActive) {
    Serial.println("#");
    motorsActive = false;
  }
}

String code;
String value;

void parseCommand(String com)
{

  code = com.substring(0, com.indexOf(" "));
  value = com.substring(com.indexOf(" ") + 1);

//  Serial.println(code);
//  Serial.println(value);

  if(code == "SD") {
    stepperL.setCurrentPosition(value.toInt());
    stepperR.setCurrentPosition(value.toInt());
  }
  else if(code == "LM") {
    stepperL.move(value.toInt());
  }
  else if(code == "RM") {
    stepperR.move(value.toInt());
  }
  else if(code == "GP") {
    Serial.println("Left motor @ " + String(stepperL.currentPosition()) + "   Right motor @ " + String(stepperR.currentPosition()));
  }
  else if(code == "BM") {
    stepperL.moveTo(value.substring(value.indexOf("L") + 1, value.indexOf(" ")).toInt());
    stepperR.moveTo(value.substring(value.indexOf("R") + 1).toInt());
    motorsActive = true;
  }
  else if(code == "SS") {
    sprayServo.write(value.toInt());
  }
  else if(code == "BS") {
    sprayServo.write(value.substring(value.indexOf("A") + 1, value.indexOf(" ")).toInt());
    delay(value.substring(value.indexOf("D") + 1, value.indexOf("B") - 1).toInt());
    sprayServo.write(value.substring(value.indexOf("B") + 1).toInt());
    delay(200);
    Serial.println("#");
  }
  else if(code == "?") {
    String position_message = "Pos:";
    position_message = position_message + stepperL.currentPosition();
    position_message = position_message + ",";
    position_message = position_message + stepperR.currentPosition();
    Serial.println(position_message);
  }  
  else if(code == "STOPXY") {
    stepperL.stop();
    stepperR.stop();
    Serial.println("Stop received");
  }
  
  
  
  else
  {
    Serial.println("Command not recognised");
  }
}
