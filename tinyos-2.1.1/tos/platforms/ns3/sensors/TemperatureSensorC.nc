/**
 * Configuration of Magnetomiter sensor
 */
 
configuration TemperatureSensorC
{
 provides
 {
		interface SplitControl;
 		interface InterruptWithData; 		           		
 }
}
 
 implementation
 {
 	components TemperatureSensorP as sens;
 	
 	SplitControl = sens.SplitControl;
 	InterruptWithData = sens.Data;
 	
 }
 
