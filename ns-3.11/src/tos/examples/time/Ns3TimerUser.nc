

#include "Timer.h"
#include <stdio.h>

module Ns3TimerUser 
{
  uses interface Timer<TMilli> as Timer0;
  uses interface Timer<TMilli> as Timer1;
//  uses interface Timer<TMilli> as Timer2;
//  uses interface Timer<TMilli> as Timer3;
  uses interface Boot;
}
implementation
{

uint16_t t1=0;
uint16_t t2=2;
uint16_t t3=3;

uint16_t ev = 0;

  event void Boot.booted()
  {
    printf("boot.booted\n");
    call Timer0.startPeriodic( 500 );
    call Timer1.startPeriodic(490);



  }

  event void Timer1.fired()
  {
    printf("Node %d fired timer %d event %d\n", TOS_NODE_ID, 1, ev);
    ev++; 
  }
  
  event void Timer0.fired()
  {
   
      //printf("Node %d fired timer startOneShot %d event %d\n", TOS_NODE_ID, 0, ev);
      //call Timer0.startPeriodic( 500 );

    printf("Node %d fired timer %d event %d\n", TOS_NODE_ID, 0, ev);
    ev++; 
    
  }

}

