#include <AccelStepper.h>

// Arduino Mega board
// RAMPS 1.4 SHIELD

#define L_STEP_PIN 54
#define L_DIR_PIN 55
#define L_ENABLE_PIN 38

#define R_STEP_PIN 60
#define R_DIR_PIN 61
#define R_ENABLE_PIN 56

AccelStepper stepperL(AccelStepper::DRIVER, L_STEP_PIN, L_DIR_PIN);
AccelStepper stepperR(AccelStepper::DRIVER, R_STEP_PIN, R_DIR_PIN);

int L_target = 1000;
int R_target = 2000;

void setup()
{  
  Serial.begin(9600);
  
  pinMode(L_ENABLE_PIN , OUTPUT);
  digitalWrite(L_ENABLE_PIN , LOW);

  pinMode(R_ENABLE_PIN , OUTPUT);
  digitalWrite(R_ENABLE_PIN , LOW);
  
  stepperL.setMaxSpeed(800);//1100
  stepperL.setAcceleration(800);
  stepperL.moveTo(L_target);

  stepperR.setMaxSpeed(3200);//1100
  stepperR.setAcceleration(3200);
  stepperR.moveTo(R_target);

}

void loop()
{
    // If at the end of travel go to the other end
    if (stepperL.distanceToGo() == 0){
      stepperL.moveTo( -stepperL.currentPosition() );
      L_target = L_target * -1;
      Serial.println("L-Reached!");
    }
    if (stepperR.distanceToGo() == 0){
      stepperR.moveTo( -stepperR.currentPosition() );
      R_target = R_target * -1;
      Serial.println("R-Reached!");
    }
    
    stepperL.run();
    stepperR.run();
}
