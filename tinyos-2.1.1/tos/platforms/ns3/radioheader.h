
#ifndef __NS3RADIO_H__
#define __NS3RADIO_H__
#include "AM.h"

typedef struct ns3_metadata_t
{
	uint8_t lqi;
	union
	{
		uint8_t power;
		uint8_t rssi;
	};
} ns3_metadata_t;



typedef nx_struct ns3packet_header_t
{
	nxle_uint8_t length;
	nxle_uint8_t dsn;
	nx_am_id_t type;
	nxle_uint16_t fdest;
	am_group_t destpan;
	am_addr_t dest;
	am_addr_t src;
	nxle_uint8_t padd;

} ns3packet_header_t;

typedef struct timestamp_metadata_t
{
	uint32_t timestamp;
} timestamp_metadata_t;

typedef nx_struct ns3packet_footer_t
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

#endif//__NS3RADIO_H__

