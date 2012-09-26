/*
 * gateway-client.h
 *
 *  Created on: Aug 14, 2012
 *      Author: lauril
 * simple example of app sending a packet to remote python server end closing connection
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
    
    void sendData( const uint8_t * data, int size);

    
   private:
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
    //remote port
    uint16_t m_port;
    /// Start time to report total ping time
    Time m_started;

  };
}
#endif /* TOS_GATEWAY_CLIENT_H_ */
