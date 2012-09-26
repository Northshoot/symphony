#!/bin/python
#this is helper script to allow remote start of *THIS*
#simulation instance and store the results in S3 bucket
#dependencies:
#boto, cloud-utils
#PRE: existance of /etc/boto.cfg 
#
#USAGE:

import sys
from boto.s3.key import Key
from boto.s3.connection import S3Connection
import time

from socket import *
from threading import *

KEEPRUNNING=True

def handler(clientsock,addr):
       while 1:
             data = clientsock.recv(BUFSIZ)
             if not data: break
             if str(data) == 'close':
                 msg='bye bye'
                 print 'Shutting down server'
                 clientsock.send(msg)
                 clientsock.close()
                 KEEPRUNNING = False
             elif str(data)=='bye':
                 msg='nooo don\'t leave!'
             else:
                 msg='say what?'
             clientsock.send(msg)
  
       clientsock.close()




def storeAll(name, path):
    #creates are bucket for current simulation
    #recall that buckets need to have unique name
    try:
        conn =S3Connection()
        bucket = conn.create_bucket(name)
        k = Key(bucket)
    except:
        # error handling code here
        return 1  # exit on error
    finally:
        conn.close()
    return 0  # exit errorlessly

def main(args):
    try:
       HOST = 'localhost'
       PORT = 21567
       BUFSIZ = 1024
       ADDR = (HOST, PORT)
       serversock = socket(AF_INET, SOCK_STREAM)
       serversock.bind(ADDR)
       serversock.listen(2)

       while KEEPRUNNING:
             print 'waiting for connection...'
             clientsock, addr = serversock.accept()
             print '...connected from:', addr
             ct=Thread(target=handler, args=(clientsock, addr))
             ct.run()
    except:
        # error handling code here
        return 1  # exit on error
    else:
        print 'Got exit command'
        return 0  # exit errorlessly



 
if __name__ == '__main__':
    sys.exit(main(sys.argv))
