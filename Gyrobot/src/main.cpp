#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;


int led = 13;
int ena = 5;
int enb = 6;
int ina = 7;
int inb = 4;
int inc = 9;
int ind = 8;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  mpu.setThreshold(3);
pinMode(led, OUTPUT);
pinMode(ena, OUTPUT);
pinMode(enb, OUTPUT);
pinMode(ina, OUTPUT);
pinMode(inb, OUTPUT);
pinMode(inc, OUTPUT);
pinMode(ind, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  timer = millis();

  // Read normalized values
  Vector norm = mpu.readNormalizeGyro();

  // Calculate Pitch, Roll and Yaw
  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;

  // Output raw
  Serial.print(" Pitch = ");
  Serial.print(pitch);
  Serial.print(" Roll = ");
  Serial.print(roll);  
  Serial.print(" Yaw = ");
  Serial.println(yaw);

  // Wait to full timeStep period
  delay((timeStep*1000) - (millis() - timer));

  if ( yaw <= 3 && yaw >= -3 ) {   // you can increse the range to suit your sensor's accuracy
        digitalWrite(ina, HIGH);
        digitalWrite(inb,HIGH);
        analogWrite(ena, 0);
        digitalWrite(inc,HIGH);
        digitalWrite(ind,HIGH);
        analogWrite(enb, 0); 
        digitalWrite(led, HIGH);
  }
  else {
    if ( yaw < -3 ) {
        digitalWrite(ina, HIGH);
        digitalWrite(inb,LOW);
        analogWrite(ena, 80);
        digitalWrite(inc,LOW);
        digitalWrite(ind,HIGH);
        analogWrite(enb, 80); 
        digitalWrite(led, LOW);
  }

  else {
        digitalWrite(ina, LOW);
        digitalWrite(inb,HIGH);
        analogWrite(ena, 80);
        digitalWrite(inc,HIGH);
        digitalWrite(ind,LOW);
        analogWrite(enb, 80); 
        digitalWrite(led, LOW);
  }
    
  }
}