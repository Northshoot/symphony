#include "../sim/sim_main.h"
#include "defines.h"
#include "ns3/calls-to-ns3.h"

module Ns3ApplicationP
{
    provides
    {
        interface SplitControl;
        interface Ns3Application;
        
    }
}

implementation
{
     command error_t SplitControl.start(){
        gatewayApplication( proxy , APP_ON, 0, (void *)0);
        return 0;
        }
        
    extern int ApplicationStartDone(error_t error)@C() @spontaneous(){
        signal SplitControl.startDone( error );        
        return 0;
    }
    
    command error_t SplitControl.stop(){
    	void *buff;
    	gatewayApplication( proxy ,APP_OFF, 0, (void *)0);
        return 0;
        }
        
    extern int AplicationStopDone(error_t error)@C() @spontaneous(){
        signal SplitControl.stopDone( error );        
        return 0;
    }
    
     command void Ns3Application.SendDataToApplication(uint16_t length, void * buffer){
        gatewayApplication( proxy ,APP_RX, length, buffer);
        }
}