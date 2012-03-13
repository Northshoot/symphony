/*
 * wsn-tos-device.cc
 *
 *  Created on: Feb 13, 2012
 *      Author: lauril
 */
#include <memory>
#include "ns3/log.h"
#include "ns3/assert.h"
#include "ns3/wifi-mac.h"
#include "ns3/wifi-phy.h"
#include "ns3/wifi-channel.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include "ns3/pointer.h"
#include "ns3/ptr.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/wifi-mac-header.h"
#include "ns3/net-device.h"
#include "ns3/wifi-mac-header.h"
#include "calls-to-ns3.h"
#include "ns3includes.h"
#include "tos-net-device.h"
#include "tos-node.h"
#include "tos-mac-low.h"
#include "tos-mac-low.h"
#include "ns3-to-tos-proxy.h"
#include <stdio.h>

void
printTosPacket( char *buf){
	int size = sizeof(message_t);
	int hsize = sizeof(ns3packet_header_t);
	int i=0;
	ns3packet_header_t *hdr;
	hdr =(ns3packet_header_t*)(((message_t*)buf)->header);
	printf("FROM NS3 - SIZE: %d :: HEADER size: %d\n", size, hsize);
	printf("HEX: ");
	for (;i<size-1;i++){
		printf("%02X ", (uint8_t)buf[i]);
	}
	printf("%02X\n",(uint8_t)buf[i]);
	printf("header: ");
	printf("len %d :: dsn %d :: type %d :: fdest %d :: destpan %d\n",hdr->length,hdr->dsn,hdr->type,hdr->fdest,hdr->destpan);
	printf("dest %d :: src %d :: padd %d\n", hdr->dest,hdr->src,hdr->padd);
}

NS_LOG_COMPONENT_DEFINE("TosNetDevice");
using namespace std;
namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (TosNetDevice);


TosNetDevice::TosNetDevice() :
		m_configComplete(false) {
	NS_LOG_FUNCTION_NOARGS ();
}

TypeId TosNetDevice::GetTypeId(void) {
	  static TypeId tid = TypeId ("ns3::TosNetDevice")
	    .SetParent<NetDevice> ()
	    .AddConstructor<TosNetDevice> ()
	    .AddAttribute ("Mtu", "The MAC-level Maximum Transmission Unit",
	                   UintegerValue (MAX_MSDU_SIZE - 8),
	                   MakeUintegerAccessor (&TosNetDevice::SetMtu,
	                                         &TosNetDevice::GetMtu),
	                   MakeUintegerChecker<uint16_t> (1,MAX_MSDU_SIZE - 8))
	    .AddAttribute ("Channel", "The channel attached to this device",
	                   PointerValue (),
	                   MakePointerAccessor (&TosNetDevice::DoGetChannel),
	                   MakePointerChecker<TosNetDevice> ())
	    .AddAttribute ("Phy", "The PHY layer attached to this device.",
	                   PointerValue (),
	                   MakePointerAccessor (&TosNetDevice::GetPhy,
	                                        &TosNetDevice::SetPhy),
	                   MakePointerChecker<WifiPhy> ())
	    .AddAttribute ("Mac", "The MAC layer attached to this device.",
	                   PointerValue (),
	                   MakePointerAccessor (&TosNetDevice::GetMac,
	                                        &TosNetDevice::SetMac),
	                   MakePointerChecker<WifiMac> ())
	  ;
	  return tid;
}

TosNetDevice::~TosNetDevice() {
	NS_LOG_FUNCTION_NOARGS ();
}

void TosNetDevice::SetMac(Ptr<TosMacLow> mac) {
	m_tos_mac = mac;
	CompleteConfig();
}

void TosNetDevice::SetPhy(Ptr<WifiPhy> phy) {
	m_phy = phy;
}

Ptr<TosMacLow> TosNetDevice::GetMac(void) const {
	return m_tos_mac;
}

Ptr<WifiPhy> TosNetDevice::GetPhy(void) const {
	return m_phy;
}

Ptr<Channel> TosNetDevice::GetChannel(void) const {
	return m_phy->GetChannel();
}

void TosNetDevice::SetMac48Address(Mac48Address address) {
	m_tos_mac->SetAddress(address);
}

Mac48Address TosNetDevice::GetMac48Address(void) const {
	return m_tos_mac->GetAddress();
}

Ptr<Node> TosNetDevice::GetNode(void) const {
   NS_LOG_FUNCTION(m_node << typeid(m_node).name());
	return m_node;
}

void TosNetDevice::SetNode(Ptr<Node> node) {
	m_node = node;
}

error_t
TosNetDevice::DeviceTurnOff() {
	m_state = RADIO_STATE_OFF;
	return SUCCESS;
}

error_t TosNetDevice::DeviceStandby() {
	return EBUSY;
}

error_t TosNetDevice::DeviceTurnOn() {
	return EBUSY;
}

error_t TosNetDevice::DeviceSetChannel(uint8_t channel) {
	return EBUSY;
}

void TosNetDevice::done() {
}

uint8_t TosNetDevice::DeviceGetChannel() {
	uint16_t channel = m_phy->GetChannelNumber();
	NS_ASSERT(channel<=14);
	return static_cast<uint8_t>(channel);
}

error_t TosNetDevice::DeviceSend(ns3pack* hder, void* msg) {
	NS_ASSERT(!m_busy);
	memcpy((void *)&m_tx_msg, (void *)msg, sizeof(message_t));
	memcpy((void *)&m_tx_hdr, (void *)hder, sizeof(ns3pack));
	//TODO: logic for device needs to be added
	//TODO: implement callbacks to tos
	//TODO: implement time delay;
	//make ns 3 packet from the tos packet
	Ptr<Packet> pkt = TosToNsPacket((message_t*)msg);
	printTosPacket((char*)msg);
	WifiMacHeader hdr;
	hdr.SetTypeData();
	hdr.SetAddr1(Mac48Address::GetBroadcast());
	hdr.SetAddr2 (m_tos_mac->GetAddress ());
	// hdr.SetAddr3 (GetBssid ());
	hdr.SetDsNotFrom();
	hdr.SetDsNotTo();

//	pkt->AddHeader(hdr);
//	message_t * msg1  = (message_t*) malloc(sizeof(message_t));
//	pkt->RemoveHeader(hdr);
//	pkt->CopyData(reinterpret_cast< uint8_t*>(msg1), sizeof(message_t));
//	printTosPacket((char*)msg1,sizeof(message_t));
	DeviceGetChannel();
	//m_tos_mac->TransmitData(pkt->Copy(), &hdr);
	return SUCCESS;
}

Ptr<Packet>
TosNetDevice::TosToNsPacket(message_t* msg) {
	Ptr <Packet> pkt =Create <Packet> (Packet(reinterpret_cast<uint8_t*>(msg),
							sizeof(message_t)));
	return pkt;
}

message_t* TosNetDevice::NsToTosPacket(Ptr<Packet> packet, const WifiMacHeader* hdr) {
	WifiMacHeader hdrr;
	message_t * msg  = (message_t*) malloc(sizeof(message_t));
	packet->RemoveHeader(hdrr);
	packet->CopyData(reinterpret_cast< uint8_t*>(msg), sizeof(message_t));
//	NS_LOG_FUNCTION_NOARGS();
//	printTosPacket((char *) msg, 28);
	memcpy((void *)&m_rx_msg, (void *)msg, sizeof(message_t));
	return &m_rx_msg;
}

void TosNetDevice::DeviceSendDone(message_t* msg, uint8_t error) {
}

void TosNetDevice::DeviceCancel(message_t* msg) {
}

bool TosNetDevice::DeviceRXHeader(message_t* msg) {
	return true;
}

message_t* TosNetDevice::DeviceReceive(message_t* msg) {
	return &m_rx_msg;
}

void TosNetDevice::DoDispose(void) {
	NS_LOG_FUNCTION_NOARGS ();
	m_node=0;
	m_tos_mac->Dispose();
	m_phy->Dispose();
	m_tos_mac=0;
	m_phy=0;
	NetDevice::DoDispose ();
}

void TosNetDevice::DoStart(void) {
	NS_LOG_FUNCTION_NOARGS ();
	m_tos_mac->Start();
	m_phy->Start();
	NetDevice::DoStart();
}

message_t
TosNetDevice::GetCurrentMsg(){
	return m_tx_msg;
}

void
TosNetDevice::ForwardUp(Ptr<Packet> packet, const WifiMacHeader* hdr) {
	message_t * msg = NsToTosPacket(packet, hdr);
	m_ns3totos->rxMsg((void*) msg);
}

void TosNetDevice::Setup(void) {
}

Ptr<WifiChannel>
TosNetDevice::DoGetChannel(void) const {
	return m_phy->GetChannel();
}

bool
TosNetDevice::Send(Ptr<Packet> packet, const Address& dest) {
	NS_LOG_FUNCTION(this << "NOT implemented");
	return false;
}

void
TosNetDevice::SetIfIndex(const uint32_t index) {
	NS_LOG_FUNCTION(this << "NOT in use");
	m_ifIndex = index;
}

uint32_t
TosNetDevice::GetIfIndex(void) const {
	NS_LOG_FUNCTION(this << "NOT in use");
	return m_ifIndex;
}

void
TosNetDevice::SetAddress(Address address) {
	m_tos_mac->SetAddress (Mac48Address::ConvertFrom (address));

}

Address
TosNetDevice::GetAddress(void) const {
	return m_tos_mac->GetAddress();
}

bool
TosNetDevice::SetMtu(const uint16_t mtu) {
	if(mtu <= MAX_MSDU_SIZE){
		m_mtu = mtu;
		return true;
	}
	return false;
}

uint16_t
TosNetDevice::GetMtu(void) const {
	return m_mtu;
}

bool
TosNetDevice::IsLinkUp(void) const {
	NS_LOG_FUNCTION(this << "NOT implemented");
	return false;
}

void
TosNetDevice::AddLinkChangeCallback(Callback<void> callback) {
	NS_LOG_FUNCTION(this << "NOT implemented");
}

bool
TosNetDevice::IsBroadcast(void) const {
	NS_LOG_FUNCTION(this << "NOT implemented");
	return false;
}

Address
TosNetDevice::GetBroadcast(void) const {
	return Mac48Address::GetBroadcast ();
}

bool
TosNetDevice::IsMulticast(void) const {
	NS_LOG_FUNCTION(this << "NOT implemented");
	return false;
}

Address
TosNetDevice::GetMulticast(Ipv4Address multicastGroup) const {
	return Mac48Address::GetMulticast (multicastGroup);
}

bool
TosNetDevice::IsPointToPoint(void) const {
	NS_LOG_FUNCTION(this << "NOT implemented");
	return false;
}

bool
TosNetDevice::IsBridge(void) const {
	NS_LOG_FUNCTION(this << "NOT implemented");
	return false;
}

bool
TosNetDevice::Send(Ptr<Packet> packet, const Address& dest,
		uint16_t protocolNumber) {
	NS_LOG_FUNCTION(this << "NOT implemented");
	return false;
}

bool
TosNetDevice::NeedsArp(void) const {
	NS_LOG_FUNCTION(this << "NOT implemented");
	return true;
}

void
TosNetDevice::SetReceiveCallback(NetDevice::ReceiveCallback cb) {
	NS_LOG_FUNCTION(this << "NOT implemented");
}

void
TosNetDevice::LinkUp(void) {
	NS_LOG_FUNCTION(this << "NOT implemented");
}

void
TosNetDevice::LinkDown(void) {
	NS_LOG_FUNCTION(this << "NOT implemented");
}
Address
TosNetDevice::GetMulticast (Ipv6Address addr) const{
	return Mac48Address::GetMulticast (addr);
}
bool
TosNetDevice::SendFrom(Ptr<Packet> packet, const Address& source,
		const Address& dest, uint16_t protocolNumber) {
	NS_LOG_FUNCTION(this << "NOT implemented");
	return false;
}

void
TosNetDevice::SetPromiscReceiveCallback(PromiscReceiveCallback cb) {
	NS_LOG_FUNCTION(this << "NOT implemented");
}

bool
TosNetDevice::SupportsSendFrom(void) const {
	NS_LOG_FUNCTION(this << "NOT implemented");
	return false;
}

void TosNetDevice::CompleteConfig(void) {
	if (m_tos_mac == 0 || m_phy == 0 || m_node == 0)
	{ return; }
	  m_tos_mac->SetPhy(m_phy);
	  m_tos_mac->SetRxCallback (MakeCallback (&TosNetDevice::ForwardUp, this));
//	  m_tos_mac->ReceiveError (MakeCallback (&TosWifiNetDevice::LinkUp, this));
//	  m_tos_mac->ReceiveOk (MakeCallback (&TosWifiNetDevice::LinkDown, this));

	  m_configComplete = true;
	  m_busy = false;
}

void
TosNetDevice::setNs3ToTos(Ns3ToTosProxy * nstos){
	m_ns3totos=nstos;
}

//void
//TosNetDevice::SetTosNodeContainer(TosNodeContainer c){
//	m_node_container = c;
//}


} /* namespace ns3 */
