#include "sim/sim_main.h"
#include "defines.h"
#include "sim_packet.h"

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
	

        
//     Foo f;
	task void sendDone(){
		signal Send.sendDone(msg_out,error_out);
	}
	
	task void receive(){
		signal Receive.receive(msg_in);
	}
	
	command error_t Send.send(message_t* msg){
		ns3pack fo;
//		int a=100;
		fo = convertToNS3(msg);
		msg_out = msg;
		printf("NS3MsgGatewayP.Send.send: size of sent msg %lu\n", sizeof(fo));
		a=gatewayRadio(proxy, 0,  &fo, msg);
		printf("gatewayRadio(proxy, 0, f) return: %d\n", a);
		post sendDone();
		return 0;
	
	}
	

	command error_t Send.cancel(message_t* msg){
		return 0;
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
		return 0;
	}

	/**
	 * Goes into receive state. The radio continuously receive messages 
	 * and able to transmit.
	 */
	tasklet_async command error_t State.turnOn(){
		return 0;
	}

	/**
	 * Sets the current channel. Returns EBUSY if the stack is unable
	 * to change the channel this time (some other operation is in progress)
	 * SUCCESS otherwise.
	 */
	tasklet_async command error_t State.setChannel(uint8_t channel){
		return 0;
	}


	//tasklet_async event void done();

	tasklet_async command uint8_t State.getChannel(){
		return 0;
		}
}