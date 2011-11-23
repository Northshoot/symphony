/*
 * TosToLibProxy.cpp
 *
 *  Created on: Apr 21, 2010
 *      Author: laurynas
 */
#include <iostream>
#include <boost/thread/thread.hpp>
#include "tos-to-lib-proxy.h"

void
TosToLibProxy::tickTimer(){
	pass__timerFired(a);
	a++;
	boost::this_thread::sleep(boost::posix_time::milliseconds(1));
}

TosToLibProxy::TosToLibProxy() {
	a=1;
	m_Thread = boost::thread(&TosToLibProxy::tickTimer, this);

}

void
TosToLibProxy::setStartMote(void * tos){
	//std::cout<<"TosToLibProxy boot node " << (int)tos <<std::endl;
	pass__sim_main_start_mote=(tosfunc)tos;
	m_Thread.join();
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
