/* YunBot
  
   Arduino Yun and Uno robot for control via the web
   Following the project in Chapter 4 of Internet of Things with the Arduino Yun by Marco Schwartz
   (his code is at https://github.com/openhomeautomation/geeky-projects-yun/tree/master/chapter4/remote_control)

   Arduino Uno connected to Adafruit motor shield (version 1)
   pin A4 to Yun pin 2
   pin A5 to Yun pin 3
   V5 to Yun VIN
   ground to Yun ground
   
   Using dfrobot Pirate 4WD robot platform, 
   http://www.dfrobot.com/index.php?route=product/product&product_id=97#.VofzU5MrLhO

   This is the sketch for the Arduino Uno;
   receives messages from Yun and drives the motors.

*/

#include <Wire.h>
#include <AFMotor.h>

AF_DCMotor frontleft(1, MOTOR12_1KHZ);
AF_DCMotor backleft(2, MOTOR12_1KHZ);
AF_DCMotor backright(3, MOTOR34_1KHZ);
AF_DCMotor frontright(4, MOTOR34_1KHZ);

void run_motors(int speed_left, int direction_left, int speed_right, int direction_right)
{
  frontleft.setSpeed(speed_left);
  backleft.setSpeed(speed_left);
  frontright.setSpeed(speed_right);
  backright.setSpeed(speed_right);

  frontleft.run(direction_left);
  backleft.run(direction_left);
  frontright.run(direction_right);
  backright.run(direction_right);
}


void setup()
{
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
}

void loop()
{
  delay(100);
}

void receiveEvent(int howMany)
{
  int left_speed = Wire.read();
  char c = Wire.read();
  
  int left_direction = Wire.read();
  c = Wire.read();
  
  int right_speed = Wire.read();
  c = Wire.read();
  
  int right_direction = Wire.read();

  run_motors(left_speed, left_direction,
             right_speed, right_direction);

}
