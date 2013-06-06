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
  
  components MainC, SkynetTosC as App;
  components new TimerMilliC();
  components Ns3ApplicationC as Ns3;
  components TemperatureSensorC;
  
  App.Boot -> MainC.Boot;
  App.AppControl -> Ns3;
  App.MilliTimer -> TimerMilliC;
  App.Ns3Application -> Ns3;
  
  App.SensorControl -> TemperatureSensorC.SplitControl;
  App.DataIn -> TemperatureSensorC.InterruptWithData;
  
}


