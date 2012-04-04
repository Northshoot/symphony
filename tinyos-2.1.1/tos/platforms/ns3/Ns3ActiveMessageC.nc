/**
 * Simplified version of ACtive message used for testing purpose of TInyOS ns3 coupling
 */
 
#include "radioheader.h"
#include "defines.h"



module Ns3ActiveMessageC
{
	provides
	{
		interface SplitControl;

		interface AMSend[am_id_t id];
		interface Receive[am_id_t id];
		interface Receive as Snoop[am_id_t id];
		interface SendNotifier[am_id_t id];

		interface Packet;
		interface AMPacket;

		interface PacketAcknowledgements;
//		interface LowPowerListening;
#ifdef PACKET_LINK
//		interface PacketLink;
#endif
//
//		interface RadioChannel;

//		interface PacketField<uint8_t> as PacketLinkQuality;
//		interface PacketField<uint8_t> as PacketTransmitPower;
//		interface PacketField<uint8_t> as PacketRSSI;

//		interface LocalTime<TRadio> as LocalTimeRadio;
//		interface PacketTimeStamp<TRadio, uint32_t> as PacketTimeStampRadio;
//		interface PacketTimeStamp<TMilli, uint32_t> as PacketTimeStampMilli;


	}
	uses{
		interface ActiveMessageAddress;
		interface BareSend as SubSend;
		interface BareReceive as SubReceive;
		interface RadioState as SubState;
	}


}

implementation
{
	void task SplitControlStartDone(){
		signal SplitControl.startDone(SUCCESS);
	}
	
	extern int radioStateDone() @C() @spontaneous(){
        printf("\t radio state done\n");        
		signal SplitControl.startDone(SUCCESS);
		return 0;
		
	}	
	command error_t SplitControl.start(){
		post SplitControlStartDone();
		return 0;
	}

	command error_t SplitControl.stop(){
		return SUCCESS;
	}
	
	default event void SplitControl.startDone(error_t err) {}
	
	
	//***** Active message config stuff *** /
	
	ns3packet_header_t* getHeader(message_t* msg){
		return ((ns3packet_header_t*) msg->header);
	}

	void* getPayload(message_t* msg){
		return (void*)msg->data;
	}
	
	ns3packet_metadata_t* getMeta(message_t* msg){
		return ((ns3packet_metadata_t*) msg->metadata);
	}

	am_addr_t destination(message_t* msg){
	  return getHeader(msg)->dest;
	}

    void setDestination(message_t* msg, am_addr_t addr){
      getHeader(msg)->dest = addr;
	}

	am_addr_t source(message_t* msg){
	  return getHeader(msg)->src;
	}

	void setSource(message_t* msg, am_addr_t addr){
	  getHeader(msg)->src = addr;
	}

	am_group_t group(message_t* msg){
	  return getHeader(msg)->destpan;
	}

	void setGroup(message_t* msg, am_group_t grp){
	  getHeader(msg)->destpan = grp;
	}
	
	/*----------------- Send -----------------*/

	command error_t AMSend.send[am_id_t id](am_addr_t addr, message_t* msg, uint8_t len)
	{
		if( len > call Packet.maxPayloadLength() )
			return EINVAL;

		call Packet.setPayloadLength(msg, len);
		call AMPacket.setSource(msg, call AMPacket.address());
		call AMPacket.setGroup(msg, call AMPacket.localGroup());
		call AMPacket.setType(msg, id);
		call AMPacket.setDestination(msg, addr);
		signal SendNotifier.aboutToSend[id](addr, msg);
		return call SubSend.send(msg);
	}

	event void SubSend.sendDone(message_t* msg, error_t error)
	{
		signal AMSend.sendDone[call AMPacket.type(msg)](msg, error);
	}

	command error_t AMSend.cancel[am_id_t id](message_t* msg)
	{
		return call SubSend.cancel(msg);
	}

	default event void AMSend.sendDone[am_id_t id](message_t* msg, error_t error)
	{
	}

	inline command uint8_t AMSend.maxPayloadLength[am_id_t id]()
	{
		return call Packet.maxPayloadLength();
	}

	inline command void* AMSend.getPayload[am_id_t id](message_t* msg, uint8_t len)
	{
		return call Packet.getPayload(msg, len);
	}

	default event void SendNotifier.aboutToSend[am_id_t id](am_addr_t addr, message_t* msg)
	{
	}

	tasklet_async event void SubState.done(){
		
	}
/*----------------- Receive -----------------*/

	event message_t* SubReceive.receive(message_t* msg)
	{
		am_id_t id = call AMPacket.type(msg);
		void* payload = getPayload(msg);
		uint8_t len = call Packet.payloadLength(msg);
		signal Receive.receive[id](msg, payload, len);
//		call AMPacket.isForMe(msg) 
//			? signal Receive.receive[id](msg, payload, len)
//			: signal Snoop.receive[id](msg, payload, len);
		
		return msg;
	}

	default event message_t* Receive.receive[am_id_t id](message_t* msg, void* payload, uint8_t len)
	{
		return msg;
	}

	default event message_t* Snoop.receive[am_id_t id](message_t* msg, void* payload, uint8_t len)
	{
		return msg;
	}

/*----------------- AMPacket -----------------*/

	inline command am_addr_t AMPacket.address()
	{
		return call ActiveMessageAddress.amAddress();
	}
 
	inline command am_group_t AMPacket.localGroup()
	{
		return call ActiveMessageAddress.amGroup();
	}

	inline command bool AMPacket.isForMe(message_t* msg)
	{
		am_addr_t addr = call AMPacket.destination(msg);
		return addr == call AMPacket.address() || addr == AM_BROADCAST_ADDR;
	}

	inline command am_addr_t AMPacket.destination(message_t* msg)
	{
		return destination(msg);
	}
 
	inline command void AMPacket.setDestination(message_t* msg, am_addr_t addr)
	{
		setDestination(msg, addr);
	}

	inline command am_addr_t AMPacket.source(message_t* msg)
	{
		return source(msg);
	}

	inline command void AMPacket.setSource(message_t* msg, am_addr_t addr)
	{
		setSource(msg, addr);
	}

	inline command am_id_t AMPacket.type(message_t* msg)
	{
		return getHeader(msg)->type;
	}

	inline command void AMPacket.setType(message_t* msg, am_id_t type)
	{
		getHeader(msg)->type = type;
	}
  
	inline command am_group_t AMPacket.group(message_t* msg) 
	{
		return group(msg);
	}

	inline command void AMPacket.setGroup(message_t* msg, am_group_t grp)
	{
		setGroup(msg, grp);
	}

	inline async event void ActiveMessageAddress.changed()
	{
	}



/*----------------- Packet -----------------*/

	command void Packet.clear(message_t* msg)
	{
		//TODO:clear flags
		getMeta(msg)->flags ;		
	}

	command uint8_t Packet.payloadLength(message_t* msg)
	{
		return sizeof(ns3packet_header_t);
	}

	command void Packet.setPayloadLength(message_t* msg, uint8_t len)
	{
		ASSERT( sizeof(ns3packet_header_t) + len + sizeof(ns3packet_metadata_t) <= sizeof(message_t) );
		getHeader(msg)->length = len;
	}

	command uint8_t Packet.maxPayloadLength()
	{
		return TOSH_DATA_LENGTH;
	}

	command void* Packet.getPayload(message_t* msg, uint8_t len)
	{
		ASSERT( len > call Packet.maxPayloadLength());

		return (void*)msg->data;
	}


	async command error_t PacketAcknowledgements.requestAck(message_t *msg){
		return 0;
	}

	async command error_t PacketAcknowledgements.noAck(message_t *msg){
		return 0;
	}

	async command bool PacketAcknowledgements.wasAcked(message_t *msg){
		return 0;
	}
}
