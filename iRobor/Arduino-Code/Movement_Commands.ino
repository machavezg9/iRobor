//Controller values for movement, adjust according to your controller
//Start and end points for reverse and left movement(Bottom half of throttle)
int backwardStart = 980;
int backwardEnd = 1450;
//Start and end points for stop (Middle of throttle)
//Note: change this to deadzone from start stop, this is redundant
int stopStart = 1450;
int stopEnd = 1550;
//Start and end points for forward (Top half of throttle)
int forwardStart = 1550;
int forwardEnd = 2010;
//Start and end points for turning left (Left half of rudder)
int leftStart = 980;
int leftEnd = 1450;
//Start and end points for turning dead zone(Middle of rudder)
int deadZoneStart = 1450;
int deadZoneEnd = 1550;
//Start and end points for turning right (Right half of rudder)
int rightStart = 1550;
int rightEnd = 2010;
//Motor speed values
int motorLow = 0;
int motorHigh = 255;

//Sends PWM command to turn right wheel clockwised at some speed between 0-255
void rightForward(int fwSpeed) {
  //does do CW turns
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, fwSpeed);
}
//Sends PWM command to turn left wheel counterclockwise at some speed between 0-255
void leftForward(int fwSpeed) {
  //Needs to do CCW turns
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, fwSpeed);
}
//Sends PWM command to turn right wheel counterclockwised at some speed between 0-255
void rightBackward(int fwSpeed) {
  //does do CCW turns
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, fwSpeed);
}
//Sends PWM command to turn left wheel clockwise at some speed between 0-255
void leftBackward(int fwSpeed) {
  //Needs to do CW turns
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, fwSpeed);
}
//Stops all motors
void stopMotors() {
  analogWrite(enA, LOW);
  analogWrite(enB, LOW);
}
//The following reads the input PWM signal from the receiver on an approximate scale of 1000-2000
//Note: adjust your scale correctly by modifying the variable definitions on top
/*----------Forward & Backward Movement Direction-----------*/
int readMovementDirection() {
  //Reads channel1
  int motorSpeed = pulseIn(channel1, HIGH); 
  return motorSpeed;
}
/*---------------Left & Right Turn Direction----------------*/
int readTurningDirection() {
  //Reads channel2
  int motorSpeed = pulseIn(channel3, HIGH); 
  return motorSpeed;
}

int returnMapSpeed(int directionSpeed, int mapStart, int mapEnd) {
  int mappedSpeed = map(directionSpeed, mapStart, mapEnd, motorLow, motorHigh);
  return mappedSpeed;
}

int returnMapTurn(int mapTurnStart, int mapTurnEnd, int mapTurnSpeed) {
  int mappedTurnSpeed = map(readTurningDirection(), mapTurnStart, mapTurnEnd, mapTurnSpeed, motorLow);
  return mappedTurnSpeed;
}
int returnMapTurnSpeed(int mapTurnSpeedStart, int mapTurnSpeedEnd, int mapTurnSpeed) {
  int mappedTurnSpeed = map(readTurningDirection(), mapTurnSpeedStart, mapTurnSpeedEnd, mapTurnSpeed, motorHigh);
  return mappedTurnSpeed;
}
//Have to update turning to work better, when turning right make left wheel turn starting from current 
//forward speed to 255 and the right wheel go from current forward speed to 0
void sendDirection() {
  int mappingDirection;
  int mappingTurn;
  if ( readMovementDirection() > forwardStart && readMovementDirection() < forwardEnd) {
    mappingDirection = returnMapSpeed(readMovementDirection(), forwardStart, forwardEnd);
    //Forward right, left and forward
    if ( readTurningDirection() > rightStart && readTurningDirection() < rightEnd ) {
      //Right turn while moving forward
      //mappingTurn = map(readTurningDirection(), rightStart, rightEnd, mappingDirection, 0);
      mappingTurn = returnMapTurn(rightStart, rightEnd, mappingDirection);
      rightForward(mappingTurn);
      leftForward(mappingDirection);
    } else if ( readTurningDirection() > leftStart && readTurningDirection() < leftEnd ) {
      //mappingTurn = map(readTurningDirection(), leftEnd, leftStart, mappingDirection, 0);
      mappingTurn = returnMapTurn(leftEnd, leftStart, mappingDirection);
      rightForward(mappingDirection);
      leftForward(mappingTurn);
      delay(100);
    } else {
      rightForward(mappingDirection);
      leftForward(mappingDirection);
      delay(100);
    }
    //delay(100);
  } else if ( readMovementDirection() > backwardStart && readMovementDirection() < backwardEnd ) {
    mappingDirection = returnMapSpeed(readMovementDirection(), backwardEnd, backwardStart);
    //Backward right, left, and backward
    if ( readTurningDirection() > rightStart && readTurningDirection() < rightEnd ) {
      //mappingTurn = map(readTurningDirection(), rightStart, rightEnd, mappingDirection, 0);
      mappingTurn = returnMapTurn(rightStart, rightEnd, mappingDirection);
      rightBackward(mappingTurn);
      leftBackward(mappingDirection);
      delay(100);
    } else if ( readTurningDirection() > leftStart && readTurningDirection() < leftEnd ) {
      //mappingTurn = map(readTurningDirection(), leftEnd, leftStart, mappingDirection, 0);
      mappingTurn = returnMapTurn(leftEnd, leftStart, mappingDirection);
      rightBackward(mappingDirection);
      leftBackward(mappingTurn);
      delay(100);
    } else {
      rightBackward(mappingDirection);
      leftBackward(mappingDirection);
      delay(100);
    }
    //delay(100);
  } else if ( readMovementDirection() > deadZoneStart && readMovementDirection() < deadZoneEnd ) {
    //Forward right, left and forward
    int turnSpeed = 225;
    if ( readTurningDirection() > rightStart && readTurningDirection() < rightEnd ) {
      //Right turn, stops then turns
      rightBackward(turnSpeed);
      leftForward(turnSpeed);
      delay(100);
//      while(mappingTurn > motorLow) {
//        rightBackward(mappingTurn);
//        leftForward(mappingTurn);
//        mappingTurn = map(readTurningDirection(), rightStart, rightEnd, motorLow, motorHigh);
//        delay(100);
//      }
    } else if ( readTurningDirection() > leftStart && readTurningDirection() < leftEnd ) {
      rightForward(turnSpeed);
      leftBackward(turnSpeed);
      delay(100);
//      while(mappingTurn > motorLow) {
//        rightForward(mappingTurn);
//        leftBackward(mappingTurn);
//        mappingTurn = map(readTurningDirection(), leftEnd, leftStart, motorLow, motorHigh);
//        delay(100);
//      }
    } else {
      stopMotors();
      delay(100);
    } 
  } else {
    stopMotors();
    delay(100);
  }
delay(100);
}
