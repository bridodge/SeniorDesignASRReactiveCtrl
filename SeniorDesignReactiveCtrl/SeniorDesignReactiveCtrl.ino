/* Autonomous Sentry Robot
   Senior Design II Summer 2015
   Group 9
   Brian Dodge
   Nick Musco
   Trevor Roman
   
   Reactive Robotic Control
   This promgram will implement obstacle avoidance while receiving
   movement commands from the Deliberative Control System via serial
   input.
   When an obstacle has been detected, the robot will reverse its course
   for a short distance and then stop.  It will also send a flag back to the
   Deliberative Control System

*/

int rightMotor = 3;  // Right Motor connected to digital pin 3 for PWM
int leftMotor = 5;  // Left Motor connected to digital pin 5 for PWM

int forward = 100;  // Speed for moving forward
int backwards = 240; // Speed for moving backward

// Pins for the bumpers
int frontLeftBump = 13;
int frontRightBump = 12;
int backLeftBump = 11;
int backRightBump = 10;

// Pins for the ultrasonic sensors
int frontTrig = 4;
int backTrig = 9;
int frontUS = 8;
int backUS = 7;

// Set obstacle to false
int obstacle = 0;


void setup() {
// Set motor pins as output  
  pinMode(rightMotor, OUTPUT);
  pinMode (leftMotor, OUTPUT);

// Set bump sensor pins as input
  pinMode( frontLeftBump, INPUT);
  pinMode( frontRightBump, INPUT);
  pinMode( backLeftBump, INPUT);
  pinMode( backRightBump, INPUT);
  
// Set Ultrasonic Sensors Echo pins as input
  pinMode( frontUS, INPUT);
  pinMode( backUS, INPUT);

// Set Ultrasonic Sensor Trig pins as output
  pinMode(frontTrig, OUTPUT);
  pinMode(backTrig, OUTPUT);
  
// Set serial baud rate  
  Serial.begin(9600);
}

// USRead will take the pin for the Ultrasonic Echo, send out a pulse
// and determine the distance to an obstacle, if there is one.  It will then
// return 1 if and obstacle has been detected, 0 otherwise
int USRead(int USEcho, int USTrig){
// Duration of the pulse 
  long duration;
// Distance to an object
  long distance;
// Pulse the Ultrasonic Sensor
  digitalWrite(USTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(USTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(USTrig, LOW);
  duration = pulseIn(USEcho, HIGH);
  distance = (duration/2) / 29.1;  
  
 // Determine if an object is detected or not
  if(distance <= 10){
 // FOR DEBUGGING: Display distance to object   
    Serial.print("Distance: ");
    Serial.println(distance);
    Serial.println("US!!!");
    return 1;
    }
  else return 0;
}

int bumped(){
  int bump = 0;
// Check Front Left Bumper, if there is an obstacle, return 1
  bump = digitalRead(frontLeftBump);
  if(bump == 1){
    Serial.println("BUMP!!");
    return bump;
  }
// Check Front Right Bumper, if there is an obstacle, return 1
  bump = digitalRead(frontRightBump);
  if(bump == 1){
    Serial.println("BUMP!!");
    return bump;
  }
// Check Back Left Bumper, if there is an obstacle, return 1
  bump = digitalRead(backLeftBump);
  if(bump == 1){
    Serial.println("BUMP!!");
    return bump;
  }
// Check Back Right Bumper, if there is an obstacle, return 1
  bump = digitalRead(backRightBump);
  if(bump == 1){
    Serial.println("BUMP!!");
    return bump;
  }
  else return bump;
    
}

void loop() {
  
  int speed;

// Loop for movement, when an obstacle has been detected, the robot will stop  
  while(!obstacle){
    
    if (Serial.available()){
//  FOR DEBUGGING: User input to control motor speed   
      speed = Serial.parseInt();
      if (speed >= 0 && speed <= 255){
        analogWrite(rightMotor, speed);
        analogWrite(leftMotor, speed);
      }
    }
// First Check for long range obstacles with Ultrasonic Sensor
// Check the front Ultrasonic first, if no obstacle, next check the 
// back Ultrasonic
    obstacle = USRead(frontUS, frontTrig);
    if(obstacle == 0)
      obstacle = USRead(backUS, backTrig);
    
// If nothing detected with Ultrasonics, check for bumper contact
    if(obstacle == 0){
      obstacle = bumped();  
    }
// FOR DEBUGGING: Print obstacle state    
    Serial.println(obstacle);

// IF an obstacle is detected, turn off the motors    
    if(obstacle == 1){
      speed = 0;
      analogWrite(rightMotor, speed);
      analogWrite(leftMotor, speed);
    }
  }
  
// Reset Obstacle detection to false  
  obstacle = 0;  
}

