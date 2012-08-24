/*
 * message.h
 *
 *  Created on: Dec 8, 2011
 *      Author: lauril
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

//OBS! need better way to handle dual headers!
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
	uint8_t type;
	uint16_t fdest;
	uint16_t destpan;
	uint16_t dest;
	uint16_t src;
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


typedef union message_header {
	ns3packet_header_t rf230;
	//serial_header_t serial;
} message_header_t;

typedef union message_footer {
	ns3packet_footer_t rf230;
} message_footer_t;

typedef union message_metadata {
	ns3packet_metadata_t rf230;
} message_metadata_t;


typedef struct message_t {
  uint8_t header[sizeof(message_header_t)];
  uint8_t data[28];
  uint8_t footer[sizeof(message_footer_t)];
  uint8_t metadata[sizeof(message_metadata_t)];
} message_t;

#endif /* MESSAGE_H_ */
