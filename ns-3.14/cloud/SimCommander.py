#!/usr/bin/python

import sys
from SimJobHandler import *
from LogServer import *
from CloudHelper import *





if __name__ == "__main__":
    logger.info("started")
    #start the server
    try:    
        
        server = ThreadingServer(("130.240.231.18", 12345), LoggingTCPHandler)
        server.serve_forever()
        print "local server started"
#        c = Connector()
#        print 'starting simulation fleet'
#        c.start_simulation_instances(2)       



    except (KeyboardInterrupt, SystemExit):
        print "Got keyboard"
        server.shutdown()
        sys.exit()
        raise KeyboardInterrupt
    except Exception ,e:
        print "Error %s" %str(e)
        