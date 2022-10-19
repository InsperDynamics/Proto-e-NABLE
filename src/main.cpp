#include <Arduino.h>
#include <Servo.h>

int delayTime = 24;              // The delay time between each step in milliseconds max (45)
int updateList[] = {0, 2, 4, 6}; // Array containing the servos that should be updated in each loop (0-7)

int minAngle = 40;  // The minimum angle of the servo
int maxAngle = 170; // The maximum angle of the servo

Servo servos[] = {Servo(), Servo(), Servo(), Servo(), Servo(), Servo(), Servo(), Servo()};

uint8_t step[] = {4, 4, 4, 4, 4, 4, 4, 4}; // The step value for each servo

void setup()
{
  int pins[] = {5, 6, 7, 8, 9, 10, 11, 12};               // The pins used for the servos
  int startAngles[] = {90, 130, 90, 100, 90, 90, 90, 90}; // The start angles for each servo

  for (int i = 0; i < 8; i++)

  {
    servos[i].attach(pins[i]);
    servos[i].write(startAngles[i]);
  }
}

void loop()
{
  for (int position : updateList)
  {
    int angle = servos[position].read() + step[position];

    servos[position].write(angle); // Update the servo position to the new angle

    if (angle < minAngle || angle > maxAngle) // Check if step need to be inverted
    {
      step[position] = -step[position]; // Reverse the step value
    }
  }
  delay(delayTime); // Delay of x ms between each loop
}