//Controller values for movement, adjust according to your controller
//Start and end points for reverse and left movement(Bottom & left half of Ele and Ail)
int lowerStart = 980;
int lowerEnd = 1450;
//Start and end points for stop (Middle of Ele and Ail)
int deadZoneStart = 1450;
int deadZoneEnd = 1550;
//Start and end points for forward (Top half of throttle)
int upperStart = 1550;
int upperEnd = 2010;
//Motor speed values
int motorLow = 0;
int motorHigh = 255;

//Sends PWM command to turn right wheel clockwised at some speed between 0-255
void rightForward(int fwSpeed) {
  //does do CW turns
  analogWrite(MR1, fwSpeed);
  analogWrite(MR2, motorLow);
  analogWrite(MR3, motorLow);
  analogWrite(MR4, fwSpeed);
}
//Sends PWM command to turn left wheel counterclockwise at some speed between 0-255
void leftForward(int fwSpeed) {
  //Needs to do CCW turns
  analogWrite(ML1, fwSpeed);
  analogWrite(ML2, motorLow);
  analogWrite(ML3, motorLow);
  analogWrite(ML4, fwSpeed);
}
//Sends PWM command to turn right wheel counterclockwised at some speed between 0-255
void rightBackward(int fwSpeed) {
  //does do CCW turns
  analogWrite(MR1, motorLow);
  analogWrite(MR2, fwSpeed);
  analogWrite(MR3, fwSpeed);
  analogWrite(MR4, motorLow);
}
//Sends PWM command to turn left wheel clockwise at some speed between 0-255
void leftBackward(int fwSpeed) {
  //Needs to do CW turns
  analogWrite(ML1, motorLow);
  analogWrite(ML2, fwSpeed);
  analogWrite(ML3, fwSpeed);
  analogWrite(ML4, motorLow);
}
//Stops all motors
void stopMotors() {
  analogWrite(MR1, motorLow);
  analogWrite(MR2, motorLow);
  analogWrite(MR3, motorLow);
  analogWrite(MR4, motorLow);
  analogWrite(ML1, motorLow);
  analogWrite(ML2, motorLow);
  analogWrite(ML3, motorLow);
  analogWrite(ML4, motorLow);
}
//The following reads the input PWM signal from the receiver on an approximate scale of 1000-2000
//Note: adjust your scale correctly by modifying the variable definitions on top
/*----------Forward & Backward Movement Direction-----------*/
int readMovementDirection() {
  //CH1
  int motorSpeed = pulseIn(CH1, HIGH); 
  return motorSpeed;
}
/*---------------Left & Right Turn Direction----------------*/
int readTurningDirection() {
  //CH2
  int motorSpeed = pulseIn(CH2, HIGH); 
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
  //First Directional Loop
  if ( readMovementDirection() > upperStart && readMovementDirection() < upperEnd) {
    mappingDirection = returnMapSpeed(readMovementDirection(), upperStart, upperEnd);
    //Forward right, left and forward
    if ( readTurningDirection() > upperStart && readTurningDirection() < upperEnd ) {
      //Right turn while moving forward
      //mappingTurn = map(readTurningDirection(), upperStart, upperEnd, mappingDirection, 0);
      mappingTurn = returnMapTurn(upperStart, upperEnd, mappingDirection);
      rightForward(mappingTurn);
      leftForward(mappingDirection);
    } else if ( readTurningDirection() > lowerStart && readTurningDirection() < lowerEnd ) {
      //mappingTurn = map(readTurningDirection(), lowerEnd, lowerStart, mappingDirection, 0);
      mappingTurn = returnMapTurn(lowerEnd, lowerStart, mappingDirection);
      rightForward(mappingDirection);
      leftForward(mappingTurn);
      delay(100);
    } else {
      rightForward(mappingDirection);
      leftForward(mappingDirection);
      delay(100);
    }
    //delay(100);
  } 
  //Second Direction Loop
  else if ( readMovementDirection() > lowerStart && readMovementDirection() < lowerEnd ) {
    mappingDirection = returnMapSpeed(readMovementDirection(), lowerEnd, lowerStart);
    //Backward right, left, and backward
    if ( readTurningDirection() > upperStart && readTurningDirection() < upperEnd ) {
      //mappingTurn = map(readTurningDirection(), upperStart, upperEnd, mappingDirection, 0);
      mappingTurn = returnMapTurn(upperStart, upperEnd, mappingDirection);
      rightBackward(mappingTurn);
      leftBackward(mappingDirection);
      delay(100);
    } else if ( readTurningDirection() > lowerStart && readTurningDirection() < lowerEnd ) {
      //mappingTurn = map(readTurningDirection(), lowerEnd, lowerStart, mappingDirection, 0);
      mappingTurn = returnMapTurn(lowerEnd, lowerStart, mappingDirection);
      rightBackward(mappingDirection);
      leftBackward(mappingTurn);
      delay(100);
    } else {
      rightBackward(mappingDirection);
      leftBackward(mappingDirection);
      delay(100);
    }
    //delay(100);
  } 
  // Third Directional Loop
  else if ( readMovementDirection() > deadZoneStart && readMovementDirection() < deadZoneEnd ) {
    //Forward right, left and forward
    int turnSpeed = 225;
    if ( readTurningDirection() > upperStart && readTurningDirection() < upperEnd ) {
      //Right turn, stops then turns
      rightBackward(turnSpeed);
      leftForward(turnSpeed);
      delay(100);
//      while(mappingTurn > motorLow) {
//        rightBackward(mappingTurn);
//        leftForward(mappingTurn);
//        mappingTurn = map(readTurningDirection(), upperStart, upperEnd, motorLow, motorHigh);
//        delay(100);
//      }
    } else if ( readTurningDirection() > lowerStart && readTurningDirection() < lowerEnd ) {
      rightForward(turnSpeed);
      leftBackward(turnSpeed);
      delay(100);
//      while(mappingTurn > motorLow) {
//        rightForward(mappingTurn);
//        leftBackward(mappingTurn);
//        mappingTurn = map(readTurningDirection(), lowerEnd, lowerStart, motorLow, motorHigh);
//        delay(100);
//      }
    } else {
      stopMotors();
      delay(100);
    } 
  } 
  //Fourth Directional Loop
  else {
    stopMotors();
    delay(100);
  }
delay(100);
}
