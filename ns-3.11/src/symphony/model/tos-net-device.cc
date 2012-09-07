/*
 * wsn-tos-device.cc
 *
 *  Created on: Feb 13, 2012
 *      Author: lauril
 */
#include <stdio.h>
#include <stddef.h>
#include <memory>
#include "boost/lexical_cast.hpp"
#include "ns3/nstime.h"
#include "ns3/simulator.h"
#include "ns3/event-id.h"
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
#include "tos-net-device.h"
#include "tos-node.h"
#include "tos-mac-low.h"
#include "tos-packet.h"
#include "calls-to-ns3.h"
#include "hardware-model.h"
#include "model-element.h"
#include "model-vocabulary.h"

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
	printf ("offsetof() is %lu\n",offsetof(ns3packet_header_t,fdest));

}

NS_LOG_COMPONENT_DEFINE("TosNetDevice");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (TosNetDevice);

class PhyTosListener : public ns3::WifiPhyListener
{
public:
  PhyTosListener (ns3::TosNetDevice *device)
    : m_device (device)
  {
  }
  virtual ~PhyTosListener ()
  {
    delete m_device;
  }
  virtual void NotifyRxStart (Time duration)
  {
    std::cout<<" \tNotifyRxStart "<< duration.GetMicroSeconds()<<std::endl;
  }
  virtual void NotifyRxEndOk (void)
  {
    std::cout<<" \tNotifyRxEndOk"<<std::endl;

  }
  virtual void NotifyRxEndError (void)
  {
    std::cout<<" \tNotifyRxEndError"<<std::endl;
  }
  virtual void NotifyTxStart (Time duration)
  {
    m_device->DeviceSendDone(0);
    std::cout<<" \tNotifyTxStart "<< duration.GetMicroSeconds()<< std::endl;
  }
  virtual void NotifyMaybeCcaBusyStart (Time duration)
  {

    std::cout<<" \tNotifyMaybeCcaBusyStart "<<duration.GetMicroSeconds()<<std::endl;
  }
  virtual void NotifySwitchingStart (Time duration)
  {
    std::cout<<" \tNotifySwitchingStart"<<duration.GetMicroSeconds()<<std::endl;
    //m_macLow->NotifySwitchingStartNow (duration);
  }
private:
  ns3::TosNetDevice *m_device;
};


TosNetDevice::TosNetDevice() :
		m_configComplete(false) {
	NS_LOG_FUNCTION_NOARGS ();
	m_state = RADIO_STATE_OFF;
}

TypeId
TosNetDevice::GetTypeId(void) {
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

void
TosNetDevice::SetMac(Ptr<TosMacLow> mac) {
	m_tos_mac = mac;
	CompleteConfig();
}

void
TosNetDevice::SetPhy(Ptr<WifiPhy> phy) {
	m_phy = phy;
}

Ptr<TosMacLow>
TosNetDevice::GetMac(void) const {
	return m_tos_mac;
}

Ptr<WifiPhy>
TosNetDevice::GetPhy(void) const {
	return m_phy;
}

Ptr<Channel>
TosNetDevice::GetChannel(void) const {
	return m_phy->GetChannel();
}

void
TosNetDevice::SetMac48Address(Mac48Address address) {
	m_tos_mac->SetAddress(address);
}

Mac48Address
TosNetDevice::GetMac48Address(void) const {
	return m_tos_mac->GetAddress();
}

Ptr<Node>
TosNetDevice::GetNode(void) const {
   NS_LOG_FUNCTION(m_node << typeid(m_node).name());
	return m_node;
}

void
TosNetDevice::SetNode(Ptr<Node> node) {
	m_node = node;
}

tos_error_t
TosNetDevice::DeviceTurnOff() {
  m_state = RADIO_STATE_OFF;
	return SUCCESS;
}

tos_error_t
TosNetDevice::DeviceStandby() {
	return EBUSY;
}

tos_error_t
TosNetDevice::DeviceTurnOn() {
  DoStart();
	return SUCCESS;
}

tos_error_t
TosNetDevice::DeviceSetChannel(uint8_t channel) {
	return EBUSY;
}

void
TosNetDevice::done() {
}

uint8_t
TosNetDevice::DeviceGetChannel() {
	uint16_t channel = m_phy->GetChannelNumber();
	NS_ASSERT(channel<=14);
	return static_cast<uint8_t>(channel);
}

tos_error_t
TosNetDevice::DeviceSend(void* msg) {
  std::cerr <<"TosNetDevice::DeviceSend(void* msg) "<<(!m_busy)<<std::endl;
  NS_ASSERT(m_state == RADIO_STATE_ON && !m_busy);
   if(m_state == RADIO_STATE_ON && !m_busy){

    memcpy((void *)&m_tx_msg, (void *)msg, sizeof(message_t));
    m_state = RADIO_STATE_TX;
    m_busy=true;
//    uint64_t t = boost::lexical_cast<uint64_t>(m_txParams->getElement(ModelVocabulary::CALL,"DeviceSend")->getAttributeValue("time"));
//    NS_LOG_FUNCTION(t);
//    Time run_time=MilliSeconds(20);
//    m_sendEvent = Simulator::Schedule(run_time, &TosNetDevice::TransmitData, this);
    TransmitData();
    return SUCCESS;
    } else {
      NS_LOG_FUNCTION("send busy");
      return EBUSY;
    }
	return FAIL;
}

void
TosNetDevice::TransmitData(void)
{
  NS_LOG_FUNCTION_NOARGS();
  printf("\t\t\t\tNS3 SENDING\n");
  //printTosPacket((char*)&m_tx_msg);
  m_tx_pkt = TosToNsPacket((message_t*)&m_tx_msg);
  WifiMacHeader hdr;
  hdr.SetTypeData();
  hdr.SetAddr1(Mac48Address::GetBroadcast());
  hdr.SetAddr2 (m_tos_mac->GetAddress ());
  // hdr.SetAddr3 (GetBssid ());
  hdr.SetDsNotFrom();
  hdr.SetDsNotTo();
  m_tx_pkt->AddHeader(hdr);
  m_tos_mac->TransmitData(m_tx_pkt->Copy(), &hdr);

}

void
TosNetDevice::radioStartDone()
{
  Simulator::Remove(m_startUpEvent);
  m_state = RADIO_STATE_ON;
  c_ns2tosStartDone(SUCCESS);
  NS_LOG_FUNCTION_NOARGS ();
}
void
TosNetDevice::DoStart(void)
{
  NS_LOG_FUNCTION_NOARGS ();
  m_tos_mac->Start();
  m_phy->Start();
  NetDevice::DoStart();
  //m_txParams->printModel();
  uint64_t t = boost::lexical_cast<uint64_t>(m_txParams->getElement(ModelVocabulary::CALL,"radioStart")->getAttributeValue("time"));
  Time run_time=MilliSeconds(t);
  m_startUpEvent = Simulator::Schedule(run_time, &TosNetDevice::radioStartDone, this);
}
Ptr<Packet>
TosNetDevice::TosToNsPacket(message_t* msg) {
//	Ptr <Packet> pkt =Create <Packet> (Packet(reinterpret_cast<uint8_t*>(msg),
//							sizeof(message_t)));
	return Create <Packet> (Packet(reinterpret_cast<uint8_t*>(msg),sizeof(message_t)));;
}

message_t*
TosNetDevice::NsToTosPacket(Ptr<Packet> packet, const WifiMacHeader* hdr) {
	WifiMacHeader hdrr;
	message_t * msg  = (message_t*) malloc(sizeof(message_t));
	packet->RemoveHeader(hdrr);
	packet->CopyData(reinterpret_cast< uint8_t*>(msg), sizeof(message_t));
	NS_LOG_FUNCTION_NOARGS();

	memcpy((void *)&m_rx_msg, (const void *)msg, sizeof(message_t));
	//printTosPacket((char *) &m_rx_msg);
	free(msg);
	return &m_rx_msg;
}
void
TosNetDevice::SendDone(uint8_t error){
  //uint64_t t = boost::lexical_cast<uint64_t>(m_txParams->getElement(ModelVocabulary::CALLBACK,"sendDone")->getAttributeValue("time"));
  Time run_time=MicroSeconds(10);
  m_sendEvent = Simulator::Schedule(ns3::MicroSeconds(run_time), &TosNetDevice::DeviceSendDone, this, 0);

}

void TosNetDevice::DeviceSendDone(uint8_t error) {
  m_state = RADIO_STATE_ON;
  NS_LOG_FUNCTION("DEVICE_SEND_DONE");
  m_busy = false;
  //Simulator::Remove(m_sendEvent);
  c_ns2tosSendDone(error);
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
//	m_node=0;
//	m_tos_mac->Dispose();
//	m_phy->Dispose();
//	m_tos_mac=0;
//	m_phy=0;
//	m_phyListener=0;
	m_ns3totos=0;

	delete m_phyListener;
	NetDevice::DoDispose ();
}


message_t
TosNetDevice::GetCurrentMsg(){
	return m_tx_msg;
}

void
TosNetDevice::ForwardUp(Ptr<Packet> packet, const WifiMacHeader* hdr) {
  std::cerr<<"TosNetDevice::ForwardUp " <<std::endl;
  if(m_state != RADIO_STATE_TX) {
        m_rx_pkt = packet->Copy();
	message_t * msg = NsToTosPacket(m_rx_pkt, hdr);
	std::cerr<<"TosNetDevice::ForwardUp " <<std::endl;
	  c_ns2tosRx((void*) msg);
	} else {
	  NS_LOG_FUNCTION("RX in RADIO_STATE_TX"<<m_node->GetId());
	}
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
TosNetDevice::SetRadioStartDoneCallback(Callback<void,int> c){
  c_ns2tosStartDone =c;
}
void
TosNetDevice::SetDeviceSendDoneCallback(Callback<int,int> c){
  c_ns2tosSendDone=c;
}
void
TosNetDevice::SetReceiveMessageCallback(Callback<int, void *> c){
  c_ns2tosRx =c;
}

void
TosNetDevice::SetIfIndex(const uint32_t index) {
	NS_LOG_FUNCTION(this << "NOT in use");
	m_ifIndex = index;
}



void TosNetDevice::CompleteConfig(void) {
	if (m_tos_mac == 0 || m_phy == 0 || m_node == 0)
	{ return; }
	  m_tos_mac->SetPhy(m_phy);
	  m_tos_mac->SetRxCallback (MakeCallback (&TosNetDevice::ForwardUp, this));
	  m_tos_mac->SetTxCallback(MakeCallback(&TosNetDevice::SendDone, this));
//	  m_tos_mac->ReceiveError (MakeCallback (&TosWifiNetDevice::LinkUp, this));
//	  m_tos_mac->ReceiveOk (MakeCallback (&TosWifiNetDevice::LinkDown, this));
	  m_phyListener = new PhyTosListener (this);
	  m_phy->RegisterListener(m_phyListener);
	  m_configComplete = true;
	  m_busy = false;
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


Address
TosNetDevice::GetMulticast(Ipv4Address multicastGroup) const {
  return Mac48Address::GetMulticast (multicastGroup);
}

Address
TosNetDevice::GetMulticast (Ipv6Address addr) const{
  return Mac48Address::GetMulticast (addr);
}

void
TosNetDevice::setNs3ToTos(Ns3ToTosProxy * nstos){
	m_ns3totos=nstos;
}

void
TosNetDevice::SetRadioModel(Ptr<HardwareModel> model){
  m_txParams = model;
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
void
TosNetDevice::SetPromiscReceiveCallback(PromiscReceiveCallback cb) {
  NS_LOG_FUNCTION(this << "NOT implemented");
}

bool
TosNetDevice::SupportsSendFrom(void) const {
  NS_LOG_FUNCTION(this << "NOT implemented");
  return false;
}
bool
TosNetDevice::SendFrom(Ptr<Packet> packet, const Address& source,
    const Address& dest, uint16_t protocolNumber) {
  NS_LOG_FUNCTION(this << "NOT implemented");
  return false;
}
} /* namespace ns3 */
