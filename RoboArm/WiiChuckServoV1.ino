#include <Wire.h>

const int clawPin = 8;
const int armPin = 9;
const int rotPin = 10;
int armPos = 0, clawPos = 0, rotPos = 0;
float wiiP = 0.0;
float wiiPAvg = 0.0;
int lastarmPos = 350;

const char i2c_address = 0x52;
int jx = 0, jy = 0, accX = 0, accY = 0, accZ = 0, buttonZ = 0, buttonC = 0;

void setup() {
  Serial.begin(115200);
  
  //Nunchuck read
  Wire.begin();
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);
  delay(100);
  initNunchuck();
  
  //Servo pins
  pinMode(clawPin, OUTPUT);
  pinMode(armPin, OUTPUT);
  pinMode(rotPin, OUTPUT);
}

void loop() {
  get_data();
  //Right Servo
  armPos = map( buttonZ, 0, 1, 500, 1250);
  //Left Servo
  clawPos = map(jy*100, 30*100, 220*100, 1250, 2400);
  //Bottom Servo
  rotPos = map( accX*100, 65*100, 180*100, 1000, 2500);
  
  pulseServo( armPin, armPos );
  pulseServo( clawPin, clawPos );
  pulseServo( rotPin, rotPos );
  
  printDebug();
}

float runningAvg(float current, float old) {
  float newWeight = 0.3;
  return newWeight * current + ( 1 - newWeight) * old;
}

void pulseServo(int servoPin, int pulseLenUs){
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulseLenUs);
  digitalWrite(servoPin, LOW);
  delay(1);
}

void get_data() {
  int buffer[6];
  Wire.requestFrom(i2c_address, 6);
  int i = 0;
  while(Wire.available()) {
    buffer[i] = Wire.read();
    buffer[i] ^= 0x17;
    buffer[i] += 0x17;
    i++;
  }
  if(i != 6) {
    Serial.println("Error reading from i2c");
  }
  write_i2c_zero();
  
  buttonZ = buffer[5] & 0x01;
  buttonC = (buffer[5] >> 1) & 0x01;
  jx = buffer[0];
  jy = buffer[1];
  accX = buffer[2];
  accY = buffer[3];
  accZ = buffer[4];
}

void write_i2c_zero() {
  Wire.beginTransmission(i2c_address);
  Wire.write((byte)0x00);
  Wire.endTransmission();
}

void initNunchuck() {
  Wire.beginTransmission(i2c_address);
  Wire.write((byte)0x40);
  Wire.write((byte)0x00);
  Wire.endTransmission();
}

//debug
void printDebug() {
  Serial.print("accZ: ");
  Serial.print(accZ);
  Serial.print(", wiiP: ");
  Serial.print(wiiP);
  Serial.print(", wiiPAvg: ");
  Serial.print(wiiPAvg);
  Serial.print(", jx: ");
  Serial.print(jx);
  Serial.print(", jy: ");
  Serial.print(jy);
  Serial.print(", clawPos: ");
  Serial.println(clawPos);
}
