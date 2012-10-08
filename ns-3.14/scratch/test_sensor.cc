/**
 * Show case of sensor model
 * It only reads specified data and
 * run interminal
 * export NS_LOG=RawSensor
 * then
 * ./waf --run="test_sensor"
 */

#include "ns3/symphony-module.h"
#include "ns3/ptr.h"
#include "ns3/core-module.h"

using namespace ns3;
using namespace std;
int
main(int argc, char *argv[]){
  //LogComponentEnableAll(LOG_ALL);
  Ptr<RawSensor> sens= CreateObject<RawSensor>();
  sens->SetAttribute ("SensorDataPath", StringValue ("/home/lauril/dev/symphony/ns-3.14/bin_pkt/"));
  sens->DoStart();

  //Uncomment if you want to run simpler simulation
  //Simulator::Stop(Seconds(1000));
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
