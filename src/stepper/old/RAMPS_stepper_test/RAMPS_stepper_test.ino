/*     
 *  For stepper chips found on the RAMPS board
 *  
 *  Based on: Simple Stepper Motor Control Exaple Code by Dejan Nedelkovski, www.HowToMechatronics.com
 */
 
// defines pins numbers
const int stepPin = 54; 
const int dirPin = 55; 
const int enablePin = 38; 
 
void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enablePin,OUTPUT);
  digitalWrite(enablePin,LOW); 
}
void loop() {
  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 200; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(200); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(200); 
  }
  delay(50); // One second delay
  
  digitalWrite(dirPin,LOW); //Changes the rotations direction
  // Makes 400 pulses for making two full cycle rotation
  for(int x = 0; x < 400; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(200);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(200);
  }
  delay(50);
}
