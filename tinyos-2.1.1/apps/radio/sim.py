#! /usr/bin/python
import sys
from TOSSIM import *
from RadioCountMsg import *

t = Tossim([])
m = t.mac()
r = t.radio()

t.addChannel("RadioCountToLedsC", sys.stdout)

m = t.getNode(0)
m.bootAtTime(1)
m = t.getNode(1)
m.bootAtTime(1000)

for i in range(60):
  t.runNextEvent()

msg = RadioCountMsg()
array = [0] * 121
msg.set_counter(array);

pkt = t.newPacket()
pkt.setData(msg.data)
pkt.setType(msg.get_amType())
pkt.setDestination(1)

print "Delivering " + str(msg) + " to 0 at " + str(t.time() + 3);
pkt.deliver(1, t.time() + 3)


for i in range(20):
  t.runNextEvent()
