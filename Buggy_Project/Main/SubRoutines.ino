#include "Buggy.h"

void Pins_init()
{

// initialise pins for right motor 
pinMode(AMOTOR, OUTPUT);
pinMode(ABRAKE, OUTPUT);

// initialise pins for left motor 
pinMode(BMOTOR, OUTPUT);
pinMode(BBRAKE, OUTPUT);


// initialise LED pins 
pinMode(LED_1, OUTPUT);
pinMode(LED_2, OUTPUT);

pinMode(IRsensor,OUTPUT);

}

///////////////////////////////////////////////////////////////////////////
//////////////////////////////////////MOTOR/////////////////////////////////////


//// Motors Controls ///

void Buggy_mov(Dir_t New_Dir, uint8_t speed)
{
  if(speed)
  {
    switch(New_Dir){
      case LEFT:
        digitalWrite(BMOTOR,MOTOR_R);
        digitalWrite(AMOTOR,MOTOR_R);
        analogWrite(ASPEED,speed);
        analogWrite(BSPEED,speed-speed/2);
        break;
      case RIGHT:
        digitalWrite(BMOTOR,MOTOR_F);
        digitalWrite(AMOTOR,MOTOR_F);
        analogWrite(ASPEED,speed-speed/2);
        analogWrite(BSPEED,speed);
        break;
      case FWD:
        digitalWrite(BMOTOR,MOTOR_F);
        digitalWrite(AMOTOR,MOTOR_R);
        analogWrite(ASPEED,speed);
        analogWrite(BSPEED,speed);
        break;
      case BWD:
        digitalWrite(BMOTOR,MOTOR_R);
        digitalWrite(AMOTOR,MOTOR_F);
        analogWrite(ASPEED,speed);
        analogWrite(BSPEED,speed);
        break;
      case HARD_LEFT:
        digitalWrite(BMOTOR,MOTOR_R);
        digitalWrite(AMOTOR,MOTOR_R);
        analogWrite(ASPEED,speed);
        analogWrite(BSPEED,0);
        break;
      default:
        analogWrite(ASPEED,0);
        analogWrite(BSPEED,0);
        break;
    }
  }
  else
  {
    analogWrite(ASPEED,0);
    analogWrite(BSPEED,0);
  }
}


/////////////////////////////////////////////////////////////////////////////
//////////////////////////LED/////////////////////////////////////////


// LED on and off Routine////

void LED()
{
digitalWrite(LED_1,HIGH);     // Turn on all 4 LEDs
digitalWrite(LED_2,HIGH); 


delay(1000);                 // Waits for 1 second

digitalWrite(LED_1,LOW);     // Turn off all 4 LEDs
digitalWrite(LED_2,LOW);


delay(1000);                // Waits for 1 second


}

void LED_off()
{

digitalWrite(LED_1,LOW);     // Turn off all 4 LEDs
digitalWrite(LED_2,LOW);


}


////////////////////////////////////////////////////////////////////////////////
///////////////////////// ULTRASONIC SENSOR/////////////////////////////////




int FrontSensor()
{

    // initialise Pin Trig and Echo respectively 
Ultrasonic ultrasonic1(5,6);

    // Convert to cm
int DistanceA =(ultrasonic1.Ranging(CM));

  // return the Distance value
  return DistanceA;
 
 }

  int RightSensor()
{

// initialise Pin Trig and Echo respectively 
Ultrasonic ultrasonic2(10,7);

 // Convert to cm
int DistanceB =(ultrasonic2.Ranging(CM));

// return the Distance value 
  return DistanceB;
 
  }


    int LeftSensor()
{
  
  // initialise Pin Trig and Echo respectively 
Ultrasonic ultrasonic3(18,19);

  // Convert to cm
int DistanceC =(ultrasonic3.Ranging(CM));
  
  // return the Distance value 
  return DistanceC;  
  }

