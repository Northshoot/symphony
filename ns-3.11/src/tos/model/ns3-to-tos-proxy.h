/*
 * TosLibProxy.h
 *
 *  Created on: Apr 21, 2010
 *      Author: laurynas
 */

#ifndef NS3TOTOSPROXY_H_
#define NS3TOTOSPROXY_H_
#include <stdint.h>

typedef int (*tosfunc)(int);

typedef int (*tosfuncvoid)(void *);

class Ns3ToTosProxy {
	friend class TosNode;

public:
	Ns3ToTosProxy();

	uint32_t timerFired(uint32_t);
	void start_mote(int id);
	/**
	 * Functions that are proxied
	 */
	void setStartMote(void *  tos);
	void setTimerFired(void *  tos);
	void setDownlink(void * tos);
	void runNextEvent(void *  tos);
	void rxMsg(void *msg);


	~Ns3ToTosProxy();

private:
	tosfunc pass__timerFired;
	tosfunc pass__sim_main_start_mote;
	tosfunc pass__runNext;
	tosfuncvoid pass__rxMsg;

};

#endif /* NS3TOTOSPROXY_H_ */
