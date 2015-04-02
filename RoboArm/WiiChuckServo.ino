#include <Wire.h>

const int rotatePin = 8;
const int verticalPin = 9;
const int expandPin = 7;
int vertPos = 0, rotPos = 0, extPos = 0;
float wiiP = 0.0;
float wiiPAvg = 0.0;
int lastarmPos = 350;

const char i2c_address = 0x52;
unsigned long lastGet = 0;//ms
int jx = 0, jy = 0, accX = 0, accY = 0, accZ = 0, buttonZ = 0, buttonC = 0;
const int light = 6;

void setup() {
  Serial.begin(115200);
  //Nunchuck read
  Wire.begin();
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);
  pinMode(light, OUTPUT);
  delay(100);
  initNunchuck();
  
  //Servo pins
  pinMode(rotatePin, OUTPUT);
  pinMode(verticalPin, OUTPUT);
}

void loop() {
//  if(millis() - lastGet > 100) {
//    get_data();
//    lastGet = millis();
//  }
  get_data();
  
  wiiP = (accZ - 70.0)/(178.0 - 70.0);
  if (accY > 120 && accZ > 100) wiiP = 1;
  if (accY > 120 && accZ < 100) wiiP = 0;
  if (wiiP > 1) wiiP = 1;
  if (wiiP < 0) wiiP = 0;
  wiiPAvg = runningAvg( wiiP, wiiPAvg);
  vertPos = map( wiiPAvg * 10 * 100, 0, 1, 1000, 2000);
  //1000-2000
  extPos = map(jy, 30, 220, 1000, 2500);
  //1000 - 2500
  rotPos = map(jx, 30, 220, 1250, 2250);
  
  pulseServo( verticalPin, vertPos );
  pulseServo( rotatePin, rotPos );
  pulseServo( expandPin, extPos );
  
  printDebug();
  if(buttonZ == 0){
    digitalWrite(light, HIGH);
    delay(10);
  }
  else if(buttonZ == 1){
    digitalWrite(light, LOW);
    delay(10);
  }
}

float runningAvg(float current, float old) {
  float newWeight = 0.3;
  return newWeight * current + ( 1 - newWeight) * old;
}

void pulseServo(int servoPin, int pulseLenUs){
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulseLenUs);
  digitalWrite(servoPin, LOW);
  delay(15);
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
  Serial.print(", jy: ");
  Serial.print(jy);
  Serial.print(", rotPos: ");
  Serial.println(rotPos);
  
//  Serial.print("Button Z: ");
//  Serial.print(buttonZ);
//  Serial.print(", Button C: ");
//  Serial.print(buttonC);
//  Serial.print(", Joystick: (x,y) (");
//  Serial.print(jx);
//  Serial.print(", ");
//  Serial.print(jy);
//  Serial.print("), Acceleration (x,y,z) (");
//  Serial.print(accX);
//  Serial.print(", ");
//  Serial.print(accY);
//  Serial.print(", ");
//  Serial.print(accZ);
//  Serial.println(")");
//  delay(10);
}
