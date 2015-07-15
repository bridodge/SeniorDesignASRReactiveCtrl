
/*

 Experimenting with the VEX motor libraries. This library is beneficial because 
 it initializes a motor class with parameters specifically targeted at our motors.

 Parameters from the vexMotor class:
 _zeroPoint = 0;        // default zeroPoint
 _deadBand = 5;         // default deadBand
 _fullSpeedCCW = -255;  // counter-clockwise
 _fullSpeedCW = 255;    // clockwise
 _maxPulse = 2000;      // pwm values
 _neutralPulse = 1500;  
 _minPulse = 1000;

 I noticed that with this setup, the wheel will turn full speed forward at +255
 and full speed backwards at -255, which is not what happens in Brian's code.

 The issue I'm having is that only one side is turning on. It seems to be whichever motors
 are declared first (in this code's current state, that would be the left side). It's not a hardware
 issue because Brian's code turns on all of the wheels. In addition, when I switch the pin
 numbers, the wheels on the opposite side will turn. It's very strange.
 
 To run this code, you need the vexMotor libraries. Download them from here:
 https://github.com/sparkfun/vexMotor
 Unzip this to a folder called vexMotor in the your arduino directory's libraries folder
 
 Final note: This code is obviously a WIP, I haven't finished designing the other movement cases.
 For now, I'm just trying to get forward movement, but there's nothing stopping you from putting
 in negative values and moving backwards.

*/

#include <vexMotor.h> // includes the vexMotor library (must also include Servo.h)
#include <Servo.h>    // servo library -- vexMotor relies on the Servo library

//int rightMotors = 3;
//int leftMotors = 5;

int currentCommand = 1;
int currentSpeed = 0;
int newSpeed = 0;

vexMotor leftMotors;
vexMotor rightMotors;

void setup() 
{
  //pinMode(rightMotors, OUTPUT);
  //pinMode(leftMotors, OUTPUT);
  
  leftMotors.attach(3);
  rightMotors.attach(5);
  
  Serial.begin(9600);
}

int validateCommand(int input)
{
  while(input > 4 || input < 1)
  {
      Serial.println("Bad input, please input a command between 1 and 4");
      
      printPrompt();
      
      while(Serial.available() == 0)
      {
      }
      
      input = Serial.parseInt();
  }
  
  return input;
}

int validateSpeed(int input)
{
  while(input > 255 || input < -255)
  {
      Serial.println("Bad input, please input a speed between -255 and 255");
      
      while(Serial.available() == 0)
      {
      }
      
      input = Serial.parseInt();
  }
  
  return input;
}

void printPrompt()
{
  Serial.println();
  Serial.println("*-------------------------------------*");
  Serial.println("1) Move Forward");
  Serial.println("2) Move Backward");
  Serial.println("3) Turn Left");
  Serial.println("4) Turn Right");
  Serial.println();
  Serial.print("Current Command: ");
  Serial.println(currentCommand);
  Serial.print("Current Speed: ");
  Serial.println(currentSpeed); 
  Serial.println("*-------------------------------------*");
  Serial.println();
}

void loop()
{
  int command;
  int input;
  
  printPrompt();
  
  while(Serial.available() == 0)
  {
  }
  
  input = Serial.parseInt();
  command = validateCommand(input);
  Serial.print("Command: ");
  Serial.println(command);
  
  currentCommand = command;
  
  Serial.println("Please enter a speed between -255 and 255"); 
  
  while(Serial.available() == 0)
  {
  }
  
  input = Serial.parseInt();
  newSpeed = validateSpeed(input);
  Serial.print("Speed: ");
  Serial.println(newSpeed);
  
  currentSpeed = newSpeed;
  
  switch(command)
  {
  case 1:
    Serial.print("Moving forward at a speed of ");
    Serial.println(newSpeed);
    //analogWrite(rightMotors, newSpeed);
    //analogWrite(leftMotors, newSpeed);
    rightMotors.write(newSpeed);
    leftMotors.write(newSpeed);
    break;
  case 2:
    Serial.print("Moving backward at a speed of ");
    Serial.println(newSpeed);
    break;
  case 3:
    Serial.print("Turning right at a speed of ");
    Serial.println(newSpeed);
    break;
  case 4:
    Serial.print("Turning left at a speed of ");
    Serial.println(newSpeed);
    break;
  } 
}


