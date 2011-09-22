
//#include <RadioConfig.h>

configuration ActiveMessageC
{
	provides
	{
		interface SplitControl;

		interface AMSend[uint8_t id];
		interface Receive[uint8_t id];
		//interface Receive as Snoop[uint8_t id];
		//interface SendNotifier[am_id_t id];

		interface Packet;
		interface AMPacket;

//		interface PacketAcknowledgements;
//		interface LowPowerListening;
#ifdef PACKET_LINK
#error packet link is not supporter
		//interface PacketLink;
#endif

//		interface PacketTimeStamp<TMicro, uint32_t> as PacketTimeStampMicro;
//		interface PacketTimeStamp<TMilli, uint32_t> as PacketTimeStampMilli;
	}
}

implementation
{
	components Ns3ActiveMessageC as MessageC;
	components NS3MsgGatewayP as Gate;
	components ActiveMessageAddressC;
	
	Gate.ActiveMessageAddress -> ActiveMessageAddressC;

	MessageC.SubSend -> Gate.Send;
	MessageC.SubReceive -> Gate.Receive;
	MessageC.SubState -> Gate.State;

	SplitControl = MessageC.SplitControl;

	AMSend = MessageC;
	Receive = MessageC.Receive;
	Snoop = MessageC.Snoop;
	SendNotifier = MessageC;

	Packet = MessageC;
	AMPacket = MessageC;

//	PacketAcknowledgements = MessageC;
//	LowPowerListening = MessageC;
#ifdef PACKET_LINK
//	PacketLink = MessageC;
#endif

//	PacketTimeStampMilli = MessageC;
//	PacketTimeStampMicro = MessageC;
}
