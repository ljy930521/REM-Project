#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

#define RightMotorSpeed       5   //14 
#define RightMotorDir         0   //12 
#define LeftMotorSpeed     4   //13 
#define LeftMotorDir       2   //15 

char auth[] = "ZXbWT_mIwk5mIXyYFGXxl4LRy7DKcRfL";
char ssid[] = "OTL";
char pass[] = "9305211066519";

int minRange = 312;
int maxRange = 712;

int minSpeed = 450;
int maxSpeed = 1020;
int noSpeed = 0;

Servo servoX; //  X
Servo servoY; //  Y

// Get from Blynk one virtual variable values of two axes
BLYNK_WRITE(V2) {
  servoX.write(param[0].asInt()); 
  servoY.write(param[1].asInt());
  
}

void moveControl(int x, int y)
{
    if(y >= maxRange && x >= minRange && x<= maxRange)
    {
        digitalWrite(RightMotorDir,HIGH);
        digitalWrite(LeftMotorDir,HIGH);
        analogWrite(RightMotorSpeed, maxSpeed);
        analogWrite(LeftMotorSpeed, maxSpeed);
    }



    else if(x >= maxRange && y >= maxRange)
    {
        digitalWrite(RightMotorDir, HIGH);
        digitalWrite(LeftMotorDir,HIGH);
        analogWrite(RightMotorSpeed,minSpeed);
        analogWrite(LeftMotorSpeed,maxSpeed);
    }


    else if(x <= minRange && y >= maxRange)
    {
        digitalWrite(RightMotorDir,HIGH);
        digitalWrite(LeftMotorDir,HIGH);
        analogWrite(RightMotorSpeed,maxSpeed);
        analogWrite(LeftMotorSpeed,minSpeed);
    }


    else if(y < maxRange && y > minRange && x < maxRange && x > minRange)
    {
        analogWrite(RightMotorSpeed,noSpeed);
        analogWrite(LeftMotorSpeed, noSpeed);
    }


    else if(y <= minRange && x >= minRange && x <= maxRange)
    {
        digitalWrite(RightMotorDir,LOW);
        digitalWrite(LeftMotorDir,LOW);
        analogWrite(RightMotorSpeed,maxSpeed);
        analogWrite(LeftMotorSpeed,maxSpeed);
    }


    else if(y <= minRange && x <= minRange)
    {
        digitalWrite(RightMotorDir,LOW);
        digitalWrite(LeftMotorDir,LOW);
        analogWrite(RightMotorSpeed,minSpeed);
        analogWrite(LeftMotorSpeed,maxSpeed);
    }


    else if(y <= minRange && x >= maxRange)
    {
        digitalWrite(RightMotorDir,LOW);
        digitalWrite(LeftMotorDir,LOW);
        analogWrite(RightMotorSpeed,maxSpeed);
        analogWrite(LeftMotorSpeed,minSpeed);
    }
}

void setup()
{
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);


    pinMode(RightMotorSpeed, OUTPUT);
    pinMode(LeftMotorSpeed, OUTPUT);
    pinMode(RightMotorDir, OUTPUT);
    pinMode(LeftMotorDir, OUTPUT);

    digitalWrite(RightMotorSpeed, LOW);
    digitalWrite(LeftMotorSpeed, LOW);
    digitalWrite(RightMotorDir, HIGH);
    digitalWrite(LeftMotorDir, HIGH);

    // assign our object servo nomber Pin
    servoX.attach(15); // GPIO 15 corresponds to a physical pin D8
    servoY.attach(13); // GPIO 13 corresponds to a physical pin D7


}


void loop()
{

    Blynk.run();
}


BLYNK_WRITE(V1)
{
    int x = param[0].asInt();
    int y = param[1].asInt();
    moveControl(x,y);
}