/*
This code only moves one servo located at PWM pin 0 on the adafruit board.
*/
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  100 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  425 // this is the 'maximum' pulse length count (out of 4096)

// our servo # counter
uint8_t servonum = 0;

void setup() {
  pwm.begin();
  
  pwm.setPWMFreq(50);  // Analog servos run at ~60 Hz updates
}

void loop() {
  // Drive each servo one at a time
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; ++pulselen) {
    pwm.setPWM(0, 0, pulselen);
    delay(10);
  }
  delay(1000);
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; --pulselen) {
    pwm.setPWM(0, 0, pulselen);
    delay(10);
  }
  delay(1000);

}
