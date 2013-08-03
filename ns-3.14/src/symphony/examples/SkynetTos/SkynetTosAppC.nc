#include "SkynetTos.h"

/**
 * Implementation of a node based on the Skynet project
 *
 * @author Jose Angel Fernandez Rodrigues
 * @date   March 2013
 */

configuration SkynetTosAppC {

}

implementation {
  
  components MainC, SkynetTosC as app;
  components Ns3ApplicationC as Ns3;
  components TemperatureSensorC;
  components ActuatorC;
  components HypervectorInitC;
  
  app.Boot -> MainC.Boot;
  app.AppControl -> Ns3;
  app.Ns3Application -> Ns3;
  
  app.SensorControl -> TemperatureSensorC.SplitControl;
  app.DataIn -> TemperatureSensorC.InterruptWithData;
  
  app.InitVector -> HypervectorInitC.initVector;
  app.RandomVector -> HypervectorInitC.randomVector;
  
  app.ActuatorInput -> ActuatorC.actuatorInputInterrupt;
  app.ActuatorHvInput -> ActuatorC.actuatorHvInputInterrupt;
}


