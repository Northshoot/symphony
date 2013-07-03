#include "SkynetTos.h"

/**
 * Configuration for the Skynet Tiny OS Node App
 *
 * @author Jose Angel Fernandez Rodrigues
 * @date   March 2013
 */

configuration SkynetTosAppC {

}

implementation {
  
  components MainC, SkynetTosC as app;
  components new TimerMilliC();
  components Ns3ApplicationC as Ns3;
  components TemperatureSensorC;
  components HypervectorInitC;
  
  app.Boot -> MainC.Boot;
  app.AppControl -> Ns3;
  app.MilliTimer -> TimerMilliC;
  app.Ns3Application -> Ns3;
  
  app.SensorControl -> TemperatureSensorC.SplitControl;
  app.DataIn -> TemperatureSensorC.InterruptWithData;
  
  app.HvInit -> HypervectorInitC.InterruptWithData;
  
}


