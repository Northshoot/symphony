/**
 * Configuration of Application component
 */
 configuration Ns3ApplicationC
 {
    provides
    {
        interface SplitControl;
        interface Ns3Application;
                   
        }
        
 }
 
 implementation
 {
    components Ns3ApplicationP as app;
    
    SplitControl=app.SplitControl;
    Ns3Application=app.Ns3Application;
    
 }