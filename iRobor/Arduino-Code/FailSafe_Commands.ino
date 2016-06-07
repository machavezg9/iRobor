//This is to prevent the iRobor from operating once signal has been lost
//Signal Variables
int minSignal = 100;

/*-----------------------Read RSSI-=------------------------*/
int readSignalInput() {
  int signalStrength = pulseIn(channelRSSI, HIGH); 
  return signalStrength;
}
//Checks if signal is higher than the minimum required signal
void signalCheck() {
  while (readSignalInput() < minSignal) {
    stopMotors();
    readSignalInput();
    delay(100);
  }
}

