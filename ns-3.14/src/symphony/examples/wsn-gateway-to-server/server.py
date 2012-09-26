from socket import *
from threading import *
import sys
from ctypes import *

BUFSIZ = 8

def handler(clientsock,addr):
    data = clientsock.recv(BUFSIZ)
    #convert data from 
    test = c_char_p(data).value
    print "Data %s of size %s new data %s" %(str(data), str(sys.getsizeof(data)), test)
    #msg = "Thanks, bye!"
    #clientsock.send(msg)
    clientsock.close()

if __name__=='__main__':
       HOST = '130.240.175.138'
       PORT = 21567
       
       ADDR = (HOST, PORT)
       serversock = socket(AF_INET, SOCK_STREAM)
       serversock.bind(ADDR)
       serversock.listen(2)
       serversock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)

       while 1:
             print 'waiting for connection...'
             clientsock, addr = serversock.accept()
             print '...connected from:', addr
             ct=Thread(target=handler, args=(clientsock, addr))
             try:  
                ct.run()
                
             except Exception as errtxt:
                print errtxt

