#ifndef _HEADER_H
#define _HEADER_H


#include "Arduino.h"

// Right Motor
const int AMOTOR = 12;
const int ABRAKE = 9;
const int ASPEED = 3;


// Left Motor
const int BMOTOR = 13;
const int BBRAKE = 8;
const int BSPEED = 11;

#define MOTOR_R  LOW // REVERSE GEAR
#define MOTOR_F  HIGH // FORWARD GEAR 



//Front IR sensor 
const int IRsensor = 4;

// LED - Beacon //
int LED_1 = A2;
int LED_2 = A3;


/*Buggy commands*/
typedef enum{
  LEFT,
  RIGHT,
  FWD,
  BWD,
  BRAKE,
  HARD_LEFT,
}Dir_t;

void Buggy_mov(Dir_t New_Dir,uint8_t speed);
void Pins_init();

#endif /*_HEADER_H*/
