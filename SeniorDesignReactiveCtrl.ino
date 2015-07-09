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
int backwards = 240; // Speed for moving backwards

// Set pins for the bumpers
int frontLeftBump = 13;
int frontRightBump = 12;
int backLeftBump = 11;
int backRightBump = 10;

// Set pins for the ultrasonic sensors
int USTrig = 9;
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
  pinMode(USTrig, OUTPUT);
  
// Set serial baud rate  
  Serial.begin(9600);
}

int USRead(int USEcho){
  long duration, distance;
  
  digitalWrite(USTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(USTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(USTrig, LOW);
  duration = pulseIn(USEcho, HIGH);
  distance = (duration/2) / 29.1;  
  
  if(distance <= 40){
    Serial.print("Left Front: ");
    Serial.println(distance);
    return 1;
    }
  else return 0;
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
    obstacle = USRead(frontUS);
    
// If nothing detected with Ultrasonics, check for bumper contact
    if(obstacle == 0){
      obstacle = digitalRead(frontLeftBump);  
    }  
    Serial.println(obstacle);
    if(obstacle == 1){
      speed = 0;
      analogWrite(rightMotor, speed);
      analogWrite(leftMotor, speed);
    }
  }
  
// Reset Obstacle detection to false  
  obstacle = 0;  
  
  

}

