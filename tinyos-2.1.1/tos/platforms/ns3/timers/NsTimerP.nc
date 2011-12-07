#include "Timer.h"

#include "sim/sim_main.h"




module NsTimerP
{
  provides {
    interface Init;
    interface Timer<TMilli> as Timer;
  
  }

}
implementation
{

uint32_t time_now=0;
typedef struct
  {
    uint32_t t0;
    uint32_t dt;
    uint32_t shoot;
    bool isoneshot : 1;
    bool isrunning : 1;
    bool _reserved : 6;
  } Timer_t;
 
Timer_t m_timer;

  void updateTimer(){
    //printf("updateTimer( %i\n",  time_now);
    if(m_timer.shoot == time_now) {
        printf("m_timer.shoot == time_now %i\n",  time_now);
        signal Timer.fired();
    } 

  } 
  
extern int tickFired(uint32_t a) @C() @spontaneous() {
  //printf("Timer.thisFired %i\n",  a);
  atomic time_now = a;
 updateTimer();
 runNextEventExternal(0);
  //printf("Timer.thisFired %i\n",  time_now);
  signal Timer.fired();
  return 0;
  }
   
 
  
  command void Timer.startPeriodic(uint32_t dt){
//    
//       int a=gateway(proxy,0,dt);
//       printf("Timer.startPeriodic %i return code %i\n", dt, a);
        
    }


  command void Timer.startOneShot(uint32_t dt)
  {

    printf("Timer.startOneShot(uint32_t dt) %i\n", dt);
    }


  command void Timer.stop()  {
    //printf("Timer.stop() \n");
        atomic {
    m_timer.isoneshot = FALSE;
    m_timer.dt = 0;
    m_timer.t0=0;
    m_timer.shoot = 0;
    m_timer.isrunning = FALSE;
    }
    }




  command bool Timer.isRunning()  {
   return m_timer.isrunning;
    }


  command bool Timer.isOneShot()  {
    return m_timer.isoneshot;
    }

  command void Timer.startPeriodicAt(uint32_t t0, uint32_t dt)  {
    
    printf("Timer.startPeriodicAt(uint32_t %i, uint32_t %i) \n", t0, dt);
    
    }


  command void Timer.startOneShotAt(uint32_t t0, uint32_t dt){
    atomic {
	    m_timer.isoneshot = TRUE;
	    m_timer.dt = dt;
	    m_timer.t0=t0;
	    m_timer.shoot = t0+dt;
	    m_timer.isrunning = TRUE;
    }
    printf("Timer.startOneShotAt(time_now %i t0 %i, dt %i m_timer.shoot % i) \n", time_now, t0, dt,m_timer.shoot);
    updateTimer();
     }


  command uint32_t Timer.getNow()  {
    //printf("Timer.getNow %i\n", time_now);
    return time_now;//gateway(proxy, 1, 0);
    
    }


  command uint32_t Timer.gett0()  {
    printf("Timer.gett0() \n");
    return 0;
    }


  command uint32_t Timer.getdt()  {
    printf("Timer.getdt() \n");
    return 0;
    }
    



  command error_t Init.init(){
    atomic time_now=0;
    printf(" Init.init() \n");
    return 0;
  }
}