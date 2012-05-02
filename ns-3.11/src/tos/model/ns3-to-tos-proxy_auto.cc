
/*
 * ns3-to-tos-proxy.cc
 *
 *  Created on: Mars 20, 2011
 *      Author: laurynas
 *     Autogenerated on: 2012-05-02
 */
 
#include <iostream>
#include "ns3-to-tos-proxy_auto.h"


Ns3ToTosProxy::Ns3ToTosProxy() {
    m_tos_functions.set_empty_key("empty");
}            

void
Ns3ToTosProxy::addFunction(std::string name, void * pointer){
    m_tos_functions[name]=pointer;

}
          
            
int
Ns3ToTosProxy::sendSendDone(int b)
{
 	return ((tossendSendDone)m_tos_functions["sendSendDone"])(b);
}
void
Ns3ToTosProxy::radioStartDone(int b)
{
 	((tosradioStartDone)m_tos_functions["radioStartDone"])(b);
}
int
Ns3ToTosProxy::setUniqueID(int b)
{
 	return ((tossetUniqueID)m_tos_functions["setUniqueID"])(b);
}
void
Ns3ToTosProxy::sim_main_start_mote(int b)
{
 	((tossim_main_start_mote)m_tos_functions["sim_main_start_mote"])(b);
}
int
Ns3ToTosProxy::setProxy(long b)
{
 	return ((tossetProxy)m_tos_functions["setProxy"])(b);
}
int
Ns3ToTosProxy::tickFired(uint32_t b)
{
 	return ((tostickFired)m_tos_functions["tickFired"])(b);
}
int
Ns3ToTosProxy::radioStateDone()
{
 	return ((tosradioStateDone)m_tos_functions["radioStateDone"])();
}
int
Ns3ToTosProxy::receiveMessage(void * b)
{
 	return ((tosreceiveMessage)m_tos_functions["receiveMessage"])(b);
}
int
Ns3ToTosProxy::runNextEventExternal(uint32_t b)
{
 	return ((tosrunNextEventExternal)m_tos_functions["runNextEventExternal"])(b);
}

Ns3ToTosProxy::~Ns3ToTosProxy() { }
