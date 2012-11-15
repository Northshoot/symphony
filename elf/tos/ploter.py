import numpy as np
from matplotlib.mlab import *
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.path as path

experiment = dict(
                  nodes=FormatInt(),
                  open=FormatInt(),
                  load=FormatInt(),
                  excec=FormatInt(),
                  close=FormatInt(),
                  )


    
data= csv2rec('SUMMARY.EFL-TESTS.7.0KiB.LOG',delimiter='\t')

data.sort()
press_mc=0.001 #micro seconds
press_ms=0.000001 #milli seconds
press_s = 1/1000000000

def getData(type, prec=None):
    ret=[]
    if type == 'nodes':
        ret= [int(z[0]) for z in data]
    elif type == 'open':
        ret = [int(z[1]) for z in data]
    elif type == 'load':
        ret = [int(z[2]) for z in data]
    elif type == 'excec':
        ret = [int(z[3]) for z in data]
    elif type == 'close':
        ret = [int(z[4]) for z in data]
        
    if prec =='ms':
        ret=[x*press_ms for x in ret]
    elif prec =='mc':
        ret=[x*press_mc for x in ret]
    elif prec =='s':
        ret=[x*press_s for x in ret]
    elif prec is None:
        pass
    
    return ret
        
#nodes = [int(z[0]) for z in data]
#open = [int(z[1]*press) for z in data]
#load = [int(z[2]*press) for z in data]
#excec = [int(z[3]) for z in data]
#close = [int(z[4]*press) for z in data]

norm_excec = [x/y for x,y in zip(getData('excec'),getData('nodes'))]    

print norm_excec
print "Mean %f" %np.mean(norm_excec, dtype=np.float64)
print "Average %f" %np.average(norm_excec)
print "Variance %f" %np.var(norm_excec, dtype=np.float64)
print "Standard deviation %f" %np.std(norm_excec, dtype=np.float64)

fig = plt.figure()
ax = fig.add_subplot(111)
ax.set_title('Histogram of call time per function')
n, bins = np.histogram(norm_excec,15)
# get the corners of the rectangles for the histogram
left = np.array(bins[:-1])
right = np.array(bins[1:])
bottom = np.zeros(len(left))
top = bottom + n


# we need a (numrects x numsides x 2) numpy array for the path helper
# function to build a compound path
XY = np.array([[left,left,right,right], [bottom,top,top,bottom]]).T

# get the Path object
barpath = path.Path.make_compound_path_from_polys(XY)

# make a patch out of it
patch = patches.PathPatch(barpath, facecolor='blue', edgecolor='white', alpha=0.8)
ax.add_patch(patch)

# update the view limits
ax.set_xlim(left[0], right[-1])
ax.set_ylim(bottom.min(), top.max())
ax.set_xlabel('Average time per call in Nanoseconds')
ax.set_ylabel('Number of records')


fig1 = plt.figure()
ax1 = fig1.add_subplot(111)
ax1.set_title('Number of nodes vs function call')
ax1.plot( norm_excec, getData('nodes'),'o')
ax1.set_xlabel('Average time per call in Nanoseconds')
ax1.set_ylabel('Number of nodes')

fig2 = plt.figure()
ax2 = fig2.add_subplot(111)
ax2.set_title('Time to call one function vs number of nodes')
ax2.plot( getData('excec','ms'), getData('nodes'),'o')
ax2.set_xlabel('Time per call in Nanoseconds')
ax2.set_ylabel('Number of nodes')

fig3 = plt.figure()
ax3 = fig3.add_subplot(111)
ax3.set_title('Time to open images')
ax3.plot( getData('close','ms'), getData('nodes'),'o')
ax3.set_xlabel('Time in microseconds')
ax3.set_ylabel('Number of nodes')

#
plt.show()


