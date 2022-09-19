#include <SoftwareServo.h>

int delayTime = 24;              // The delay time between each step in milliseconds max (45)
int updateList[] = {0, 2, 4, 6}; // Array containing the servos that should be updated in each loop (0-7)

SoftwareServo servos[] = {{5, 90}, {6, 130}, {7, 90}, {8, 100}, {9, 90}, {10, 90}, {11, 90}, {12, 90}}; // The servos objects using the defined pins and initial angles {ping, angle}

uint8_t step[] = {4, 4, 4, 4, 4, 4, 4, 4}; // The step value for each servo

void setup()
{
  // Serial.begin(115200); // Max baud rate for the serial monitor
  Serial.begin(9600);
}

void loop()
{
  for (int position : updateList)
  {
    servos[position].write(servos[position].read() + step[position]); // Update the servo position to the new angle

    if (servos[position].changeDirection()) // Check if step need to be inverted
    {
      step[position] = -step[position]; // Reverse the step value
    }
  }
  delay(delayTime); // Delay of x ms between each loop

  SoftwareServo::refresh(); // Refresh all the servos and send them all the new angle values
}