/*
 * tos-packet.h
 *
 *  Created on: Jan 3, 2012
 *      Author: lauril
 */

#ifndef TOS_PACKET_CONVERTER_H_
#define TOS_PACKET_CONVERTER_H_
#include "ns3includes.h"


ns3packet_header_t *
getTosHeader(void * buf){
	return (ns3packet_header_t*)(((message_t*)buf)->header);
}
uint8_t *
getTosPayload(void * buf){
	return (uint8_t *)(((message_t*)buf)->data);
}

ns3packet_footer_t *
getTosFooter(void * buf){
	return (ns3packet_footer_t *)(((message_t*)buf)->footer);
}

ns3packet_metadata_t *
getTosMetadata(void * buf){
	return (ns3packet_metadata_t *)(((message_t*)buf)->metadata);
}

/**
 * Get header primitive
 */

uint8_t
get_enght(void *buf){
	 return getTosHeader(buf)->length;
 }
uint8_t
get_dsn(void * buf){
	return getTosHeader(buf)->dsn;
}
uint8_t
get_type(void * buf){
	return getTosHeader(buf)->type;
}
uint16_t
get_fdest(void * buf){
	return getTosHeader(buf)->fdest;
}
uint8_t
get_destpan(void * buf){
	return getTosHeader(buf)->destpan;
}
uint16_t
get_dest(void * buf){
	return getTosHeader(buf)->dest;
}
uint16_t
get_src(void * buf){
	return getTosHeader(buf)->src;
}
uint8_t
get_padd(void * buf){
	return getTosHeader(buf)->padd;
}

#endif /* TOS_PACKET_CONVERTER_H_ */
