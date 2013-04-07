/*
 * Generates a real time simulation on ns-3 with a TCP Socket 
 * listening on port 9999 by default. It creates an echo of the 
 * data received.
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
#include "ns3/SkynetNs3ProxyServer.h"

#include "ns3/symphony-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("SkynetNs3ProxyScript");

void Log(uint8_t size, void * buffer){
    typedef struct {
      uint32_t nodeId;
      int32_t counter;

    } NodePacket;

    NodePacket *npkt = (NodePacket*) buffer;

    NS_LOG_UNCOND("[NS3] Node [" << npkt->nodeId << "] sent value " << npkt->counter );
}

int 
main (int argc, char *argv[])
{
  
  NS_LOG_INFO ("Loading Skynet NS3 Proxy Script");
  
  LogComponentEnable("SkynetNs3ProxyScript", LOG_INFO);
  LogComponentEnable("SkynetNs3ProxyServer", LOG_INFO);
  
  // Default network parameters
  std::string deviceName("eth0");
  std::string localIp("172.16.107.142");
  std::string localMask("255.255.255.0");
  std::string localGateway("172.16.107.2");

  int portNumber(9999);
  
  // Default Symphony parameters
  std::string nodeModel("/home/onir/dev/symphony/ns-3.14/build/symphony.xml");
  std::string nodeImage("/home/onir/dev/symphony/ns-3.14/build/libSkynetTos.so");

  // Default simulation time
  std::string simulationTime("60");

  // Allow modification of default network parameters
  CommandLine cmd;
  cmd.AddValue ("deviceName", "Device Name (e.g eth0)", deviceName);
  cmd.AddValue ("localIp", "Local IP address (e.g 192.168.1.100) - It should match with the IP range inside the network to work", localIp);
  cmd.AddValue ("localMask", "Local Network Mask (e.g. 255.255.255.0)", localMask);
  cmd.AddValue ("localGateway", "Local Gateway (e.g. 192.168.1.1)", localGateway);
  cmd.AddValue ("simulationTime", "Simulation time (s) (e.g. 60)", simulationTime);
  cmd.AddValue ("portNumber", "Listening port for the server (e.g 9999)", portNumber);

  cmd.AddValue ("nodeModel", "Full path to XML description of the node (s) (e.g. /home/user/symphony.xml)", simulationTime);
  cmd.AddValue ("nodeImage", "Full path to .so image of TinyOS code (e.g /home/user/libTos.so)", portNumber);

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
  NS_LOG_INFO("- Adding Skynet NS3 IO Server");
  
  Ptr<SkynetNs3ProxyServer> app = CreateObject<SkynetNs3ProxyServer> ();
  node->AddApplication (app);
  app->SetStartTime (Seconds (1.0));
  app->SetStopTime (Seconds (atoi(simulationTime.c_str()))); 
  app->SetAttribute("PortNumber", IntegerValue(portNumber));


  // Configure the TinyOS node
  NS_LOG_INFO("- Creating TinyOS node");

  TosNodeContainer tosNode;
  tosNode.Create(1, nodeImage.c_str());
  tosNode.Get(0)->SetAttribute("TosId", UintegerValue(0));

  // Configure the Symphony Application
  NS_LOG_INFO("- Adding bridge between TinyOs and NS3");

  Ptr<SymphonyApplication> symphonyApp = CreateObject<SymphonyApplication>();
  tosNode.Get(0)->AddApplication(symphonyApp);
  symphonyApp->SetNode(tosNode.Get(0));
  symphonyApp->SetAttribute("ReceiveDataFromApplication", CallbackValue(MakeCallback(&Log)));
  symphonyApp->SetStartTime (Seconds (0.0));
  symphonyApp->SetStopTime (Seconds (20.0));
  symphonyApp->StartApplication();

  // Configuring the sensors available in the node
  NS_LOG_INFO("- Adding sensors");
  TosHelper sens;
  sens.SetNodeModel(nodeModel);
  SymphonySensorContainer sc = sens.InstallSensors(1, tosNode,"/home/onir/dev/symphony/ns-3.14/bin_pkt/");

  // Set the names to access a path
  Names::Add("TemperatureSensor", sc.Get(0));

  // Send a fake temperature to test the system
  // Config::Set("/Names/TemperatureSensor/TemperatureValue", IntegerValue(40));


  // Start the simulation
  NS_LOG_INFO ("- Emulation starting");
  NS_LOG_INFO ("========================");
  
  Simulator::Stop (Seconds (atoi(simulationTime.c_str())));
  Simulator::Run ();
  Simulator::Destroy ();
   
  NS_LOG_INFO ("========================");
  NS_LOG_INFO ("- Emulation finished");
}
