#! /usr/bin/env python
## -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-
#
from subprocess import Popen, PIPE, STDOUT
import time


folder="nightly-logs/"

runLog = open(folder+"LOGSUMMARY.SIM.LOG",'w')

run=True
runtime=302400
simTime = 100
num=0
while runtime >=0:
    before = time.time()
    fName = folder+str(int(before))+"."+str(simTime)
    f=open(fName+".sim.log",'w')
    args1="tos-simple --simLength=%s --realTime=0" %simTime
    p = Popen(['./waf','--run='+args1], stdout=PIPE, stderr=STDOUT)
    
    stdout, stderr = p.communicate()
    after = time.time()
    f.write(stdout)
    f.close
    if stderr:
      f=open(fName+".sim.error",'w')
      f.write(stderr)
      f.close()
    msg = "Finished run #%s simulation time = %s s running time %s s\n" %(num,simTime,str(round(after-before,5)))
    print msg
    runLog.write(msg)
    runtime-=simTime
    simTime+=100
    num+=1
     
runLog.close()     