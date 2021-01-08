void displayInputs() {
  delay(100);

  int readCH1 = rdCH1(); // read CH1 pin
  int readCH2 = rdCH2(); // read CH2 pin
  int readRSSI = rdRSSI(); // read RSSI pin
  int eleSpeed = speed(); // read speed being sent to motors
  int eleDirection = direction(); // read direction being sent to motors (1 = forward, 2 = reverse, 0 = stop)

  // Min and Max RC channel values (lowest and highest PWM signals output by TX)
  int rcMin = 980;
  int rcMax = 2020;
  int deadBand = 25;
  // calculated values
  int rcMid = rcMin + ((rcMax - rcMin) / 2);

  display.clearDisplay(); // clear display buffer
  display.setTextSize(1); // set font size
  display.setTextColor(SSD1306_WHITE); // set color (use white despite color)
  // line 1
  display.setCursor(0, 0); // set the cursor coordinates
  display.print("Rall-E");
  // line 2
  display.setCursor(0, 10);
  display.print("CH1: ");
  display.print(readCH1);
  // line 3
  display.setCursor(0, 20);
  display.print("CH2: ");
  display.print(readCH2);
  // line 4
  display.setCursor(0, 30);
  display.print("RSSI: ");
  display.print(readRSSI);
  // line 5
  display.setCursor(0, 40);
  display.print("Speed: ");
  display.print(eleSpeed);
  // line 6
  display.setCursor(0, 50);
  display.print("Dir: ");
  switch (eleDirection) {
    case 1:
      display.print("Forward");
      break;
    case 2:
      display.print("Reverse");
      break;
    case 0:
      display.print("Stopped");
      break;
    default:
      display.print("Stopped");
      break;
  }
}
