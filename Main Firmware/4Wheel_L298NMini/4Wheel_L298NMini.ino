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

#include <Wire.h> 
//Read input from the RC receiver
#define CH1 A0 // Aileron signal from RC Tx
#define CH2 A1 // Elevator signal from RC Tx
#define CH3 A2 // Auxilliary signal from RC Tx
#define RSSI A3 // Signal strength indicator from RC Tx

// connect motor controller pins to Arduino digital pins
// front right motor
#define MR1 4
#define MR2 5
// rear right motor
#define MR3 6
#define MR4 7
// front left motor
#define ML1 8
#define ML2 9
// rear left motor
#define ML3 10
#define ML4 11

void setup() {
  Serial.begin(9600);
  //input channels x8r
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(RSSI, INPUT);
  // set all the motor control pins to outputs
  pinMode(MR1, OUTPUT);
  pinMode(MR2, OUTPUT);
  pinMode(MR3, OUTPUT);
  pinMode(MR4, OUTPUT);
  pinMode(ML1, OUTPUT);
  pinMode(ML2, OUTPUT);
  pinMode(ML3, OUTPUT);
  pinMode(ML4, OUTPUT);
}

void loop() {
/*--------------------Debugging for RSSI--------------------*/
//  int RSSISignal = pulseIn(channelRSSI, HIGH); 
//  Serial.print("RSSI: ");
//  Serial.println(RSSISignal);
/*------------------End debugging for RSSI------------------*/

/*-----------------Debugging for channel 1------------------*/
//  int moveSpeed = readMovementDirection();
//  Serial.print("Channel 1: ");
//  Serial.println(moveSpeed);
//  delay(50);
//  int mapSpeed = map(moveSpeed, 980, 2010, 0, 255);
//  Serial.print("Mapped Speed: ");
//  Serial.println(mapSpeed);
  //rightForward(mapSpeed);
  //leftForward(mapSpeed);
/*---------------End Debugging for channel 1----------------*/

/*-----------------Debugging for channel 3------------------*/
//  int turnSpeed = readTurningDirection();
//  Serial.print("Channel 3: ");
//  Serial.println(turnSpeed);
  //int mapTurnSpeed = map(turnSpeed, 980, 2010, 0, 255);
  //Serial.print("Mapped Speed: ");
  //Serial.println(mapTurnSpeed);
  //rightForward(mapSpeed);
  //leftForward(mapSpeed);
/*---------------End Debugging for channel 3----------------*/

  signalCheck();
  sendDirection();
  delay(100);
}
