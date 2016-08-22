#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#define channel5 5

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 6, NEO_RGB + NEO_KHZ800);

byte gammatable[256];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Color Led Test Begin!");

  pinMode(channel5, INPUT);
  
  strip.begin();
  strip.show(); //initializes led to off
}

void setRed(int wait) {
  strip.setPixelColor(0, strip.Color(255,0,0));
  strip.show(); 
  delay(wait);
}

void setGreen(int wait) {
  strip.setPixelColor(0, strip.Color(0,255,0));
  strip.show(); 
  delay(wait);
}

void setBlue(int wait) {
  strip.setPixelColor(0, strip.Color(0,0,255));
  strip.show(); 
  delay(wait);
}

void setOff(int wait) {
  strip.setPixelColor(0, strip.Color(0,0,0));
  strip.show(); 
  delay(wait);
}

void loop() {
  int readMode = pulseIn(channel5, HIGH);
  Serial.print("Channel 5: ");
  Serial.println(readMode);

  if ( readMode > 1990 ){
    setRed(50);
  } else if ( readMode < 990 ) {
    setOff(50);
  }
  /*
  setRed(100);
  setOff(200);
  setRed(100);
  setOff(200);
  setRed(100);
  setOff(1000);
  setRed(200);
  setOff(1000);
  setRed(200);
  setOff(1000);
  setRed(200);
  setOff(1000);
  setRed(100);
  setOff(200);
  setRed(100);
  setOff(200);
  setRed(100);
  setOff(2500);
  */

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
