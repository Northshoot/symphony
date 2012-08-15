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
#include <string>
#include "helper/practical-socket.h"

class WSNGatewayClient
  {
  public:
    WSNGatewayClient(string url, unsigned short port);
    virtual ~WSNGatewayClient();
    
    void sendData(void *data, int size);
    void connect();
    void disconnect();
    
   private:
    string url;
    unsigned short port;
    const int RCVBUFSIZE = 32; 
    TCPSocket clientsocket;
  };

#endif /* TOS_GATEWAY_CLIENT_H_ */
