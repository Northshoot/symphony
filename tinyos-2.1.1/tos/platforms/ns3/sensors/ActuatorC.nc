
/**
 * Receives the initialization hypervectors from the simulator
 * inside the TinyOS node.
 *
 * @author Jose Angel Fernandez Rodrigues
 * @date   July 2013
 */
 
 configuration ActuatorC
 {
 	provides
 	{
 		interface InterruptWithData as actuatorInputInterrupt;	   
 		interface InterruptWithData as actuatorHvInputInterrupt;        
 	}	
 }
 
 implementation
 {
 	components ActuatorP as act;
 	
 	actuatorInputInterrupt = act.actuatorInputInterrupt;
 	actuatorHvInputInterrupt = act.actuatorHvInputInterrupt;
 }
