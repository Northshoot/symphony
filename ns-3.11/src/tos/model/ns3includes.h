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
	uint8_t type;
	uint16_t fdest;
	uint8_t destpan;
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


typedef struct message_t {
  uint8_t header[sizeof(ns3packet_header_t)];
  uint8_t data[TOSH_DATA_LENGTH];
  uint8_t footer[sizeof(ns3packet_footer_t)];
  uint8_t metadata[sizeof(ns3_metadata_t)];
} message_t;

//XXX: redefined from TinyError.h
//simply to reduce the complexity of build system


typedef enum {
  SUCCESS        =  0,
  FAIL           =  1,           // Generic condition: backwards compatible
  ESIZE          =  2,           // Parameter passed in was too big.
  ECANCEL        =  3,           // Operation cancelled by a call.
  EOFF           =  4,           // Subsystem is not active
  EBUSY          =  5,           // The underlying system is busy; retry later
  EINVAL         =  6,           // An invalid parameter was passed
  ERETRY         =  7,           // A rare and transient failure: can retry
  ERESERVE       =  8,           // Reservation required before usage
  EALREADY       =  9,           // The device state you are requesting is already set
  ENOMEM         = 10,           // Memory required not available
  ENOACK         = 11,           // A packet was not acknowledged
  ELAST          = 11            // Last enum value
}error_t;


//TODO: with multiple includes brakes function...

//error_t errCombine(error_t r1, error_t r2)
///* Returns: r1 if r1 == r2, FAIL otherwise. This is the standard error
//     combination function: two successes, or two identical errors are
//     preserved, while conflicting errors are represented by FAIL.
//*/
//{
//  return r1 == r2 ? r1 : FAIL;
//}


#endif /* NS3INCLUDES_H_ */
