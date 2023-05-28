//Installing necessary libraries
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Servo.h>


Adafruit_MPU6050 mpu;

//Defined Servo
Servo leftServo;
Servo rightServo;

//Varibles

double angleXP = 0.0;
double targetAngle = 78;
double Kp = 6.0;
double Ki = 0.2;  // Terme intégral
double Kd = 0.5;
double lastError = 0.0;
double totalError = 0.0;  // Erreur cumulée
double dt = 15.0;

int baseSpeed = 90;



void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.begin();

  //setting the pinmodes
  leftServo.attach(11);
  rightServo.attach(10);

  //Init des servo
  leftServo.write(90);  // set servo to mid-point
  rightServo.write(90);  // set servo to mid-point

  delay(5000);
}

void loop() {
  // lecture des données brutes de la centrale inertielle
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);

  // conversion des données brutes en degrés d'inclinaison
  double angleX = atan2(-accel.acceleration.y, -accel.acceleration.z) * (180 / M_PI);


  int angleXP = -angleX;




  // Contrôle des servomoteurs pour maintenir l'équilibre
  double error = angleXP - targetAngle;
  totalError += error;  // Accumulation de l'erreur
  double pwm = Kp * error + Ki * totalError + Kd * (error - lastError) / dt;
  
  lastError = error;
  pwm = constrain(pwm, -255, 255);
  Serial.println(pwm);

  int leftSpeed = baseSpeed + pwm;
  int rightSpeed = baseSpeed - pwm;

  leftServo.write(map(leftSpeed, -255, 255, 0, 180));
  rightServo.write(map(rightSpeed, -255, 255, 0, 180));

  // Attente de la prochaine boucle
  
  delay(dt);
}