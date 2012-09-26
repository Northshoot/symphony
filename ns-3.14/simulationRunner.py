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
        Worker.screen_mutex.acquire()        
        print("{timestamp:%d-%b-%Y %H:%M:%S.%f UTC} "
              "{name}: {message}".format(timestamp=datetime.datetime.utcnow(),
                                         name=self.getName(),
                                         message=message))
        if(message):
            self.file.write(message+'\n')
            self.file.flush()
            
        Worker.screen_mutex.release()

    def run(self):
        while True:
            job = self.queue.get()
            before = time.time()
            args1="tos-simple --simLength=%s --realTime=%s" %(job['runtime'],job['real-time'])
            p = Popen(['./waf','--run='+args1], stdout=PIPE, stderr=STDOUT)
            stdout, stderr = p.communicate()
            after = time.time()
            fName = job['fileName']+str(int(before))+"."+str(job['runtime'])+".sim.log"
            
            f=open(fName,'w')  
            if(stdout):
                f.write(stdout)
                f.close
            
            if stderr:
              f=open(job['fileName']+str(int(before))+"."+".sim.error",'w')
              f.write(stderr)
              f.close()
            statinfo = os.stat(fName)          
            msg = "Finished run #%s simulation time = %s  running time %s log size %s" \
                %(job['num'],niceTime(job['runtime']),niceTime(after-before),h_r(statinfo.st_size))
            self.log(msg)
            os.remove(fName)
            # when the job is done, you signal the queue - refer to
            # the Queue module documentation
            self.queue.task_done()


def main(number_of_workers):
    folder="nightly-logs/"
    runtime=31536000
    simTime = 2419200
    incr = 3600*24*7
    number_of_jobs=int((runtime-simTime)/incr)
    queue = Queue()
    runLog = open(folder+"LOGSUMMARY.SIM.LOG",'w')

    for _ in range(number_of_jobs):
        worker = Worker(queue,runLog)
        worker.daemon = True        
        worker.start()


    for _ in range(number_of_jobs):
        args={'num':_+1,'runtime':simTime, 'fileName':folder,'real-time':0}
        queue.put(args)
        simTime+=incr

    queue.join()
    runLog.close()   

if __name__ == "__main__":
    import multiprocessing
    # call main             
    main(multiprocessing.cpu_count())
