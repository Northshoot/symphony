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
        self.envviron=os.environ
        self.envviron["LD_LIBRARY_PATH"]=".:../"

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
            args1="%s" %(job['num'])
           
            p = Popen(['./testtos',args1], stdout=PIPE, stderr=STDOUT,env=self.envviron)
            stdout, stderr = p.communicate()
            after = time.time()

            if(stdout):
                msg = "STDOUT: %s" %(stdout)
                self.log(msg)
            
            if stderr:
                msg = "STERR: %s" %(stderr)
                self.log(msg)
   
            msg = "Finished run with  = %s  open libs running time %s" \
                %(job['num'],niceTime(after-before))
            self.log(msg)

            # when the job is done, you signal the queue - refer to
            # the Queue module documentation
            self.queue.task_done()


def main(number_of_workers):
    runtime=100000
    incr = 100
    number_of_jobs=int((runtime)/incr)
    queue = Queue()
    runLog = open("SUMMARY.EFL-TESTS.LOG",'w')

    for _ in range(number_of_workers):
        worker = Worker(queue,runLog)
        worker.daemon = True        
        worker.start()


    for _ in range(number_of_jobs):
        args={'num':_*incr}
        queue.put(args)
  

    queue.join()
    runLog.close()   

if __name__ == "__main__":
    import multiprocessing
    # call main             
    main(multiprocessing.cpu_count()-1)