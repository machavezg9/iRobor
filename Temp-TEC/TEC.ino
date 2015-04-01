//Arduino Uno code, Modify pins for Arduino Mega
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//Distance sensor
const int trigPin = 8;
const int echoPin = 7;
const int lightFlash = 9;
float v = 331.5 + 0.6 * 20; //m/s

//TMP36 Pin Variables
//int tempPin = 2; 
//int tempFPin = 3;//the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade with a
                        //500 mV offset to allow for negative temperatures
//int tempReading;
//int tempFReading;
// constants won't change. Used here to set pin numbers:
// Motor Driver Pins
//Function	    pins per   pins per
//                  Ch. A      Ch. B
//Direction	    D12	       D13
//PWM	            D3	       D11
//Brake	            D9	       D8
//Current Sensing   A0         A1
/* The following code is to control the TEC 1
const int TecDirA = 12;
const int TecPWNA = 3;
const int TecBrakeA = 9;
const int TecCurrA = 0;
// The following code is to control the TEC 2
const int TecDirB = 13;
const int TecPWNB = 11;
const int TecBrakeB = 8;
const int TecCurrB = 1;
const int Fan1 = 6;
*/
void setup() { 
  lcd.init();// initialize the lcd 
  lcd.backlight();
/* Set Pin Modes for TECs
  pinMode(TecDirA, OUTPUT);
  pinMode(TecPWNA, OUTPUT);
  pinMode(TecBrakeA, OUTPUT);
  pinMode(TecCurrA, OUTPUT);
  pinMode(TecDirB, OUTPUT);
  pinMode(TecPWNB, OUTPUT);
  pinMode(TecBrakeB, OUTPUT);
  pinMode(TecCurrB, OUTPUT);
  pinMode(Fan1, OUTPUT);
  */
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(lightFlash, OUTPUT);
}

float distanceM(){
  //seconds sound pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  
  //listen for echo
  float tUs = pulseIn(echoPin, HIGH); //microseconds
  float t = tUs / 1000.0 / 1000.0 / 2; //s
  float d = t*v; //m
  return d*100; //cm
}
  
void loop() {
  lcd.noBlink();
  int d = distanceM();
  delay(1);
  
/*Temperature code for the LM 34 hot side temperature
  tempFReading = analogRead(tempFPin); 
  float tempC = (tempFReading * 4.88 * 100.0) / 1024.0;
  float tempF = (tempC * 9.0 / 5.0) + 32.0;
//  float tempF = (voltageF - 0.5) * 100; 
  delay(1000);
  //Temperature code for the TMP36 cold side temperature
  tempReading = analogRead(tempPin); 
  float voltage = tempReading * 4.88;
  voltage /=1024.0;
  float temperatureC = (voltage - 0.5) * 100;
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0; 
  delay(1000);
  */
  /*
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Current Distance");
  lcd.setCursor(0,1);
  lcd.print(d);
  //lcd.print(char(223));
  lcd.print(" cm");
  delay(1000);*/
  
  {
    if (d > 10){ //Controlling when the Cold TEC powers on and off
      digitalWrite(lightFlash, HIGH);
      delay(1);
    }
    else if (d <= 10){
      digitalWrite(lightFlash, LOW);
      delay(1);
    }
  }
  
/*
  lcd.setCursor(0,0);
  lcd.print("Current Cold Temp:");
  lcd.setCursor(0,1);
  lcd.print(temperatureF);
  lcd.print(char(223));
  lcd.print("F");
  lcd.setCursor(0,2);
  lcd.print("Current Hot Temp:");
  lcd.setCursor(0,3);
  lcd.print(tempF);
  lcd.print(char(223));
  lcd.print("F");
  delay(1000);
*/  
// here is where you'd put code that needs to be running all the time.
/*
digitalWrite(Fan1, HIGH);
{if (temperatureF > 43) //Controlling when the Cold TEC powers on and off
 {digitalWrite(TecDirA, HIGH);
  digitalWrite(TecPWNA, HIGH);
  digitalWrite(TecBrakeA, LOW);
  delay(1000);}
  else if (temperatureF < 34)
 {digitalWrite(TecBrakeA, HIGH);}
 }
{if (tempF < 140)  //Controlling when the Hot TEC powers on and of
 {digitalWrite(TecDirB, HIGH);
  digitalWrite(TecPWNB, HIGH);
  digitalWrite(TecBrakeB, LOW);
  delay(1000);}
  else if (tempF > 150)
 {digitalWrite(TecBrakeB, HIGH);}
}
*/
}
