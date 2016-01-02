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

   This is the sketch for the Arduino Yun;
   sends messages to Uno, which drives the motors

   THIS IS CURRENTLY JUST A TEST

*/

#include <Wire.h>
#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4

void setup()
{
  Wire.begin(4);
}

void loop()
{
  forward(150);
  delay(2000);
  halt();
  delay(2000);
  
  backward(150);
  delay(2000);
  halt();
  delay(2000);
  
  right(150);
  delay(2000);
  halt();
  delay(2000);
  
  left(150);
  delay(2000);
  halt();
  delay(2000);
}

void halt(void)
{
  run_motors(0, RELEASE, 0, RELEASE);
}

void forward(int speed)
{
  run_motors(speed, FORWARD, speed, FORWARD);
}


void backward(int speed)
{
  run_motors(speed, BACKWARD, speed, BACKWARD);
}


void right(int speed)
{
  run_motors(speed, FORWARD, speed, BACKWARD);
}


void left(int speed)
{
  run_motors(speed, BACKWARD, speed, FORWARD);
}

  


void run_motors(int speed_left, int direction_left, int speed_right, int direction_right)
{
  Wire.beginTransmission(4);
  Wire.write(speed_left);
  Wire.write(",");
  Wire.write(direction_left);
  Wire.write(",");
  Wire.write(speed_right);
  Wire.write(",");
  Wire.write(direction_right);
  Wire.endTransmission();
}