
/*
 * ns3-to-tos-proxy.h
 *
 *  Created on: Mars 20, 2011
 *      Author: laurynas
 *     Autogenerated on: 2013-04-23
 */
 

#ifndef NS3TOTOSPROXYAUTO_H_
#define NS3TOTOSPROXYAUTO_H_
#include <stdint.h>
#include <string>
#include <map>

typedef int(*tossendDone)(void *,uint8_t); //typedef for tos function sendDone(void * b , uint8_t c) 
typedef void(*tosradioStartDone)(int); //typedef for tos function radioStartDone(int b) 
typedef int(*tossetUniqueID)(int); //typedef for tos function setUniqueID(int b) 
typedef void(*tossim_main_start_mote)(int); //typedef for tos function sim_main_start_mote(int b) 
typedef int(*tossetProxy)(long); //typedef for tos function setProxy(long b) 
typedef int(*tostickFired)(uint32_t); //typedef for tos function tickFired(uint32_t b) 
typedef int(*tosradioStateDone)(); //typedef for tos function radioStateDone() 
typedef int(*tosreceiveMessage)(void *); //typedef for tos function receiveMessage(void * b) 
typedef int(*tosrunNextEventExternal)(uint32_t); //typedef for tos function runNextEventExternal(uint32_t b) 
typedef int(*tossensorStartDone)(uint8_t); //typedef for tos function sensorStartDone(uint8_t b) 
typedef int(*tossensorStopDone)(uint8_t); //typedef for tos function sensorStopDone(uint8_t b) 
typedef int(*tosinterruptData)(uint8_t,uint16_t,void *); //typedef for tos function interruptData(uint8_t b , uint16_t c , void * d) 
typedef void(*tosApplicationStartDone)(uint8_t); //typedef for tos function ApplicationStartDone(uint8_t b) 
typedef void(*tosAplicationStopDone)(uint8_t); //typedef for tos function AplicationStopDone(uint8_t b) 




class Ns3ToTosProxy {
    public:
        Ns3ToTosProxy();
        void addFunction(std::string name, void * pointer);
		int sendDone(void * b , uint8_t c);
		void radioStartDone(int b);
		int setUniqueID(int b);
		void sim_main_start_mote(int b);
		int setProxy(long b);
		int tickFired(uint32_t b);
		int radioStateDone();
		int receiveMessage(void * b);
		int runNextEventExternal(uint32_t b);
		int sensorStartDone(uint8_t b);
		int sensorStopDone(uint8_t b);
		int interruptData(uint8_t b , uint16_t c , void * d);
		void ApplicationStartDone(uint8_t b);
		void AplicationStopDone(uint8_t b);

    ~Ns3ToTosProxy();
    void * getFunction(std::string name);
    std::map<std::string, void *> m_tos_functions;

};

#endif /* NS3TOTOSPROXYAUTO_H_ */
