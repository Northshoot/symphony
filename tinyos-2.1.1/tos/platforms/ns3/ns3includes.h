/*
 * ns3includes.h
 *
 *  Created on: Dec 12, 2011
 *      Author: lauril
 */

#ifndef NS3INCLUDES_H_
#define NS3INCLUDES_H_

typedef uint8_t am_id_t;
typedef uint8_t am_group_t;
typedef uint16_t am_addr_t;

#ifndef TOSH_DATA_LENGTH
#define TOSH_DATA_LENGTH 28
#endif

#ifndef TOS_BCAST_ADDR
#define TOS_BCAST_ADDR 0xFFFF
#endif

#include "radio/radioheader.h"

typedef struct message_t {
  uint8_t header[sizeof(ns3packet_header_t)];
  uint8_t data[TOSH_DATA_LENGTH];
  uint8_t footer[sizeof(ns3packet_footer_t)];
  uint8_t metadata[sizeof(ns3_metadata_t)];
} message_t;

typedef struct {
	int x;
	int y;
} Foo;



#endif /* NS3INCLUDES_H_ */
