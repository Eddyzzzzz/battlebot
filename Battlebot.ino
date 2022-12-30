// #include <Adafruit_MotorShield.h>

// Adafruit_MotorShield MotorShield = Adafruit_MotorShield();

// Adafruit_DCMotor *leftMotor = MotorShield.getMotor(1);

// Adafruit_DCMotor *rightMotor = MotorShield.getMotor(2);

// Adafruit_DCMotor *weapon = MotorShield.getMotor(3);

// #define CHANNEL1 11 // Right stick - Horizontal - turning left / right
// #define CHANNEL2 10 // Right stick - Vertical - moving forward / backward
// #define CHANNEL3 9 // Left stick - Vertical - weapon spin

// // int variables for the values being read from the transmitter
// int c1;
// int c2;
// int c3;

// // Read the number of a specified channel and map the reading to the provided range
// // If the channel is off, return the default value
// int readChannel(int channelInput, int mapLower, int mapUpper, int defaultValue){
//   int ch = pulseIn(channelInput, HIGH, 30000); // Gets length of HIGH pulse, times out after 30000 useconds
//   if (ch < 100) return defaultValue; // If less than 100 microseconds, not a significant pulse
//   return map(ch, 1000, 2000, mapLower, mapUpper); // Map the vaule to the provided min/max
// }

// void setup() {
//   Serial.begin(9600);

//     // Set up the pins for the 6 channels
//   pinMode(CHANNEL1, INPUT);
//   pinMode(CHANNEL2, INPUT);
//   pinMode(CHANNEL3, INPUT);

//   if (!MotorShield.begin()) {   // if the MotorShield hasn't been detected      
//     Serial.println("Could not find Motor Shield. Check wiring.");
//     while (1); // hang
//   }
 
//  }

// void loop() {
//   // Read the values from each channel, map them all from -255 to 255 with default value of 0
//   c1 = readChannel(CHANNEL1, -255, 255, 0);
//   c2 = readChannel(CHANNEL2, -255, 255, 0);
//   c3 = readChannel(CHANNEL3, -255, 255, 0);

//   //Output the received values
//   Serial.print("Right_Stick_Horizontal:");
//   Serial.print(c1);
//   Serial.print(",   ");
//   Serial.print("Right_Stick_Vertical:");
//   Serial.print(c2);
//   Serial.print(",   ");
//   Serial.print("Left_Stick_Vertical:");
//   Serial.println(c3);
//   delay(500); // Wait for 1/4 second before looping again

//   if (c2 > -30 and c2 < 30) {
//     stopMotors();
//   } else if (c2 > 30) {
//     if (c1 > -30 and c1 < 30) {
//       driveForward(c2);
//     } else if (c1 > 30) {
//       turnRightfor(c2);
//     } else if (c1 < -30) {
//       turnLeftfor(c2);
//     }
//   } else if (c2 < -30) {
//     if (c1 > -30 and c1 < 30) {
//       driveBackward(-c2);
//     } else if (c1 > 30) {
//       turnRightback(-c2);
//     } else if (c1 < -30) {
//       turnLeftback(-c2);
//     }
//   } 

//   if (c3 > -100 and c3 < 100) {
//     stopWeapon();
//   } else if (c3 > 100) {
//     weaponSpinfor(c3);
//   } else if (c3 < -100) {
//     weaponSpinback(-c3);
//   }

// }

// void stopMotors() {
//   leftMotor->run(RELEASE);
//   rightMotor->run(RELEASE);
//   // Serial.println("stop.");
//   // delay(250);
// }

// void driveForward(int input) {
//   rightMotor->setSpeed(input - 10);
//   leftMotor->setSpeed(input - 10);
//   rightMotor->run(FORWARD);
//   leftMotor->run(BACKWARD); 
// }

// void driveBackward(int input) {
//   rightMotor->setSpeed(input - 10);
//   leftMotor->setSpeed(input - 10);
//   rightMotor->run(BACKWARD);
//   leftMotor->run(FORWARD); 
// }

// void turnRightfor(int input) {
//   rightMotor->setSpeed(input - 25);
//   leftMotor->setSpeed(input);
//   rightMotor->run(FORWARD);
//   leftMotor->run(BACKWARD); 
// }

// void turnLeftfor(int input) {
//   rightMotor->setSpeed(input);
//   leftMotor->setSpeed(input - 25);
//   rightMotor->run(FORWARD);
//   leftMotor->run(BACKWARD); 
// }

// void turnRightback(int input) {
//   rightMotor->setSpeed(input - 25);
//   leftMotor->setSpeed(input);
//   rightMotor->run(BACKWARD);
//   leftMotor->run(FORWARD); 
// }

// void turnLeftback(int input) {
//   rightMotor->setSpeed(input);
//   leftMotor->setSpeed(input - 25);
//   rightMotor->run(BACKWARD);
//   leftMotor->run(FORWARD); 
// }

// void stopWeapon() {
//   weapon->run(RELEASE);
//   weapon->run(RELEASE);
// }

// void weaponSpinfor(int input) {
//   weapon->setSpeed(input - 10);
//   weapon->run(FORWARD);
// }

// void weaponSpinback(int input) {
//   weapon->setSpeed(input - 10);
//   weapon->run(BACKWARD);
// }

// Tufts Robotics Club Radio Transmitter Workshop Fall 2022 Part 2
// Using the radio controller to drive motors
#include <Adafruit_MotorShield.h>

// Define which pin numbers we'll use for the different channels
// This is for the default mapping - can be changed to use switches instead
#define CHANNEL1 11 // Right stick - Horizontal
#define CHANNEL2 10 // Right stick - Vertical
// #define CHANNEL3 9 // Left stick - Vertical
// #define CHANNEL4 6 // Left stick - Horizontal
// #define CHANNEL5 5 // VRA
// #define CHANNEL6 3 // VRB

// int variables for the values being read from the right stick
int verticalValue;
int horizontalValue;
// int weaponValue;

// defining the deadzone for driving control
int deadZone = 30;

// int variable for the speed of a motor
int motorSpeed;

// Create the motor shield object 
Adafruit_MotorShield MotorShield = Adafruit_MotorShield();

// Select which 'ports' M1, M2, M3 or M4. In this case, M1 and M2
Adafruit_DCMotor *leftMotor = MotorShield.getMotor(1);
Adafruit_DCMotor *rightMotor = MotorShield.getMotor(2);
// Adafruit_DCMotor *weapon = MotorShield.getMotor(3);

// Read the number of a specified channel and map the reading to the provided range
// If the channel is off, return the default value
int readChannel(int channelInput, int mapLower, int mapUpper, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000); // Gets length of HIGH pulse, times out after 30000 useconds
  if (ch < 100) return defaultValue; // If less than 100 microseconds, not a significant pulse
  return map(ch, 1000, 2000, mapLower, mapUpper); // Map the vaule to the provided min/max
}

void setup() {
  Serial.begin(9600);
  Serial.println("Radio Workshop part 2");

  if (!MotorShield.begin()) {   // if the MotorShield hasn't been detected      
    Serial.println("Could not find Motor Shield. Check wiring.");
    // while (1); // hang
  }
  Serial.println("Motor Shield found.");

  // Set up the pins for the two channels for the right joystick
  pinMode(CHANNEL1, INPUT);
  pinMode(CHANNEL2, INPUT);
  // pinMode(CHANNEL3, INPUT);
  
  Serial.println("Setup complete!");
}

void loop() {
  // Read the values from the two channels, map them all from -255 to 255 with default value of 0
  // Only using the right stick to drive
  horizontalValue = readChannel(CHANNEL1, -255, 255, 0);
  verticalValue = readChannel(CHANNEL2, -255, 255, 0);
  // weaponValue = readChannel(CHANNEL3, -255, 255, 0);
  motorSpeed = sqrt(verticalValue*verticalValue + horizontalValue*horizontalValue)/sqrt(2);

  // Moving the joystick to the left and down are negative values
  
  //forward right
  if (verticalValue > deadZone && horizontalValue > deadZone)
  {
    Serial.println("Forward right");
    // rightMotor->setSpeed(motorSpeed);
    // leftMotor->setSpeed(motorSpeed + horizontalValue);
    rightMotor->setSpeed(200);
    leftMotor->setSpeed(250);
    rightMotor->run(FORWARD);
    leftMotor->run(BACKWARD);     
  }
  
  // forward left
  else if (verticalValue > deadZone && horizontalValue < -deadZone)
  {
    Serial.println("Forward left");
    // rightMotor->setSpeed(motorSpeed + horizontalValue);
    // leftMotor->setSpeed(motorSpeed);
    rightMotor->setSpeed(250);
    leftMotor->setSpeed(200);
    rightMotor->run(FORWARD);
    leftMotor->run(BACKWARD);  
  }
  
  // forward
  else if (verticalValue > deadZone && horizontalValue > -deadZone && horizontalValue < deadZone)
  {
    Serial.println("Forward");
    // rightMotor->setSpeed(motorSpeed);
    // leftMotor->setSpeed(motorSpeed);
    rightMotor->setSpeed(250);
    leftMotor->setSpeed(250);
    rightMotor->run(FORWARD);
    leftMotor->run(BACKWARD);  
  }

  //back right
  else if (verticalValue < -deadZone && horizontalValue > deadZone)
  {
    Serial.println("Back right");
    // rightMotor->setSpeed(motorSpeed);
    // leftMotor->setSpeed(motorSpeed + horizontalValue);
    rightMotor->setSpeed(200);
    leftMotor->setSpeed(250);
    rightMotor->run(BACKWARD);
    leftMotor->run(FORWARD);
  }
  
  // back left
  else if (verticalValue < -deadZone && horizontalValue < -deadZone)
  {
    Serial.println("Back left");
    // rightMotor->setSpeed(motorSpeed + horizontalValue);
    // leftMotor->setSpeed(motorSpeed);
    rightMotor->setSpeed(250);
    leftMotor->setSpeed(200);
    rightMotor->run(BACKWARD);
    leftMotor->run(FORWARD);  
  }

    // backwards
  else if (verticalValue < -deadZone && abs(horizontalValue) < deadZone)
  {
    Serial.println("Backwards");
    // rightMotor->setSpeed(motorSpeed);
    // leftMotor->setSpeed(motorSpeed);
    rightMotor->setSpeed(250);
    leftMotor->setSpeed(250);
    rightMotor->run(BACKWARD);
    leftMotor->run(FORWARD); 
  }

  // turn left
  else if (abs(verticalValue) < deadZone && horizontalValue < -deadZone) {
    Serial.println("Turn left");
    // rightMotor->setSpeed(motorSpeed);
    rightMotor->setSpeed(250);
    rightMotor->run(FORWARD);
    leftMotor->run(RELEASE);      
  }

  //turn right
  else if (abs(verticalValue) < deadZone && horizontalValue > deadZone) {
    Serial.println("Turn right");
    // leftMotor->setSpeed(motorSpeed);
    leftMotor->setSpeed(250);
    rightMotor->run(RELEASE);
    leftMotor->run(BACKWARD);  
  }
  else // in the deadZone, don't move
  {
    Serial.println("Stop");
    rightMotor->run(RELEASE);
    leftMotor->run(RELEASE); 
  }
  delay(50); 

  // if (weaponValue > 60) {
  //   Serial.println("weapon spin forward");
  //   weapon->setSpeed(weaponValue - 20);
  //   weapon->run(FORWARD); 
  // } else if (weaponValue < -60) {
  //   Serial.println("weapon spin backward");
  //   weapon->setSpeed(weaponValue - 20);
  //   weapon->run(BACKWARD); 
  // }
}
