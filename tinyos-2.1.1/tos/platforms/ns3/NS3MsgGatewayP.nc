#include "sim/sim_main.h"
#include "defines.h"
#include "ns3/calls-to-ns3.h"

void
printTosPacket( char *buf){
    int size = sizeof(message_t);
    int i=0;
    ns3packet_header_t *hdr;
    hdr =(ns3packet_header_t*)(((message_t*)buf)->header);
    printf("FROM TOS - SIZE: %d :: HEADER size: %lu\n", size, sizeof(ns3packet_header_t));
    printf("HEX: ");
    for (;i<size-1;i++){
        printf("%02X ", (uint8_t)buf[i]);
    }
    printf("%02X\n",(uint8_t)buf[i]);
    printf("header: ");
    printf("len %d :: dsn %d :: type %d :: fdest %d :: destpan %d\n",hdr->length,hdr->dsn,hdr->type,hdr->fdest,hdr->destpan);
    printf("dest %d :: src %d :: padd %d\n", hdr->dest,hdr->src,hdr->padd);
}

module NS3MsgGatewayP{
	provides 
	{
		interface BareSend as Send;
		interface BareReceive as Receive;
		interface RadioState as State;
	}
}
implementation{
	
	message_t* msg_out;
	error_t error_out = 0;
	
	message_t* msg_in;
	error_t error_in = 0;
	
	task void sendDone(){
		signal Send.sendDone(msg_out,error_out);
	}
	
	task void receive(){
		signal Receive.receive(msg_in);
	}
        
	extern int receiveMessage(void * msg)@C() @spontaneous(){
		msg_in = (message_t*)msg;
		post receive();
		return 0;
	}
	
    extern int sendSendDone(void * msg, error_t err)@C() @spontaneous(){
    	error_out = err;
    	post sendDone();   
    	return 0; 	
    }
    
    extern int radioStartDone()@C() @spontaneous(){
    	signal State.done();    	
    	return 0;
    }
    

//gatewayRadio(void *obj, DeviceCall call, int val1, int val2, void* hdr, void* msg);	
	command error_t Send.send(message_t* msg){
		msg_out = msg;		
		//printTosPacket((char*)msg);
		a=gatewayRadio(proxy, RADIO_SEND,-1,-1,(void *)msg, (void *) msg);
		post sendDone();
		return 0;
	
	}

	command error_t Send.cancel(message_t* msg){
		return gatewayRadio(proxy, RADIO_CANCEL,-1,-1,(void *)msg, (void *) msg);;
		}
		
	/**
	 * Moves to radio into sleep state with the lowest power consumption but 
	 * highest wakeup time. The radio cannot send or receive in this state 
	 * and releases all access to shared resources (e.g. SPI bus). 
	 */
	tasklet_async command error_t State.turnOff(){
		return 0;
	}

	/**
	 * The same as the turnOff command, except it is not as deep sleep, and
	 * it is quicker to recover from this state.
	 */
	tasklet_async command error_t State.standby(){
		void * buff;
		return gatewayRadio(proxy, RADIO_SLEEP,  -1,-1, buff, buff);
	}

	/**
	 * Goes into receive state. The radio continuously receive messages 
	 * and able to transmit.
	 */
	tasklet_async command error_t State.turnOn(){
		void * buff;
        return gatewayRadio(proxy, RADIO_ON, -1,-1, buff, buff);
	}

	/**
	 * Sets the current channel. Returns EBUSY if the stack is unable
	 * to change the channel this time (some other operation is in progress)
	 * SUCCESS otherwise.
	 */
	tasklet_async command error_t State.setChannel(uint8_t channel){
		void * buff;
        return gatewayRadio(proxy, RADIO_SET_CHANNEL, -1, -1, buff, buff);
	}


	//tasklet_async event void done();

	tasklet_async command uint8_t State.getChannel(){
		void * buff;
		return gatewayRadio(proxy, RADIO_GET_CHANNEL, -1, -1, buff, buff);
		}
}