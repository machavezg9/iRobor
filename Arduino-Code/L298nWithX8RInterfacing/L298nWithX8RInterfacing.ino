//This code was written and tested using and arduino uno r3
#include <Wire.h> 
//Read input from the x8r and the taranis
#define channel1 9
#define channel3 10
#define channelRSSI 5

// connect motor controller pins to Arduino digital pins
// motor one
#define enA 11
#define in1 12
#define in2 13
// motor two
#define enB 3
#define in3 2
#define in4 4

void setup() {
  Serial.begin(9600);
  //input channed 1 x8r
  pinMode(channel1, INPUT);
  pinMode(channel3, INPUT);
  pinMode(channelRSSI, INPUT);
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
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

