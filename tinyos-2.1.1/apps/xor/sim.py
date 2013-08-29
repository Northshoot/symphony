import sys
from TOSSIM import *

t = Tossim([])
 
t.addChannel("Boot", sys.stdout)
 
m = t.getNode(0);
m.bootAtTime(1)

 
for i in range(0, 60):
  t.runNextEvent()
 
for i in range(0, 20):
  t.runNextEvent()
