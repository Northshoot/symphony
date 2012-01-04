/*
 * tos-packet.h
 *
 *  Created on: Jan 3, 2012
 *      Author: lauril
 */

#ifndef TOS_PACKET_H_
#define TOS_PACKET_H_
//TODO: refactor with ns3 stuff
#include <stdlib.h>
#include <stdint.h>
#include "ns3includes.h"

class TosPacket {
 public:
    TosPacket();
    TosPacket(message_t* msg);
    ~TosPacket();

    void setSource(int src);
    int source();

    void setDestination(int dest);
    am_addr_t getDestination();

    void setLength(int len);
    int length();

    void setType(int type);
    int type();

    char* data();
    void setData(char* data, int len);
    int maxLength();
    
    void setStrength(int str);

    message_t* getPacket();

    void deliver(int node, long long int t);
    void deliverNow(int node);
    
 private:
    ns3packet_header_t* getHeader(message_t* msg);
    int allocated;
    message_t* msgPtr;
};

#endif /* TOS_PACKET_H_ */
