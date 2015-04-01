/*
This still needs to be modified to control 3 MG995 servos, right now it only works with 2 but can easily be modified for the
third one.
*/
#include <Servo.h>
//Bottom 60-180
//Forward/Backward 50-170(you can go to 160 for short or 180 to hit the ground)
//Open/Close 75-180
#define min(a,b) ((a) < (b) ? (a) : (b)
#define max(a,b) ((a) > (b) ? (a) : (b)

Servo panServo, tiltServo, turnServo;

#define panPin 5
#define tiltPin 6

#define motionDelay 1
#define minPan 75
#define maxPan 180
#define minTilt 50
#define maxTilt 170


void setup() {
  // put your setup code here, to run once:
  panServo.attach(panPin);
  tiltServo.attach(tiltPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  static const uint16_t minAngle = min(minPan, minTilt);
  static const uint16_t maxAngle = max(maxPan, maxTilt);
  
  for(int i = minAngle; i <= maxAngle; ++i)
  {
    panServo.write(map(i, minAngle, maxAngle, minPan, maxPan));
    tiltServo.write(map(i, minAngle, maxAngle, minTilt, maxTilt));
    delay(motionDelay);
  }
  delay(1000);
  
  for(int i = maxAngle; i >= minAngle; --i)
  {
    panServo.write(map(i, minAngle, maxAngle, minPan, maxPan));
    tiltServo.write(map(i, minAngle, maxAngle, minTilt, maxTilt));
    delay(motionDelay);
  }
  delay(1000);  
}
