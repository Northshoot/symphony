/*
 * main.c
 *
 *  Created on: Feb 25, 2010
 *      Author: laurynas
 */
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "tiny-bridge.h"

int main(void)
{




	//std::vector<ns3::TosNode * > tos;
	std::vector<TinyBridge *> bridge;
    srand((unsigned)time(0));

    for(int i=0; i<2;i++){
    	std::cout<<"Round ./libtos.so "<<i<<std::endl;

    	bridge.push_back(new TinyBridge("./libtos.so"));
    }



	return 0;
}
