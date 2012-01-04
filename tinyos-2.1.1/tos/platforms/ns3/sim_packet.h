/*
 * Copyright (c) 2005 Stanford University. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 * - Neither the name of the copyright holder nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *
 * TOSSIM packet abstract data type, so C++ code can call into nesC
 * code that does the native-to-network type translation.
 *
 * @author Philip Levis
 * @date   Jan 2 2006
 */

// $Id: sim_packet.h,v 1.6 2010-06-29 22:07:51 scipio Exp $

#ifndef SIM_PACKET_H_INCLUDED
#define SIM_PACKET_H_INCLUDED
#include <message.h>


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




#endif // SIM_PACKET_H_INCLUDED
