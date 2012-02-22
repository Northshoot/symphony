/*
 * ns3includes.h
 *
 *  Created on: Dec 12, 2011
 *      Author: lauril
 */

#ifndef NS3INCLUDES_H_
#define NS3INCLUDES_H_

#ifdef __cplusplus
typedef uint8_t am_id_t;
typedef uint8_t am_group_t;
typedef uint16_t am_addr_t;
typedef uint8_t nx_uint8_t;
typedef uint16_t nx_uint16_t;

#define TOSH_DATA_LENGTH 28
#define TOS_BCAST_ADDR 0xFFFF

typedef struct ns3pack{
	uint8_t length;
	uint8_t dsn;
	uint8_t type;
	uint16_t fdest;
	uint8_t destpan;
	uint16_t dest;
	uint16_t src;
	uint8_t padd;
} ns3pack;

typedef struct ns3_metadata_t
{
	uint8_t lqi;
	union
	{
		uint8_t power;
		uint8_t rssi;
	};
} ns3_metadata_t;



typedef struct ns3packet_header_t
{
	uint8_t length;
	uint8_t dsn;
	am_id_t type;
	uint16_t fdest;
	am_group_t destpan;
	am_addr_t dest;
	am_addr_t src;
	uint8_t padd;

} ns3packet_header_t;

typedef struct timestamp_metadata_t
{
	uint32_t timestamp;
} timestamp_metadata_t;

typedef struct ns3packet_footer_t
{
	// the time stamp is not recorded here, time stamped messaged cannot have max length
} ns3packet_footer_t;

typedef struct flags_metadata_t
{
	// TODO: make sure that we have no more than 8 flags
	uint8_t flags;
} flags_metadata_t;


typedef struct ns3packet_metadata_t
{
	timestamp_metadata_t timestamp;
	flags_metadata_t flags;
	ns3_metadata_t ns3;
} ns3packet_metadata_t;


typedef struct message_t {
  uint8_t header[sizeof(ns3packet_header_t)];
  uint8_t data[TOSH_DATA_LENGTH];
  uint8_t footer[sizeof(ns3packet_footer_t)];
  uint8_t metadata[sizeof(ns3_metadata_t)];
} message_t;

#endif





#endif /* NS3INCLUDES_H_ */
