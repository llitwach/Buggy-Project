#include <Ultrasonic.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int8.h>
#include "Buggy.h"

ros::NodeHandle  nh;
bool on_off = false;
bool LED_on_off = false;
bool PIR = false;


void messageCb( const std_msgs::Int8& user_val){

// Command from the User (Phone or Console )

switch (user_val.data)
{
  case 0:       // Buggy Stop
    on_off = false;
    break;
  case 1:      // Buggy Start
    on_off = true;
    break;
  case 2:    // LED on 
    LED_on_off = true;
    break;
  case 3:    // LED off
    LED_on_off = false;
    break;
}


}
 
ros::Subscriber<std_msgs::Int8> sub("CMD_start_stop", &messageCb );

void setup()
{ 
  Serial.begin(57600);
   Serial.println("Start");
   Pins_init();
   delay(5000);
   Serial.write('1');  // signal received from the python script
   
  nh.initNode();
  nh.subscribe(sub);
}

int DistanceB;
int DistanceA;


void loop()
{  
   DistanceA = FrontSensor();
   DistanceB = RightSensor();
   
  
  
  // Turning on and off LED aka GPS 
  
  if (LED_on_off)
  { LED();
  }
  else
  {
  LED_off();
  }
  
  // Check if PIR is High through PySerial
  if(Serial.available() > 0) {
	   
           
            digitalWrite(IRsensor,HIGH);
            delay(100);
            digitalWrite(IRsensor,LOW);
            PIR = true;
            Serial.write('0');
            }
  
  
// 
 // Wall Following Routine  
 if (on_off == true){
  
     
    if ((DistanceA > 20) && (DistanceB > 20)) // Off and Off
     {
    
     Buggy_mov(RIGHT,100);
     Serial.println("Right");
     }
    
     if ((DistanceA < 20) && (DistanceB > 20)) // On and Off
     {
       
      Buggy_mov(HARD_LEFT,100);
      Serial.println("Left");
     }
    
     if ((DistanceA > 20) && (DistanceB < 20)) // Off and On 
       {
     
      Buggy_mov(FWD,100);
      Serial.println("Forward");
      }
  
      if ((DistanceA < 20) && (DistanceB < 20)) // On and On
      {
        Buggy_mov(HARD_LEFT,100);
        Serial.println("Left");
      }
    }// the Buggy would stop if the command stop has been sent (or but not working if the PIR detect a human)
    else if ((on_off == false) || (PIR == true))
    
     {                   
    
    Buggy_mov(FWD,0);
    
    }

    delay(1000);
    
    
    
    
    
    // Random Obstacle avoidance 

//if(DistanceA > 60)
//{ 
//  Buggy_mov(FWD,190);
//    Serial.println("Forward");
//   }
//
//else if (DistanceB > DistanceC)
//{
//  Buggy_mov(RIGHT,190);
//     Serial.println("Right");
//}
//else
//{
//     Buggy_mov(HARD_LEFT,190);
//        Serial.println("Left");
//  
//  }
    
     nh.spinOnce();
      
    }

