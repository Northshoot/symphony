/*
 * tos-packet.cc
 *
 *  Created on: Jan 3, 2012
 *      Author: lauril
 */

#include <cstddef>
#include <stdio.h>
#include <stdint.h>
#include "tos-packet.h"
#include "ns3includes.h"


TosPacket::TosPacket() {
  msgPtr =(message_t*)malloc(sizeof(message_t));
  allocated = 1;
}

TosPacket::TosPacket(message_t* m) {
  if (m != NULL) {
    msgPtr = m;
    allocated = 0;
  }
  else {
    msgPtr = (message_t*)malloc(sizeof(message_t));
    allocated = 1;
  }
}

TosPacket::~TosPacket() {
  if (allocated) {
    free(msgPtr);
  }
}

ns3packet_header_t* TosPacket::getHeader(message_t* msg) {
  return (ns3packet_header_t*)(msg->header);
}

void TosPacket::setSource(int src) {
  //sim_packet_set_source(msgPtr, (uint16_t)src);
}
int TosPacket::source() {
 return 0;//sim_packet_source(msgPtr);
}

void TosPacket::setDestination(int dest) {
//  sim_packet_set_destination(msgPtr, (uint16_t)dest);
}
am_addr_t TosPacket::getDestination() {
//	uint16_t dst = sim_packet_destination((sim_packet_t*)msgPtr);
//	printf("TosPacket::destination(): %u\n",  dst);
	return 0;

}

void TosPacket::setLength(int len) {
  //sim_packet_set_length(msgPtr, (uint8_t)len);
}
int TosPacket::length() {
  return 0;//sim_packet_length(msgPtr);
}

void TosPacket::setType(int type) {
  //sim_packet_set_type(msgPtr, (uint8_t)type);
}
int TosPacket::type() {
  return 0;//sim_packet_type(msgPtr);
}

char* TosPacket::data() {
  //char* val =  (char*)sim_packet_data(msgPtr);
  return 0;//;
}

void TosPacket::setData(char* data, int len) {
//  len = (len > maxLength())? maxLength():len;
//  memcpy(sim_packet_data(msgPtr), data, len);
//  setLength(len);
}

int TosPacket::maxLength() {
  return 0;//(int)sim_packet_max_length(msgPtr);
}

void TosPacket::setStrength(int str) {
  //sim_packet_set_strength(msgPtr, (uint16_t)str);
}


message_t* TosPacket::getPacket() {
  return  msgPtr;
}

void TosPacket::deliver(int node, long long int t) {
  //sim_packet_deliver(node, msgPtr, t);
}

void TosPacket::deliverNow(int node) {
  //deliver(node, 0);
}

