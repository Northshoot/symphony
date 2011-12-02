/*
 * TosLibProxy.h
 *
 *  Created on: Apr 21, 2010
 *      Author: laurynas
 */

#ifndef TOSTOLIBPROXY_H_
#define TOSTOLIBPROXY_H_
#include <stdint.h>
#include <boost/thread/thread.hpp>

typedef int (*tosfunc)(int);

class TosToLibProxy {
	friend class TinyBridge;
public:
	TosToLibProxy();
	uint32_t timerFired(uint32_t);
	void start_mote(int id);
	/**
	 * Functions that are proxied
	 */
	void setStartMote(void *  tos);
	void setTimerFired(void *  tos);
	void runNextEvent(void *  tos);
	void startNode(void);

	~TosToLibProxy();

private:
	tosfunc pass__timerFired;
	tosfunc pass__sim_main_start_mote;
	tosfunc pass__runNext;
	void tickTimer(int c);
	int a;
	boost::thread    m_Thread;
};

#endif /* TOSTOLIBPROXY_H_ */
