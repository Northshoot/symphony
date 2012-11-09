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
            
if __name__ == "__main__":
    import multiprocessing
    #update svn
    #build waf
    #get app name
    
    # create and run threads           
    for _ in range(multiprocessing.cpu_count()):
        worker = Worker(queue,runLog)
        worker.daemon = True        
        worker.start()
