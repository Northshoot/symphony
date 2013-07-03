/**
 * Configuration of Magnetomiter sensor
 */
 configuration HypervectorInitC
 {
 	provides
 	{
 		interface InterruptWithData;
 		           
 		}
 		
 }
 
 implementation
 {
 	components HypervectorInitP as hv;
 	InterruptWithData = hv.data;
 	
 }
