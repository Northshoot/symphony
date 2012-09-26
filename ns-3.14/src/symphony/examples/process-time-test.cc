#include <inttypes.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"

using namespace ns3;

void process(struct rusage *p, const char *when)
{
	printf("%s\n", when);
	std::cout <<" /* user time used */                    "<<  p->ru_utime.tv_sec << " " << p->ru_utime.tv_usec  << std::endl;
	std::cout <<" /* system time used */                  "<< " " << p->ru_stime.tv_sec<<p->ru_stime.tv_usec  << std::endl;
	std::cout <<" /* integral shared memory size */       "<<  p->ru_ixrss     <<      std::endl;
	std::cout <<" /* integral unshared data  */           "<<  p->ru_idrss      <<     std::endl;
	std::cout <<" /* integral unshared stack  */          "<<  p->ru_isrss      <<     std::endl;
	std::cout <<" /* page reclaims */                     "<<  p->ru_minflt    <<      std::endl;
	std::cout <<" /* page faults */                       "<<  p->ru_majflt    <<      std::endl;
	std::cout <<" /* swaps */                             "<<  p->ru_nswap     <<      std::endl;
	std::cout <<" /* block input operations */            "<<  p->ru_inblock   <<      std::endl;
	std::cout <<" /* block output operations */           "<<  p->ru_oublock   <<      std::endl;
//	std::cout <<" /* # of characters read/written */      "<<  p->ru_ioch      <<      std::endl;
	std::cout <<" /* messages sent */                     "<<  p->ru_msgsnd    <<      std::endl;
	std::cout <<" /* messages received */                 "<<  p->ru_msgrcv    <<      std::endl;
	std::cout <<" /* signals received */                  "<<  p->ru_nsignals  <<      std::endl;
	std::cout <<" /* voluntary context switches */        "<<  p->ru_nvcsw     <<      std::endl;
	std::cout <<" /* involuntary  */                      "<<  p->ru_nivcsw    <<      std::endl;

}

static void
GenerateTraffic (Ptr<Socket> socket, uint32_t size)
{
  std::cout << "at=" << Simulator::Now ().GetSeconds () << "s, tx bytes=" << size << std::endl;
  socket->Send (Create<Packet> (size));
  if (size > 0)
    {
      Simulator::Schedule (Seconds (0.5), &GenerateTraffic, socket, size - 50);
    }
  else
    {
      socket->Close ();
    }
}

static void
SocketPrinter (Ptr<Socket> socket)
{
  Ptr<Packet> packet;
  while (packet = socket->Recv ())
    { 
      std::cout << "at=" << Simulator::Now ().GetSeconds () << "s, rx bytes=" << packet->GetSize () << std::endl;
    }
}

static void
PrintTraffic (Ptr<Socket> socket)
{
  socket->SetRecvCallback (MakeCallback (&SocketPrinter));
}

void
RunSimulation (void)
{
  NodeContainer c;
  c.Create (10000);
  std::cout << "# nodes " <<c.GetN()<<std::endl;
  InternetStackHelper internet;
  internet.Install (c);


  TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");


  Ptr<Socket> sink = Socket::CreateSocket (c.Get (0), tid);
  InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 80);
  sink->Bind (local);

  Ptr<Socket> source = Socket::CreateSocket (c.Get (0), tid);
  InetSocketAddress remote = InetSocketAddress (Ipv4Address::GetLoopback (), 80);
  source->Connect (remote);
//  std::cout << "# nodes " <<c.GetN()<<std::endl;
//  std::cout << "size of node " <<sizeof(c.Get(0))<<std::endl;
//  std::cout << "size of container " << sizeof(c)<<std::endl;

  GenerateTraffic (source, 500);
  PrintTraffic (sink);


  Simulator::Run ();

  Simulator::Destroy ();
}

int main (int argc, char *argv[])
{
	  int ret;

	  int who= RUSAGE_SELF;
	  struct rusage usage;
	  struct rusage *p=&usage;
	  ret=getrusage(who,p);
	  process(p, "-------------before");
	  std::cout << "ret: " << ret<< std::endl;
  RunSimulation ();
  ret=getrusage(who,p);
  process(p, "-------------before");
  std::cout << "ret: " << ret<< std::endl;
  return 0;
}
