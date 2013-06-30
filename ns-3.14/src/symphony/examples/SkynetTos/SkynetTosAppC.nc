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
  
  components MainC, SkynetTosC as TempApp, SkynetTosC as MagnetoApp;
  components new TimerMilliC();
  components Ns3ApplicationC as Ns3;
  components TemperatureSensorC;
  components MagnetomiterC;
  
  TempApp.Boot -> MainC.Boot;
  TempApp.AppControl -> Ns3;
  TempApp.MilliTimer -> TimerMilliC;
  TempApp.Ns3Application -> Ns3;
  
  TempApp.SensorControl -> TemperatureSensorC.SplitControl;
  TempApp.DataIn -> TemperatureSensorC.InterruptWithData;
  
  MagnetoApp.Boot -> MainC.Boot;
  MagnetoApp.AppControl -> Ns3;
  MagnetoApp.MilliTimer -> TimerMilliC;
  MagnetoApp.Ns3Application -> Ns3;
  
  MagnetoApp.SensorControl -> MagnetomiterC.SplitControl;
  MagnetoApp.DataIn -> MagnetomiterC.InterruptWithData;
  
}


