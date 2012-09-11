#! /usr/bin/env python
## -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-
#
from subprocess import Popen, PIPE, STDOUT
import time
import os
import datetime

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

folder="nightly-logs/"

runLog = open(folder+"LOGSUMMARY.SIM.LOG",'w')

run=True
runtime=31536000
simTime = 100000
num=0
while runtime >=0:
    before = time.time()
    fName = folder+str(int(before))+"."+str(simTime)+".sim.log"
    f=open(fName,'w')
    args1="tos-simple --simLength=%s --realTime=0" %simTime
    p = Popen(['./waf','--run='+args1], stdout=PIPE, stderr=STDOUT)
    
    stdout, stderr = p.communicate()
    after = time.time()
    f.write(stdout)
    f.close
    statinfo = os.stat(fName)
    if stderr:
      f=open(fName+".sim.error",'w')
      f.write(stderr)
      f.close()
    msg = "Finished run #%s simulation time = %s  running time %s log size %s" \
        %(num,niceTime(simTime),niceTime(after-before),h_r(statinfo.st_size))
    print msg
    runLog.write(msg)
    runLog.flush()
    os.remove(fName)
    runtime-=simTime
    simTime+=100000
    num+=1
     
runLog.close()     