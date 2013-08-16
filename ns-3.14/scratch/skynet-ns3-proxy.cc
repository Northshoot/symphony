/*
 * 
 *
 * @author Jose Angel Fernandez Rodrigues
 */ 

#include "ns3/abort.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "ns3/emu-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-static-routing-helper.h"
#include "ns3/ipv4-list-routing-helper.h"
#include "ns3/io-proxy-server-application.h"
#include "ns3/hv-base-station-application.h"

#include "ns3/symphony-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("SkynetNs3ProxyScript");

int 
main (int argc, char *argv[])
{
  
  NS_LOG_INFO ("Loading Skynet NS3 Proxy Script");
  
  LogComponentEnable("SkynetNs3ProxyScript", LOG_INFO);
  LogComponentEnable("IOProxyServer", LOG_INFO);
  LogComponentEnable("SymphonyApplication", LOG_INFO);
  
  // IO Proxy default network parameters
  std::string deviceName("eth0");
  std::string localIp("172.16.107.142");
  std::string localMask("255.255.255.0");
  std::string localGateway("172.16.107.2");
  int localPortNumber(3333);

  // Backend Server default network parameters
  std::string remoteIp("172.16.107.1");
  int remotePortNumber(9999);

  // Default Symphony parameters
  std::string nodeModel("/home/onir/dev/skynet/ns-3.14/build/symphony.xml");
  std::string nodeImage("/home/onir/dev/skynet/ns-3.14/build/libSkynetTos.so");
  int nodePairsNumber(2);

  // Default simulation time
  std::string simulationTime("60");

  // Allow modification of default network parameters
  CommandLine cmd;
  cmd.AddValue ("deviceName", "Device Name (e.g eth0)", deviceName);

  cmd.AddValue ("localIp", "Local IP address (e.g 192.168.1.100) - It should match with the IP range inside the network to work", localIp);
  cmd.AddValue ("localMask", "Local Network Mask (e.g. 255.255.255.0)", localMask);
  cmd.AddValue ("localGateway", "Local Gateway (e.g. 192.168.1.1)", localGateway);
  cmd.AddValue ("localPortNumer", "Local Port Number (e.g 3333)", localPortNumber);

  cmd.AddValue ("remoteIp", "Remote IP address (e.g 172.16.107.1)", remoteIp);
  cmd.AddValue ("remotePortNumber", "Listening port for the server (e.g 9999)", remotePortNumber);

  cmd.AddValue ("simulationTime", "Simulation time (s) (e.g. 60)", simulationTime);

  cmd.AddValue ("nodeModel", "Full path to XML description of the node (s) (e.g. /home/user/symphony.xml)", simulationTime);
  cmd.AddValue ("nodeImage", "Full path to .so image of TinyOS code (e.g /home/user/libTos.so)", nodeImage);
  cmd.AddValue ("nodePairsNumber", "Number of sensor&actuator pairs to configure the simulation. (e.g. 1 = one sensors & one actuator", nodePairsNumber);

  cmd.Parse (argc, argv);
  
  // Configure the simulation as a real time and checksum enabled 
  // simulation to allow the communication with nodes outside.
  GlobalValue::Bind ("SimulatorImplementationType", StringValue ("ns3::RealtimeSimulatorImpl"));
  GlobalValue::Bind ("ChecksumEnabled", BooleanValue (true));

  // Configuration of the Skynet proxy node
  NS_LOG_INFO ("- Create IO Server Node");
  
  Ptr<Node> node = CreateObject<Node>();

  // Create an emu device, allocate a MAC address and point the device to the 
  // Linux device name.  The device needs a transmit queueing discipline so
  // create a droptail queue and give it to the device.  Finally, "install" 
  // the device into the node.
  NS_LOG_INFO ("- Create Emulation Device");
  
  Ptr<EmuNetDevice> device = CreateObject<EmuNetDevice> ();
  device->SetAttribute ("Address", Mac48AddressValue (Mac48Address::Allocate ()));
  device->SetAttribute ("DeviceName", StringValue (deviceName));

  Ptr<Queue> queue = CreateObject<DropTailQueue> ();
  device->SetQueue (queue);

  node->AddDevice (device);

  // Add a default internet stack to the node.
  NS_LOG_INFO ("- Add Internet Stack ");
  
  InternetStackHelper internetStackHelper;
  internetStackHelper.Install (node);

  NS_LOG_INFO ("- Add IPv4 Interface");
  
  Ipv4Address ip (localIp.c_str() );
  Ipv4Mask mask (localMask.c_str() );
  
  Ptr<Ipv4> ipv4 = node->GetObject<Ipv4> ();
  uint32_t interface = ipv4->AddInterface (device);
  Ipv4InterfaceAddress address = Ipv4InterfaceAddress (ip, mask);
  ipv4->AddAddress (interface, address);
  ipv4->SetMetric (interface, 1);
  ipv4->SetUp (interface);

  // Configure the default path to route the packets
  NS_LOG_INFO("- Add Default Route");
  
  Ipv4Address gateway (localGateway.c_str());

  Ipv4StaticRoutingHelper ipv4RoutingHelper;
  Ptr<Ipv4StaticRouting> staticRouting = ipv4RoutingHelper.GetStaticRouting (ipv4);
  staticRouting->SetDefaultRoute (gateway, interface);

  // Configure the application running on the node
  NS_LOG_INFO("- Adding IO Proxy Server");
  
  Ptr<IOProxyServer> ioApp = CreateObject<IOProxyServer> ();
  ioApp->SetStartTime(Seconds (1.0));
  ioApp->SetStopTime(Seconds (atoi(simulationTime.c_str())-1));
  ioApp->SetAttribute("RemotePortNumber", IntegerValue(remotePortNumber));
  ioApp->SetAttribute("RemoteIp", StringValue(remoteIp));
  ioApp->SetAttribute("LocalPortNumber", IntegerValue(localPortNumber));
  ioApp->SetAttribute("LocalIp", StringValue(localIp));
  ioApp->SetAttribute("NodePairsNumber", IntegerValue(nodePairsNumber));
  node->AddApplication (ioApp);

  Names::Add("IOServer", ioApp);

  // Configure the TinyOS node
  NS_LOG_INFO("- Creating TinyOS node");

  TosNodeContainer tosNode;
  tosNode.Create(nodePairsNumber * 2, nodeImage.c_str());

  // Configure the Symphony Application
  NS_LOG_INFO("- Adding bridge between TinyOs and NS3");

  Ptr<SymphonyApplication> symphonyApp = CreateObject<SymphonyApplication>();
  symphonyApp->SetNode(tosNode.Get(0));
  symphonyApp->SetStartTime (Seconds (0.0));
  symphonyApp->SetStopTime (Seconds (20.0));
  symphonyApp->StartApplication();

  // Configuring the sensors available in the node
  NS_LOG_INFO("- Adding sensors");
  TosHelper sens;
  sens.SetNodeModel(nodeModel);
  SymphonySensorContainer sc = sens.InstallSensors(1, tosNode,"/home/onir/dev/symphony/ns-3.14/bin_pkt/");

  // Set properties of the nodes

  for (int i = 0; i < nodePairsNumber; i++ )
  {
	  char numstr[21]; // enough to hold all numbers up to 64-bits

	  //Set sensor properties
	  tosNode.Get(i)->SetAttribute("TosId", UintegerValue(i));
	  tosNode.Get(i)->AddApplication(symphonyApp);

	  //Set sensor identification string
	  sprintf(numstr, "%d", i);
	  std::string name = "TemperatureSensor";
	  std::string result = name + numstr;
	  Names::Add(result, sc.Get(i));

	  //Set actuator properties
	  tosNode.Get(i + nodePairsNumber)->SetAttribute("TosId", UintegerValue(i + nodePairsNumber));
	  tosNode.Get(i + nodePairsNumber)->AddApplication(symphonyApp);

	  //Set actuator identification string
	  sprintf(numstr, "%d", i);
	  name = "Actuator";
	  result = name + numstr;
	  Names::Add(result, sc.Get(i + nodePairsNumber));
  }

  NS_LOG_INFO("- Adding HV Base Station");
  Ptr<HvBaseStation> bsApp = CreateObject<HvBaseStation> (tosNode);
  bsApp->SetStartTime(Seconds (1.0));
  bsApp->SetStopTime(Seconds (atoi(simulationTime.c_str())-1));
  node->AddApplication (bsApp);
  Names::Add("BaseStation", bsApp);

  // Start the simulation
  NS_LOG_INFO ("- Emulation starting");
  NS_LOG_INFO ("========================");
  
  Simulator::Stop (Seconds (atoi(simulationTime.c_str())));
  Simulator::Run ();
  Simulator::Destroy ();
   
  NS_LOG_INFO ("========================");
  NS_LOG_INFO ("- Emulation finished");
}
