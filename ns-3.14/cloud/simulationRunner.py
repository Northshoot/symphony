#! /usr/bin/env python
## -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-
#
from subprocess import Popen, PIPE, STDOUT
import time
import os
import datetime
from threading import Thread, Lock
from Queue import Queue


def h_r(quantity, multiple=1024):
    if quantity == 0:
        quantity = +0
    SUFFIXES = ["B"] + [i + {1000: "B", 1024: "iB"}[multiple] for i in "KMGTPEZY"]
    for suffix in SUFFIXES:
        if quantity < multiple or suffix == SUFFIXES[-1]:
            if suffix == SUFFIXES[0]:
                return "%d%s" % (quantity, suffix)
            else:
                return "%.1f%s" % (quantity, suffix)
        else:
            quantity /= multiple

def niceTime(t):
    return str(datetime.timedelta(seconds=int(t)))



class Worker(Thread):
    """This is the main worker - it will process jobs as long as the "job
    queue" has jobs available.
    """
    # this lock is used to avoid messing up the screen output - only
    # one worker will write to screen at a given time. It is
    # technically a Mutual Exclusion (mutex)
    screen_mutex = Lock()

    def __init__(self, queue, file):
        # initialize the base class
        super(Worker, self).__init__()
        self.queue = queue
        self.file=file

    def log(self, message):
        #Worker.screen_mutex.acquire()        
        msg="{timestamp:%d-%b-%Y %H:%M:%S.%f UTC}\t{message}".format(timestamp=datetime.datetime.utcnow(),
                                         message=message)
        if(message):
            self.file.write(msg+'\n')
            self.file.flush()
            
        #Worker.screen_mutex.release()

    def run(self):
        while True:
            job = self.queue.get()
            msg="{timestamp:%d-%b-%Y %H:%M:%S.%f UTC}".format(timestamp=datetime.datetime.utcnow())
            Worker.screen_mutex.acquire()   
            print "%s Queue size %s" %(msg,self.queue.qsize())
            Worker.screen_mutex.release()
            cmd="build/src/symphony/examples/./ns3-dev-clock-test-debug --simLength=%s --realTime=%s --numNodes=%s" %(job['runtime'],job['real-time'], job['numN'])
            before = time.time()
            p = Popen(cmd.split(), stdout=PIPE, stderr=STDOUT)
            #p = Popen(['ls','-all'], stdout=PIPE, stderr=STDOUT)
            stdout, stderr = p.communicate()

            after = time.time()
            fName = job['fileName']+str(int(before))+"."+str(job['runtime'])+"."+str(job['numN'])+"."+str(job['real-time'])+".sim.log"
            
            f=open(fName,'w')  
            if(stdout):
                f.write(stdout)
                f.close
            
            if stderr:
              f=open(job['fileName']+str(int(before))+"."+".sim.error",'w')
              f.write(stderr)
              f.close()
            statinfo = os.stat(fName)          
            msg = "%s\t%s\t%s\t%s\t%s\t%s" \
                %(job['num'],niceTime(job['runtime']),niceTime(after-before),job['numN'],job['real-time'],h_r(statinfo.st_size))
            self.log(msg)
            
            # when the job is done, you signal the queue - refer to
            # the Queue module documentation
            self.queue.task_done()
       


def main(number_of_workers):
    folder="nightly-logs/"
    runtime=600
    incr = 60
    number_of_time_jobs=int(runtime/incr)
    max_n = 4000
    nodeS= 50
    number_of_node_jobs=int(max_n/nodeS)
    queue = Queue()
    runLog = open(folder+"LOGSUMMARY.SIM."+str(time.time())+"LOG",'w')
    runLog.write("Timestamp\tRun\ts_time\tr_time\tnodes\treal-time\tlog size\n")



    #simulation set ups
    runNum=0
    for _ in range(number_of_time_jobs):
        run=(1+_)*incr
        #for each time we run different nodes
        for __ in range(number_of_node_jobs):
                nod=(1+__)*nodeS
                runNum+=1
                args={'num':runNum,'runtime':run, 'fileName':folder,'real-time':0,'numN':nod}
                queue.put(args)
                runNum+=1
                args={'num':runNum,'runtime':run, 'fileName':folder,'real-time':1,'numN':nod}
                queue.put(args)

    print "Queue size %s" %queue.qsize()

    for _ in range(number_of_workers):
        print "Setting upp %s of %s workers" %(_,number_of_workers)
        worker = Worker(queue,runLog)
        worker.daemon = True        
        worker.start()
    #print queue
    #print queue.qsize()
    queue.join()
    runLog.close()   

if __name__ == "__main__":
    import multiprocessing
    # call main             
    main(multiprocessing.cpu_count())
