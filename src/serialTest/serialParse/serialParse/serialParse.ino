void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

//  pinMode(3, OUTPUT); //example
}

String command;

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
  {
    char c = Serial.read();

    if (c == 'X')
    {
      command += c;
      Serial.println("COMMAND SENT: " + command);
      parseCommand(command);
      command = "";
    }
    else
    {
      command += c;
    }
  }
}

void parseCommand(String com)
{
  String part1;
  String part2;

  //PINON 3
  //PINOFF 3

  String leftMotorSteps = com.substring(com.indexOf("L") + 1, com.indexOf("R"));
  String rightMotorSteps = com.substring(com.indexOf("R") + 1, com.indexOf("A"));
  String setServoAngle = com.substring(com.indexOf("A") + 1, com.indexOf("D"));
  String sprayDuration = com.substring(com.indexOf("D") + 1, com.indexOf("B"));
  String rtnServoAngle = com.substring(com.indexOf("B") + 1, com.indexOf("X"));

  Serial.println(leftMotorSteps);
  Serial.println(rightMotorSteps);
  Serial.println(setServoAngle);
  Serial.println(sprayDuration);
  Serial.println(rtnServoAngle);
  
  if(part1.equalsIgnoreCase("pinon"))
  {
    int pin = part2.toInt();
    //do  sotmething digitalWrite(pin, HIGH)
    Serial.println("PIN ON");
    
  }
  else if(part1.equalsIgnoreCase("pinoff"))
  {
    int pin = part2.toInt();
    //do  sotmething digitalWrite(pin, HIGH)
    Serial.println("PIN OFF");
  }
  else
  {
    Serial.println("COMMAND NOT RECOGNISED");
  }
}

