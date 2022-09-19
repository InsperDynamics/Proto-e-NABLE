#ifndef SoftwareServo_h
#define SoftwareServo_h

#include <Arduino.h>
#include <inttypes.h>

class SoftwareServo
{
private:
  uint8_t pin;
  uint8_t angle;    // in degrees (minAngle-maxAngle)
  uint8_t minAngle; // in degrees (default is 140)
  uint8_t maxAngle; // in degrees (default 170)
  uint16_t pulse0;  // pulse width in TCNT0 counts
  uint8_t min16;    // minimum pulse, 16uS units  (default is 34)
  uint8_t max16;    // maximum pulse, 16uS units, 0-4ms range (default is 150)
  class SoftwareServo *next;
  static SoftwareServo *first;

public:
  SoftwareServo(uint8_t, int); // Create a servo object attached to a 'pin' and set the initial angle
  void detach();
  void write(int); // specify the angle in degrees, 0 to 180
  uint8_t read();
  uint8_t attached();
  void setMinimumAngle(int);      // Set the minimum angle allowed for the servo
  void setMaximumAngle(int);      // Set the maximum angle allowed for the servo
  bool changeDirection();         // Check if the direction of the servo needs to be changed
  void setMinimumPulse(uint16_t); // pulse length for 0 degrees in microseconds, 540uS default
  void setMaximumPulse(uint16_t); // pulse length for 180 degrees in microseconds, 2400uS default
  static void refresh();          // must be called at least every 50ms or so to keep servo alive
                                  // you can call more often, it won't happen more than once every 20ms
};

#endif