#!/usr/bin/python
import commands
import socket
import time
import struct
import sys

class Worker(Thread):
    """This is the main worker - it will process jobs as long as the "job
    queue" has jobs available.
    """
    # this lock is used to avoid messing up the screen output - only
    # one worker will write to screen at a given time. It is
    # technically a Mutual Exclusion (mutex)
    screen_mutex = Lock()

    def __init__(self, queue):
        # initialize the base class
        super(Worker, self).__init__()
        self.queue = queue
        self.remote

    def log(self, message):
        #send data to the server     
        msg="{timestamp:%d-%b-%Y %H:%M:%S.%f UTC}\t{message}".format(timestamp=datetime.datetime.utcnow(),
                                         message=message)
        if(message):
            self.file.write(msg+'\n')
            self.file.flush()
            


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
        
        def getCommand(self):	
			s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			s.connect(self.remote)
			#tosend = struct.pack('!IIBQI',ce,2,si,time.time()*1000,len(data))
			string ='halloooohalloooohalloooohalloooohalloooo'
			tosend = struct.pack('!III%ds'%len(string),1,2,len(string),string)
			print "Sending %s"%len(string)
			s.send(tosend)
			received = s.recv(1024)
			print "Received: {}".format(received)
			s.close()
			if max_tests < 0:
				sys.exit()
			max_tests-=1
			
            
"""
Send some random testdata.

host:		host_id
worker:		thread_id
type:		1/0 full or summary log
msg:		message to save
"""

if __name__ == '__main__':
	max_tests = 10
	while True:
		for ce in xrange(1,10):
			
			s = socket.socket(
			socket.AF_INET, socket.SOCK_STREAM)
			s.connect(('130.240.231.18', 12345))
			#tosend = struct.pack('!IIBQI',ce,2,si,time.time()*1000,len(data))
			string ='halloooohalloooohalloooohalloooohalloooo'
			tosend = struct.pack('!III%ds'%len(string),1,2,len(string),string)
			print "Sending %s"%len(string)
			s.send(tosend)
			received = s.recv(1024)
			print "Received: {}".format(received)
			s.close()
			if max_tests < 0:
				sys.exit()
			max_tests-=1


