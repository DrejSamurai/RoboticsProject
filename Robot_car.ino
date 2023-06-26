#include <PS4Controller.h>
#include <ESP32Servo.h>

unsigned long lastTimeStamp = 0;
#define TRACK_RIGHT_FORWARD 12
#define TRACK_RIGHT_BACKWARDS 14
#define TRACK_LEFT_FORWARDS 27
#define TRACK_LEFT_BACKWARDS 26
#define Servo1 4
#define Servo2 16
#define Servo3 17
#define Servo4 5
#define Servo5 19
#define Servo6 23

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

int rX;
int rY;
int lX;
int lY;

int posG = 180;
int posG2 = 30;
int posG3 = 30;

void notify()
{
 
}

void onConnect()
{
  Serial.println("Connected!.");
  digitalWrite(18, HIGH);
}

void onDisConnect()
{
  Serial.println("Disconnected!.");
  digitalWrite(18, LOW);    
}

void setup() 
{
  Serial.begin(115200);
  PS4.attach(notify);
  PS4.attachOnConnect(onConnect);
  PS4.attachOnDisconnect(onDisConnect);
  PS4.begin();
  Serial.println("Ready.");
  pinMode(TRACK_RIGHT_FORWARD, OUTPUT);  
  pinMode(TRACK_RIGHT_BACKWARDS, OUTPUT);
  pinMode(TRACK_LEFT_FORWARDS, OUTPUT); 
  pinMode(TRACK_LEFT_BACKWARDS, OUTPUT);
  pinMode(18, OUTPUT); 
  servo1.attach(Servo1);
  servo2.attach(Servo2);
  servo3.attach(Servo3);
  servo4.attach(Servo4);
  servo5.attach(Servo5);
  servo6.attach(Servo6);
}



void loop() 
{
  lX = PS4.LStickX();
  lY = PS4.LStickY();
  rX = PS4.RStickX();
  rY = PS4.RStickY();

  // This moves the gripper claws ------------------------------------------------------->
   if(lY < -5 && posG < 180)
  {
  posG++;
  servo1.write(posG);
  Serial.println(posG);
  delay(10);
  }
  if(lY > 5 && posG > 0)
  {
  posG--;
  servo1.write(posG);
  Serial.println(posG);
  delay(10);
  }
//-----------------------------------------------------------------------------------------------

  // This moves the Roll position of the claws ------------------------------------------------>
  
   if(rY < -5 && posG2 < 180)
  {
  posG2++;
  servo2.write(posG2);
  Serial.println(posG2);
  delay(10);
  }
  if(rY > 5 && posG2 > 0)
  {
   posG2--;
  servo2.write(posG2);
  Serial.println(posG2);
  delay(10);
  }
  //--------------------------------------------------------------------------------------------------

  // This moves the Pitch position of the claws -------------------------------------------------->

if(rX < -5 && posG3 < 180)
  {
  posG3++;
  servo3.write(posG3);
  Serial.println(posG3);
  delay(10);
  }
  if(rX > 5 && posG3 > 0)
  {
   posG3--;
  servo3.write(posG3);
  Serial.println(posG3);
  delay(10);
  }
  //---------------------------------------------------------------------------------------------------------

  // For the first rotational servo servo4 --------------------------------------------------------->
  // Makes it go counter clockwise
  if(PS4.R1() == 1){
    servo4.write(0);
  }
  // Makes it go clockwise
  if(PS4.R2() == 1){
    servo4.write(180);
  }
// Makes it stop
  if(PS4.Triangle() == 1){
    servo4.write(90);
  }
  //--------------------------------------------------------------------------------------------------
  //This moves the base 
      // Makes it go counter clockwise
  if(PS4.L1() == 1){
    servo6.write(0);
  }
  // Makes it go clockwise
  if(PS4.L2() == 1){
    servo6.write(180);
  }
// Makes it stop
  if(PS4.Square() == 1){
    servo6.write(90);
  }
  //----------------------------------------------------------------------

      // Controlls the car to move forward
      if(PS4.Up() == 1){
        digitalWrite(TRACK_RIGHT_FORWARD, HIGH);
        digitalWrite(TRACK_LEFT_FORWARDS, HIGH);
      }else{
        digitalWrite(TRACK_RIGHT_FORWARD, LOW);
        digitalWrite(TRACK_LEFT_FORWARDS, LOW);
      }
      // Controlls the car to move backwards
      if(PS4.Down() == 1){
        digitalWrite(TRACK_RIGHT_BACKWARDS, HIGH);
        digitalWrite(TRACK_LEFT_BACKWARDS, HIGH); 
      }else{
        digitalWrite(TRACK_RIGHT_BACKWARDS, LOW);
         digitalWrite(TRACK_LEFT_BACKWARDS, LOW); 
      }

      // Controlls the car to turn left
      if(PS4.Left() == 1){
        digitalWrite(TRACK_RIGHT_FORWARD, HIGH);
      }else{
        digitalWrite(TRACK_RIGHT_FORWARD, LOW);
      }

      // Controlls the car to turn right
      
      if(PS4.Right() == 1){
        digitalWrite(TRACK_LEFT_FORWARDS, HIGH);
      }else{
        digitalWrite(TRACK_LEFT_FORWARDS, LOW);
      }
      
}
