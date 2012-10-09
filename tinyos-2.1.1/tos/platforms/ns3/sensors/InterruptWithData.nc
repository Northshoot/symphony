/**
 * The InterruptWithData interface is intended for interrupt based sensor.
 * based sensors.
 * Then the interrupt event happens sensor will read the data and 
 * signal sensor reading.
 * 
 * @author Laurynas Riliskis
 */

 interface InterruptWithData {
 	
 	/**
 	 * Signals the completion of data reading
 	 * 
 	 * @param result SUCCESS if the data gathering was successful
 	 * @param buffer, pointer to the buffer were the data is
 	 * @param length, the size of the buffer
 	 * 
 	 * Note: when function return, the buffer is reused.
 	 */
 	 
 	 async event void interruptWithData(error_t result, uint16_t length, void * buffer);
 }