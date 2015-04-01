#include <Wire.h>

const char i2c_address = 0x52;

unsigned long lastGet = 0;//ms
int jx = 0, jy = 0, accX = 0, accY = 0, accZ = 0, buttonZ = 0, buttonC = 0;
const int light = 7;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);
  pinMode(light, OUTPUT);
  delay(100);
  initNunchuck();

}

void loop() {
  if(millis() - lastGet > 100) {
    get_data();
    lastGet = millis();
  }
  Serial.print("Button Z: ");
  Serial.print(buttonZ);
  Serial.print(", Button C: ");
  Serial.print(buttonC);
  Serial.print(", Joystick: (x,y) (");
  Serial.print(jx);
  Serial.print(", ");
  Serial.print(jy);
  Serial.print("), Acceleration (x,y,z) (");
  Serial.print(accX);
  Serial.print(", ");
  Serial.print(accY);
  Serial.print(", ");
  Serial.print(accZ);
  Serial.println(")");
  
  delay(10);
  if(buttonZ == 0){
    digitalWrite(light, HIGH);
    delay(10);
  }
  else if(buttonZ == 1){
    digitalWrite(light, LOW);
    delay(10);
  }
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
  Wire.write(0x00);
  Wire.endTransmission();
}

void initNunchuck() {
  Wire.beginTransmission(i2c_address);
  Wire.write(0x40);
  Wire.write(0x00);
  Wire.endTransmission();
}
