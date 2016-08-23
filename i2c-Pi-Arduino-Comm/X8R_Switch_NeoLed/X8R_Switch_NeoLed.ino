#include <Wire.h>
#include <Adafruit_NeoPixel.h>
//serial address
#define SLAVE_ADDRESS 0x04
//channel used to receive button pwm signal from taranis x9d
#define channel5 5

//initially set led to off state
int ledState = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 6, NEO_RGB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  Serial.println("Color Led Test Begin!");
  pinMode(channel5, INPUT);
  strip.begin();
  strip.show();
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
  // define callbacks for i2c communication
//  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}

void loop() {
  int readMode = pulseIn(channel5, HIGH);
  if ( readMode > 1990 ){
    setRed();
    ledState = 1;
  } else if ( readMode < 990 ) {
    setOff();
    ledState = 0;
  }
  sendData();
}

//Sets led red, green or blue
void setRed() {
  strip.setPixelColor(0, strip.Color(255,0,0));
  strip.show(); 
  //delay(wait);
}
void setGreen() {
  strip.setPixelColor(0, strip.Color(0,255,0));
  strip.show(); 
}
void setBlue() {
  strip.setPixelColor(0, strip.Color(0,0,255));
  strip.show(); 
}
//Led turn off
void setOff() {
  strip.setPixelColor(0, strip.Color(0,0,0));
  strip.show(); 
}

//send data
void sendData() {
  Serial.print(ledState);
  Wire.write(ledState);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
