
/*
 * ns3-to-tos-proxy.h
 *
 *  Created on: Mars 20, 2011
 *      Author: laurynas
 *     Autogenerated on: 2012-06-13
 */
 

#ifndef NS3TOTOSPROXYAUTO_H_
#define NS3TOTOSPROXYAUTO_H_
#include <stdint.h>

#include <string>
#include <google/dense_hash_map>
typedef int(*tossendSendDone)(int); //typedef for tos function sendSendDone(int b) 
typedef void(*tosradioStartDone)(int); //typedef for tos function radioStartDone(int b) 
typedef int(*tossetUniqueID)(int); //typedef for tos function setUniqueID(int b) 
typedef void(*tossim_main_start_mote)(int); //typedef for tos function sim_main_start_mote(int b) 
typedef int(*tossetProxy)(long); //typedef for tos function setProxy(long b) 
typedef int(*tostickFired)(uint32_t); //typedef for tos function tickFired(uint32_t b) 
typedef int(*tosradioStateDone)(); //typedef for tos function radioStateDone() 
typedef int(*tosreceiveMessage)(void *); //typedef for tos function receiveMessage(void * b) 
typedef int(*tosrunNextEventExternal)(uint32_t); //typedef for tos function runNextEventExternal(uint32_t b) 



using google::dense_hash_map;

class Ns3ToTosProxy {
    public:
        Ns3ToTosProxy();
        void addFunction(std::string name, void * pointer);
		int sendSendDone(int b);
		void radioStartDone(int b);
		int setUniqueID(int b);
		void sim_main_start_mote(int b);
		int setProxy(long b);
		int tickFired(uint32_t b);
		int radioStateDone();
		int receiveMessage(void * b);
		int runNextEventExternal(uint32_t b);

    ~Ns3ToTosProxy();
    void * getFunction(std::string name);
private:
    dense_hash_map<std::string, void *> m_tos_functions;

};

#endif /* NS3TOTOSPROXYAUTO_H_ */
