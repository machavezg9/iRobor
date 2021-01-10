// Motor speed values
int motorOff = 0;
int motorMin = 50;
int motorMax = 100;
int speedValue;
int directionValue;

// Min and Max RC channel values (lowest and highest PWM signals output by TX)
int rcMin = 980;
int rcMax = 2020;
int deadBand = 25;
// calculated values
int rcMid = rcMin + ((rcMax - rcMin) / 2);

int rdCH1() {
  int inputW = pulseIn(CH1, HIGH);
  return inputW;
}

int rdCH2() {
  int inputX = pulseIn(CH2, HIGH);
  return inputX;
}

void move() {
  if (abs(rdCH2()-rcMid) > abs(rdCH1()-rcMid)) {
    if (rdCH1() < rcMid + deadBand && rdCH1() > rcMid - deadBand && rdCH2() < rcMid + deadBand && rdCH2() > rcMid - deadBand) {
      stop();
    }
    else if (rdCH2() > rcMid && rdCH2() < rcMax) {
      speedValue = map(rdCH2(), rcMid, rcMax, motorMin, motorMax);
      moveForward(speedValue);
    }
    else if (rdCH2() < rcMid && rdCH2() > rcMin) {
      speedValue = map(rdCH2(), rcMid, rcMin, motorMin, motorMax);
      moveReverse(speedValue);
    }
    else {
      stop();
    }
  }
  else if (abs(rdCH1()-rcMid) > abs(rdCH2()-rcMid)) {
    if (rdCH1() < rcMid + deadBand && rdCH1() > rcMid - deadBand && rdCH2() < rcMid + deadBand && rdCH2() > rcMid - deadBand) {
      stop();
    }
    else if (rdCH1() > rcMid && rdCH1() < rcMax) {
      speedValue = map(rdCH1(), rcMid, rcMax, motorMin, motorMax);
      yawRight(speedValue);
    }
    else if (rdCH1() < rcMid && rdCH1() > rcMin) {
      speedValue = map(rdCH1(), rcMid, rcMin, motorMin, motorMax);
      yawLeft(speedValue);
    }
    else {
      stop();
    }
  }
  else {
    stop();
  }
}

int speed() {
  if (rdCH1() < rcMid + deadBand && rdCH1() > rcMid - deadBand && rdCH2() < rcMid + deadBand && rdCH2() > rcMid - deadBand) {
    return 0;
  }
  else if (abs(rdCH2()-rcMid) > abs(rdCH1()-rcMid)) {
    if (rdCH2() > rcMid && rdCH2() < rcMax) {
      return map(rdCH2(), rcMid, rcMax, motorMin, motorMax);
    }
    else if (rdCH2() < rcMid && rdCH2() > rcMin) {
      return map(rdCH2(), rcMid, rcMin, motorMin, motorMax);
    }
    else {
      return 0;
    }
  }
  else if (abs(rdCH1()-rcMid) > abs(rdCH2()-rcMid)) {
    if (rdCH1() > rcMid && rdCH1() < rcMax) {
      return map(rdCH1(), rcMid, rcMax, motorMin, motorMax);
    }
    else if (rdCH1() < rcMid && rdCH1() > rcMin) {
      return map(rdCH1(), rcMid, rcMin, motorMin, motorMax);
    }
    else {
      return 0;
    }
  }
  else {
    return 0;
  }
}

int direction() {
  if (rdCH1() < rcMid + deadBand && rdCH1() > rcMid - deadBand && rdCH2() < rcMid + deadBand && rdCH2() > rcMid - deadBand) {
    directionValue = "Stopped";
    return 0;
  }
  else if (abs(rdCH2()-rcMid) > abs(rdCH1()-rcMid)) {
    if (rdCH2() > rcMid && rdCH2() < rcMax) {
      directionValue = "Forward";
      return 1;
    }
    else if (rdCH2() < rcMid && rdCH2() > rcMin) {
      directionValue = "Reverse";
      return 2;
    }
    else {
      directionValue = "Stopped";
      return 0;
    }
  }
  else if (abs(rdCH1()-rcMid) > abs(rdCH2()-rcMid)) {
    if (rdCH1() > rcMid && rdCH1() < rcMax) {
      directionValue = "Right";
      return 3;
    }
    else if (rdCH1() < rcMid && rdCH1() > rcMin) {
      directionValue = "Left";
      return 4;
    }
    else {
      directionValue = "Stopped";
      return 0;
    }
  }
  else {
    directionValue = "Stopped";
    return 0;
  }
}

void moveForward(int motorSpeed) {
  analogWrite(MR1, motorSpeed);
  analogWrite(MR2, motorOff);
  analogWrite(MR3, motorOff);
  analogWrite(MR4, motorSpeed);
  analogWrite(ML1, motorSpeed);
  analogWrite(ML2, motorOff);
  analogWrite(ML3, motorOff);
  analogWrite(ML4, motorSpeed);
}

void moveReverse(int motorSpeed) {
  analogWrite(MR1, motorOff);
  analogWrite(MR2, motorSpeed);
  analogWrite(MR3, motorSpeed);
  analogWrite(MR4, motorOff);
  analogWrite(ML1, motorOff);
  analogWrite(ML2, motorSpeed);
  analogWrite(ML3, motorSpeed);
  analogWrite(ML4, motorOff);
}

void yawRight(int motorSpeed) {
  analogWrite(MR1, motorOff);
  analogWrite(MR2, motorSpeed);
  analogWrite(MR3, motorSpeed);
  analogWrite(MR4, motorOff);
  analogWrite(ML1, motorSpeed);
  analogWrite(ML2, motorOff);
  analogWrite(ML3, motorOff);
  analogWrite(ML4, motorSpeed);
}

void yawLeft(int motorSpeed) {
  analogWrite(MR1, motorSpeed);
  analogWrite(MR2, motorOff);
  analogWrite(MR3, motorOff);
  analogWrite(MR4, motorSpeed);
  analogWrite(ML1, motorOff);
  analogWrite(ML2, motorSpeed);
  analogWrite(ML3, motorSpeed);
  analogWrite(ML4, motorOff);
}

// stops all motors
void stop() {
  analogWrite(MR1, motorOff);
  analogWrite(MR2, motorOff);
  analogWrite(MR3, motorOff);
  analogWrite(MR4, motorOff);
  analogWrite(ML1, motorOff);
  analogWrite(ML2, motorOff);
  analogWrite(ML3, motorOff);
  analogWrite(ML4, motorOff);
}
