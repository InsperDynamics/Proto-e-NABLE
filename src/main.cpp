#include <Arduino.h>
#include <Servo.h>

// ####################################### START OF CONFIGURATION #######################################

// Each servo and its start angle 
// Format: {ping, angle}
int pins[][2] = {{5, 90}, {6, 130}, {7, 90}, {8, 100}, {9, 90}, {10, 90}, {11, 90}, {12, 90}};

// Array containing all servos that move, using the step values (0 - (size -1))
int updateList[] = {0, 2, 4, 6};

// The step value for each servo, the amount of degrees it should move each loop
int step[] = {4, 4, 4, 4, 4, 4, 4, 4};

// The delay time between each step in milliseconds
int delayTime = 248;

// The minimum angle of the servo
int minAngle = 40;

// The maximum angle of the servo
int maxAngle = 170;

// ####################################### END OF CONFIGURATION #######################################

Servo servos[*(&pins + 1) - pins]; // Array containing all the servos of size pins

void setup()
{
  for (int i = 0; i < *(&pins + 1) - pins; i++)
  {
    Servo servo = Servo();

    servo.attach(pins[i][0]); // Attach the servo to the pin
    servo.write(pins[i][1]);  // Set the start angle for each servo

    servos[i] = servo;
  }
}

void loop()
{
  for (int servo : updateList)
  {
    int angle = servos[servo].read() + step[servo]; // Calculate the next angle value

    if (angle < minAngle || angle > maxAngle) // If the angle is out of bounds
    {
      step[servo] = -step[servo]; // Reverse the step value
      angle -= 2 * step[servo];   // Calculate the next angle value
    }
    servos[servo].write(angle); // Update the servo position to the new angle
  }
  delay(delayTime); // Delay of x ms between each loop
}