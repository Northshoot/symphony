/**
 * Configuration of Magnetomiter sensor
 */
 configuration MagnetomiterC
 {
 	provides
 	{
 		interface SplitControl;
 		interface InterruptWithData;
 		           
 		}
 		
 }
 
 implementation
 {
 	components MagnetomiterP as sens;
 	
 	SplitControl=sens.SplitControl;
 	InterruptWithData=sens.data;
 	
 }