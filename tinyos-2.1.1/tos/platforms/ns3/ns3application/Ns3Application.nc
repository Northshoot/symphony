/**
 * Ns3Application interface provides means to send data to the ns3 application
 * from TinyOS
 * Intension of usage for the communications "like-to" gateway.
 * 
 * @author Laurynas Riliskis
 */

 interface Ns3Application {
    
    /**
     * Signals the completion of data reading
     * 
     * @param buffer, pointer to the buffer were the data is
     * @param length, the size of the buffer
     * 
     * Note: when function return, the buffer is reused.
     */
     
     command void SendDataToApplication( uint16_t length, void * buffer);
 }