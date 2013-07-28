
/**
 * Receives the initialization hypervectors from the simulator
 * inside the TinyOS node.
 *
 * @author Jose Angel Fernandez Rodrigues
 * @date   July 2013
 */
 
 configuration HypervectorInitC
 {
 	provides
 	{
 		interface InterruptWithData as initVector;	   
 		interface InterruptWithData as randomVector;        
 	}	
 }
 
 implementation
 {
 	components HypervectorInitP as hv;
 	
 	initVector = hv.initVector;
 	randomVector = hv.randomVector;
 }