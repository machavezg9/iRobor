//This is to prevent the iRobor from operating once signal has been lost
//Signal Variables
//Signal strength is measured from 0ms-1ms
int minSignal = 300;

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

