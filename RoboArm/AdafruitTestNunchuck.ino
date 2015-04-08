/*
This code only moves one servos located at PWM pin 0, 1, 2 on the adafruit board.
*/
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
//need to modify to run from any address besides 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

//Servo pin assignment
const uint8_t bottomPin = 0;
const uint8_t rightPin = 1;
const uint8_t leftPin = 2;

//Initializers
int bottomPos = 0, rightPos = 0, leftPos = 0;

void setup() 
{
  Serial.begin(115200);
  
  //Nunchuck Read
  Wire.begin();
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);
  delay(100);
  initNunchuck();
  
  pwm.begin();
  pwm.setPWMFreq(50);  // Analog servos run at ~60 Hz updates
}

void loop()
{
  get_data();
  
  //Bottom Servo
  bottomPos = map( accX, 65, 180, 1000, 2500);
  //Right Servo
  rightPos = map( buttonZ, 0, 1, 500, 1250);
  //Left Servo
  leftPos = map( jy, 30, 220, 1250, 2400);
  
  // Drive each servo one at a time
  pulseServo( bottomPin, bottomPos);
  pulseServo( rightPin, rightPos);
  pulseServo( leftPin, leftPos);
  
  printDebug();
}

void pulseServo(int servoPin, int pulseLenUs)
{
  pwm.setPWM(servoPin, 0, pulseLenUs);
  delay(1);
}

void get_data()
{
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

void write_i2c_zero()
{
  Wire.beginTransmission(i2c_address);
  Wire.write((byte)0x00);
  Wire.endTransmission();
}

void initNunchuck()
{
  Wire.beginTransmission(i2c_address);
  Wire.write((byte)0x40);
  Wire.write((byte)0x00);
  Wire.endTransmission();
}

//debug
void printDebug() 
{
  Serial.print("accX: ");
  Serial.print(accX);
  Serial.print(", jy: ");
  Serial.print(jy);
  Serial.print(", buttonZ: ");
  Serial.print(buttonZ);
  Serial.print(", bottomPos: ");
  Serial.print(bottomPos);
  Serial.print(", rightPos: ");
  Serial.print(rightPos);
  Serial.print(", leftPos: ");
  Serial.println(leftPos);
}
