#! /usr/bin/python
import sys
from tinyos.tossim.TossimApp import *
from TOSSIM import *
#from BooterMsg import *

n = NescApp()
t = Tossim(n.variables.variables())
r = t.radio()


#t.addChannel("Snoop",sys.stdout)
t.addChannel("Info",sys.stdout)
#t.addChannel("Summary",sys.stdout)
#t.addChannel("LedsC", sys.stdout)


for i in range(0, 1):
  m = t.getNode(i)
  m.bootAtTime(3 * i + 1)

f = open("topo.txt", "r")
for line in f:
  s = line.split()
  if s:
    r.add(int(s[0]), int(s[1]), float(s[2]))

noise = open("/home/lauril/dev/tinyos_source/tinyos-main/tos/lib/tossim/noise/meyer-heavy.txt", "r")
for line in noise:
  s = line.strip()
  if s:
    val = int(s)
    for i in range(10):
      t.getNode(i).addNoiseTraceReading(val)

for i in range(10):
  t.getNode(i).createNoiseModel()


for i in range(10000):
  t.runNextEvent()



