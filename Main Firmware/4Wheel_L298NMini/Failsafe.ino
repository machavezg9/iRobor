/*
  Failsafe constantly monitors signal strength through RSSI and compares it to a minimum threshold
  RSSI values range from 0-1000 (0ms-1ms)
*/
int signalMin = 300; // set this higher to failsafe sooner (lower risk), or lower to allow for longer distance (higher risk)

int rdRSSI() {
  int signalStrength = pulseIn(RSSI, HIGH); // reads PWM values of RSSI pin
  return signalStrength;
}

void signalCheck() {
  while (rdRSSI() < signalMin) { // if RSSI reading is less than the minimum acceptable signal
    stop(); // sets all motors to motorMin
    rdRSSI();
    delay(100);
  }
}
