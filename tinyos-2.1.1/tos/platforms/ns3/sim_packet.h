

#ifndef SIM_NS3_PACKET_H_INCLUDED
#define SIM_NS3_PACKET_H_INCLUDED
#include <message.h>
#include <stdio.h>

void
printPacket( char *buf , int size){
	int i;
	printf("SIZE: %d\n", size);
	for (i=0;i<size-1;i++){
		printf("%02X ", (char)buf[i]);
	}
	printf("%02X\n",buf[i]);
}

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

ns3pack convertToNS3(message_t * msg){
	ns3pack nsh;
	ns3packet_header_t* hdr = ((ns3packet_header_t*) msg->header);
	nsh.length = hdr->length;
	nsh.dsn = hdr->dsn;
	nsh.type = hdr->type;
	nsh.fdest = hdr->fdest;
	nsh.destpan = hdr->destpan;
	nsh.dest = hdr->dest;
	nsh.src = hdr->src;
	nsh.padd = hdr->padd;
	return nsh;
}




#endif // SIM_NS3_PACKET_H_INCLUDED
