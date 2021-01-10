/*
  4Wheel_L298NMini

  Control software for a 4-wheel robot car, which has 4 motors and uses L298N Mini motor drivers.
  Firmware handles movement, IO, communications, and failsafe.

  Hardware:
  Arduino Mega 2560
  Arduino Development Shield V3
  2x L298N Mini 2V -10V 1.5A Motor Drivers
  4x 3V-6V DC Motors (1:48) 25cm x 14cm
  4x Plastic Wheels 6cm x 2.7cm
  Battery Pack (4x AA Batteries, Ni-MH 1.2V 1900mAh)

  written 2016-01-06
  by Miguel A. Chávez
  modified 2021-01-06
  by Kyle A. Jordan

*/

#include <Wire.h> // includes wire library for i2c
#include <Adafruit_GFX.h> // include Adafruit Graphics library
#include <Adafruit_SSD1306.h> // include Adafruit OLED library

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (-1 since there is no reset pin, aka sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Read input from the RC receiver
#define CH1 A0 // Aileron signal from RC Tx
#define CH2 A1 // Elevator signal from RC Tx
#define CH3 A2 // Auxilliary signal from RC Tx
#define RSSI A3 // Signal strength indicator from RC Tx

// motor driver board 1 (L298N Mini), 2 motors
#define MR1 4 // MR1 = "motor right front (driver1, in1)"
#define MR2 5 // MR2 = "motor right front (driver1, in2)"
#define MR3 6 // MR3 = "motor right rear (driver1, in3)"
#define MR4 7 // MR4 = "motor right rear (driver1, in4)"
// motor driver board 2 (L298N Mini), 2 motors
#define ML1 8 // ML1 = "motor left front (driver2, in1)"
#define ML2 9 // ML2 = "motor left front (driver2, in2)"
#define ML3 10 // ML3 = "motor left rear (driver2, in3)"
#define ML4 11 // ML4 = "motor left rear (driver2, in4)"

/*
  Each L298N Mini driver board has in1 - in4 (4 pins) that accept analog signal.
  Driver 1 controls the right 2 motors, Driver 2 controls the left 2 motors.
  in1/in2 on each board is connected to the front motors, in3/in4 on each board is connected to the rear motors.
  The mapping of in1 - in4 is as follows:
  +---------+---------+-------+-------+-------+-------+
  |  Motor  |  Mode   |  in1  |  in2  |  in3  |  in4  |
  +---------+---------+-------+-------+-------+-------+
  | Motor A | Forward | 1/PWM | 0     |       |       |
  |         | Reverse | 0     | 1/PWM |       |       |
  |         | Standby | 0     | 0     |       |       |
  |         | Braking | 1     | 1     |       |       |
  +---------+---------+-------+-------+-------+-------+
  | Motor B | Forward |       |       | 1/PWM | 0     |
  |         | Reverse |       |       | 0     | 1/PWM |
  |         | Standby |       |       | 0     | 0     |
  |         | Braking |       |       | 1     | 1     |
  +---------+---------+-------+-------+-------+-------+
  Note: "1" represents high level, "0" represents low level, PWM = pulse-width modulated wave (analog)
*/

void setup() {
  Serial.begin(9600);

  // pinMode definitions for inputs
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(RSSI, INPUT);
  // pinMode definitions for outputs (Motors)
  pinMode(MR1, OUTPUT);
  pinMode(MR2, OUTPUT);
  pinMode(MR3, OUTPUT);
  pinMode(MR4, OUTPUT);
  pinMode(ML1, OUTPUT);
  pinMode(ML2, OUTPUT);
  pinMode(ML3, OUTPUT);
  pinMode(ML4, OUTPUT);

  // OLED Display
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // display i2c address is 0x3C
    Serial.println(F("SSD1306 allocation failed")); // print message if display does not begin
    for (;;); // for loop with empty operators, essentially looping forever

    display.clearDisplay(); // clear display buffer
  }
}

void loop() {

  // display
  displayInputs();
  display.display();

  // movement
  signalCheck();
  move();
  delay(10);
  
}
