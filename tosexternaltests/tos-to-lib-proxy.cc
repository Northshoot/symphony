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
TosToLibProxy::tickTimer(int c){
	int a=0;
	std::cout<<"TosToLibProxy::tickTimer(int c)"<<std::endl;
	while(a<50){
		pass__timerFired(c);
		pass__runNext(a);
		a++;
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
}

TosToLibProxy::TosToLibProxy() {
	a=1;

}

void
TosToLibProxy::setStartMote(void * tos){
	//std::cout<<"TosToLibProxy boot node " << (int)tos <<std::endl;
	pass__sim_main_start_mote=(tosfunc)tos;


}
void
TosToLibProxy::setTimerFired(void *  tos){
	pass__timerFired=(tosfunc)tos;
	//pass__timerFired(a);
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
	std::cout<<"TosToLibProxy boot node " <<std::endl;
	pass__sim_main_start_mote(id);

}

void
TosToLibProxy::startNode(void){
	TosToLibProxy::start_mote(1);
	TosToLibProxy::timerFired(1);
	m_Thread = boost::thread(&TosToLibProxy::tickTimer, this, 1);
	//TosToLibProxy::start_mote(1);
	m_Thread.join();

}
TosToLibProxy::~TosToLibProxy() {

}
