/*
 * TosToLibProxy.cpp
 *
 *  Created on: Apr 21, 2010
 *      Author: laurynas
 */
#include <iostream>
#include "TosToLibProxy.h"

TosToLibProxy::TosToLibProxy() {


}
void
TosToLibProxy::setStartMote(void * tos){
	//std::cout<<"TosToLibProxy boot node " << (int)tos <<std::endl;
	pass__sim_main_start_mote=(tosfunc)tos;
}
void
TosToLibProxy::setTimerFired(void *  tos){
	pass__timerFired=(tosfunc)tos;
}
void
TosToLibProxy::runNextEvent(void *  tos){
	pass__runNext=(tosfunc)tos;
}
uint32_t
TosToLibProxy::timerFired(uint32_t a){
	//std::cout<<"TosToLibProxy::timerFired() "<<a<<std::endl;
	pass__timerFired(a);

	return a;
}

void
TosToLibProxy::start_mote(int id){
//	std::cout<<"TosToLibProxy boot node " <<std::endl;
	pass__sim_main_start_mote(id);

}

TosToLibProxy::~TosToLibProxy() {

}
