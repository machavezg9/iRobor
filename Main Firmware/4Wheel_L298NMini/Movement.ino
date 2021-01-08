// Motor speed values
int motorMin = 0;
int motorMax = 255;
int eleSpeed;
int eleDirection;

// Min and Max RC channel values (lowest and highest PWM signals output by TX)
int rcMin = 980;
int rcMax = 2020;
int deadBand = 25;
// calculated values
int rcMid = rcMin + ((rcMax - rcMin) / 2);

int rdCH1() {
  int ele = pulseIn(CH1, HIGH);
  return ele;
}

int rdCH2() {
  int ail = pulseIn(CH2, HIGH);
  return ail;
}

void move() {
  if (rdCH1() > rcMid + deadBand && rdCH1() < rcMax) {
    eleSpeed = map(rdCH1(), rcMid + deadBand, rcMax, motorMin, motorMax);
    forward(eleSpeed);
  }
  else if (rdCH1() < rcMid - deadBand && rdCH1() > rcMin) {
    eleSpeed = map(rdCH1(),rcMid - deadBand, rcMin, motorMin, motorMax);
    reverse(eleSpeed);
  }
  else {
    stop();
  }
}

int speed() {
  if (rdCH1() > rcMid + deadBand && rdCH1() < rcMax) {
    return map(rdCH1(), rcMid + deadBand, rcMax, motorMin, motorMax);
  }
  else if (rdCH1() < rcMid - deadBand && rdCH1() > rcMin) {
    return map(rdCH1(),rcMid - deadBand, rcMin, motorMin, motorMax);
  }
  else {
    return 0;
  }
}

int direction() {
  if (rdCH1() > rcMid + deadBand && rdCH1() < rcMax) {
    eleDirection = "Forward";
    return 1;
  }
  else if (rdCH1() < rcMid - deadBand && rdCH1() > rcMin) {
    eleDirection = "Reverse";
    return 2;
  }
  else {
    eleDirection = "Stopped";
    return 0;
  }
}

void forward(int motorSpeed) {
  analogWrite(MR1, motorSpeed);
  analogWrite(MR2, motorMin);
  analogWrite(MR3, motorMin);
  analogWrite(MR4, motorSpeed);
  analogWrite(ML1, motorSpeed);
  analogWrite(ML2, motorMin);
  analogWrite(ML3, motorMin);
  analogWrite(ML4, motorSpeed);
}

void reverse(int motorSpeed) {
  analogWrite(MR1, motorMin);
  analogWrite(MR2, motorSpeed);
  analogWrite(MR3, motorSpeed);
  analogWrite(MR4, motorMin);
  analogWrite(ML1, motorMin);
  analogWrite(ML2, motorSpeed);
  analogWrite(ML3, motorSpeed);
  analogWrite(ML4, motorMin);
}

// stops all motors
void stop() {
  analogWrite(MR1, motorMin);
  analogWrite(MR2, motorMin);
  analogWrite(MR3, motorMin);
  analogWrite(MR4, motorMin);
  analogWrite(ML1, motorMin);
  analogWrite(ML2, motorMin);
  analogWrite(ML3, motorMin);
  analogWrite(ML4, motorMin);
}
