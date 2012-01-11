#include "ns3/core-module.h"
#include "ns3/node-container.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace ns3;

int main(void){

	NodeContainer c;
	c.Create(2);

    ns3::Simulator::Stop(ns3::Seconds(10.0));
    ns3::Simulator::Run();
    std::cout<<"about to destroy "<<std::endl;
    ns3::Simulator::Destroy ();


	return 0;
}
