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
#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

// used by Adafruit AFMotor library
#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4

// speed
#define SPEED 170
#define SPEED_TURN 190
// adjustment forward/backward
#define SPEED_ADJ 25

// web server
YunServer server;

void setup()
{
  Wire.begin();
  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();
}

void loop()
{
  YunClient client = server.accept();

  if(client) {
    // process request
    process(client);

    // close connection
    client.stop();
  }

  delay(50);
}

// Process called when the REST API is called
void process(YunClient client)
{
  String command = client.readStringUntil('/');
  if(command == "robot") {
    robotCommand(client);
  }
}

// Process robot commands
void robotCommand(YunClient client)
{
  String command = client.readStringUntil('\r');
  if(command=="stop") {
    halt();
  } else if(command=="forward") {
    forward(SPEED);
  } else if(command=="backward") {
    backward(SPEED);
  } else if(command=="right") {
    right(SPEED_TURN);
  } else if(command=="left") {
    left(SPEED_TURN);
  }
}


void halt(void)
{
  run_motors(0, RELEASE, 0, RELEASE);
}

void forward(int speed)
{
  run_motors(speed+SPEED_ADJ, FORWARD, speed, FORWARD);
}


void backward(int speed)
{
  run_motors(speed+SPEED_ADJ, BACKWARD, speed, BACKWARD);
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