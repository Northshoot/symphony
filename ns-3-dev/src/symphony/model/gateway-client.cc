/*
 * gateway-client.cc
 *
 *  Created on: Aug 14, 2012
 *      Author: lauril
 */

#include "gateway-client.h"

#include <iostream>           // For cerr and cout
#include <cstdlib>            // For atoi()
#include <string>              // for string
#include "helper/practical-socket.h"

using namespace std;


WSNGatewayClient::WSNGatewayClient(string url, unsigned short port)
  {
    this.url = url;
    this.port = port;
    clientsocket = NULL;
  }

WSNGatewayClient::~WSNGatewayClient()
  {
    // TODO Auto-generated destructor stub
  }

void
WSNGatewayClient::connect(){
  try {
      clientsocket = TCPSocket(url, port);
  }catch(SocketException &e) {
      cerr << e.what() << endl;
      exit(1);
    }
}

void
WSNGatewayClient::sendData( void * data, int size){
  clientsocket.send(data, size);
}

void
WSNGatewayClient::disconnect() {
  clientsocket.cleanUp();
  clientsocket = NULL;
}

