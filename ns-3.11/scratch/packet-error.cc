/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ns3/core-module.h"
#include "ns3/packet.h"
#include "ns3/ptr.h"
#include "ns3/wifi-mac-header.h"
#include "ns3/wifi-mac-trailer.h"
#include "ns3/mac48-address.h"

NS_LOG_COMPONENT_DEFINE ("ScratchSimulator");

typedef struct message_t {
  uint64_t num;
  uint32_t lgn;
}__attribute__ ((__packed__)) message_t;

using namespace ns3;
class CopyOne : public Object {
public:
  typedef Callback<void, Ptr<Packet>, const WifiMacHeader*> MyCallback;
  CopyOne();
  virtual ~CopyOne();
  void setCallback(MyCallback cb);
  void ReceiveOk(Ptr<Packet> packet,const WifiMacHeader* hdr);
  void DoStart();
  void DoDispose();
private:
  MyCallback m_forward;
  Ptr<Packet> m_currentPacket;


};

class CopyTwo : public Object {
public:
  CopyTwo();
  virtual ~CopyTwo();
  void ForwardUp(Ptr<Packet> packet, const WifiMacHeader* hdr);
  void DoStart();
  void DoDispose();
  void setCopyOne(Ptr<CopyOne> cp);
private:
  Ptr<Packet> m_rx_pkt;
  Ptr<CopyOne> m_cp;
  message_t m_rx_msg;
};

CopyOne::CopyOne(){}
CopyOne::~CopyOne(){}
void CopyOne::DoStart(){}
void CopyOne::DoDispose(){}
void CopyOne::ReceiveOk(Ptr<Packet> pkt,const WifiMacHeader* hdrr){
  WifiMacHeader hdr;
  m_currentPacket = pkt->Copy();
  m_currentPacket->RemoveHeader(hdr);
  WifiMacTrailer fcs;
  m_currentPacket->RemoveTrailer(fcs);
  m_forward(m_currentPacket, &hdr);
}
void CopyOne::setCallback(MyCallback cb){
  m_forward=cb;
}

CopyTwo::CopyTwo(){}
CopyTwo::~CopyTwo(){}
void CopyTwo::DoStart(){
  if(m_cp)
    m_cp->setCallback(MakeCallback (&CopyTwo::ForwardUp, this));
}
void CopyTwo::DoDispose(){}
void CopyTwo::setCopyOne(Ptr<CopyOne> one){
  m_cp=one;
}
void CopyTwo::ForwardUp(Ptr<Packet> packet, const WifiMacHeader* hdr){
  WifiMacHeader hdrr;
  m_rx_pkt = packet->Copy();
  m_rx_pkt->RemoveHeader(hdrr);
  m_rx_pkt->CopyData(reinterpret_cast< uint8_t*>(&m_rx_msg), sizeof(message_t));
}


int main (int argc, char *argv[])
{
  NS_LOG_UNCOND ("Scratch Simulator");
  Ptr<CopyOne> cp1=CreateObject<CopyOne>();
  Ptr<CopyTwo> cp2=CreateObject<CopyTwo>();
  cp1->DoStart();
  cp2->setCopyOne(cp1);
  cp2->DoStart();
  message_t *msg = (message_t*) malloc(sizeof(message_t));
  Ptr<Packet> m_tx;
  for(uint64_t i = 0; i> 100000; i++){
      msg->num=i;
      m_tx= Create <Packet> (Packet(reinterpret_cast<uint8_t*>(msg),sizeof(message_t)));
      WifiMacHeader hdr;
      hdr.SetTypeData();
      hdr.SetAddr1(Mac48Address::GetBroadcast());
      hdr.SetDsNotFrom();
      hdr.SetDsNotTo();
      m_tx->AddHeader(hdr);
      cp1->ReceiveOk(m_tx->Copy(), &hdr);
  }
  //Set run-time for the simulation
  free(msg);
   Simulator::Stop(Seconds(10000));
   //Run simulation
   Simulator::Run();
  //Clean up all objects
   Simulator::Destroy ();
}
