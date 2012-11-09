from subprocess import Popen, PIPE, STDOUT
import time
import os
import datetime
from threading import Thread, Lock
from Queue import Queue



class JobQueue:
    def __init__(self):            
        self.folder="nightly-logs/"
        self.runtime=600
        self.incr = 60
        self.number_of_time_jobs=int(self.runtime/self.incr)
        self.max_n = 4000
        self.nodeS= 50
        self.number_of_node_jobs=int(self.max_n/self.nodeS)
        self.queue = Queue()
        self.runLog = open(self.folder+"LOGSUMMARY.SIM."+str(time.time())+"LOG",'w')
        self.runLog.write("Timestamp\tRun\ts_time\tr_time\tnodes\treal-time\tlog size\n")
        self.InitQueue()
        #self.queue.join()
        self.runLog.close() 


    #simulation set ups
    def InitQueue(self):
        runNum=0
        for _ in range(self.number_of_time_jobs):
            run=(1+_)*self.incr
            #for each time we run different nodes
            for __ in range(self.number_of_node_jobs):
                    nod=(1+__)*self.nodeS
                    runNum+=1
                    args={'num':runNum,'runtime':run, 'fileName':self.folder,'real-time':0,'numN':nod}
                    self.queue.put(args)
                    runNum+=1
                    args={'num':runNum,'runtime':run, 'fileName':self.folder,'real-time':1,'numN':nod}
                    self.queue.put(args)

        print "Queue size %s" %self.queue.qsize()

    
    def getJob(self):
        if not self.queue.empty():           
            print "Queue size %s" %self.queue.qsize()
            return self.queue.get()
        else:
            print "Queue empty!"
            return None
    #print queue
    #print queue.qsize()
      
    
