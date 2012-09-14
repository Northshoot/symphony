/*
 * gateway-client.h
 *
 *  Created on: Aug 14, 2012
 *      Author: lauril
 * more info http://cs.baylor.edu/~donahoo/practical/CSockets/practical/
 * 
 */

#ifndef TOS_GATEWAY_CLIENT_H_
#define TOS_GATEWAY_CLIENT_H_
#include "ns3/application.h"
#include "ns3/traced-callback.h"
#include "ns3/nstime.h"
#include "ns3/inet-socket-address.h"
#include "ns3/simulator.h"
#include <map>
#include <string>

namespace ns3 {

class Socket;
/**
 * \brief an application which sends one data packet to destination address
 * Application is controlled via connect, disconnect.
 *
 */
class WSNGatewayClient : public Application
  {
  public:
    static TypeId GetTypeId (void);
    WSNGatewayClient();
    virtual ~WSNGatewayClient();
    void Receive (Ptr<Socket> socket);
    
    void sendData( uint8_t * data, int size);
    void connect();
    void disconnect();
    
   private:
    void Write32 (uint8_t *buffer, const uint32_t data);
    void Read32 (const uint8_t *buffer, uint32_t &data);

    // inherited from Application base class.
    virtual void StartApplication (void);
    virtual void StopApplication (void);
    virtual void DoDispose (void);
    uint32_t GetApplicationId (void) const;


    /// Remote address
    Ipv4Address m_remote;
    /**
     * Specifies  the number of data bytes to be sent.
     * The default is 56, which translates into 64 ICMP data bytes when combined with the 8 bytes of ICMP header data.
     */
    uint32_t m_size;


    Ptr<Socket> m_socket;
    uint16_t m_seq;
    TracedCallback<Time> m_traceRtt;
    /// produce ping-style output if true
    bool m_verbose;

    /// received packets counter
    uint32_t m_recv;
    uint16_t m_port;
    /// Start time to report total ping time
    Time m_started;

    /// Next packet will be sent
    EventId m_next;
    /// All sent but not answered packets. Map icmp seqno -> when sent
    std::map<uint16_t, Time> m_sent;
  };
}
#endif /* TOS_GATEWAY_CLIENT_H_ */
