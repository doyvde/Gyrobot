#include<Wire.h>
#include<MPU6050.h>

MPU6050 mpu;

int16_t AccX, AccY, AccZ;
float AccAngleX, AccAngleY, GyroAngleX, GyroAngleY, KalAngleX, KalAngleY;
float roll, pitch;

void setup()
{
  Wire.begin();
  mpu.initialize();
}

void loop()
{
  mpu.getAcceleration(&AccX, &AccY, &AccZ);
  AccAngleX = atan((float)AccY / sqrt(pow((float)AccX, 2) + pow((float)AccZ, 2))) * 57.29578;
  AccAngleY = atan((float)AccX / sqrt(pow((float)AccY, 2) + pow((float)AccZ, 2))) * 57.29578;
  
  KalAngleX = AccAngleX;
  KalAngleY = AccAngleY;
  
  Serial.print("Roll: ");
  roll = KalAngleX * 0.96 + GyroAngleX * 0.04;
  Serial.print(roll);
  Serial.print(", Pitch: ");
  pitch = KalAngleY * 0.96 + GyroAngleY * 0.04;
  Serial.println(pitch);
  
  delay(10);
}