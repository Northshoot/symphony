Symphony Module Documentation
----------------------------

.. heading hierarchy:
   ------------- Chapter
   ************* Section (#.#)
   ============= Subsection (#.#.#)
   ############# Paragraph (no number)


The introductory paragraph is for describing what this code is trying to
model.

Model Description
*****************

The source code for the new module lives in the directory ``src/symphony``.

Models in symphony allows to run virtualized WSN OS, here is example of usage with 
TinyOS.
Further, NodeModel contains models of hardware peripherals real behavior in time.
The model is prepared for monitoring memory, and energy consumptions. 

Design
======



Scope and Limitations
=====================

Symphony is build to be a generic emulation platform for WSN OS. Example of implementing
OS for virtualization is given on TinyOS.

References
==========

Add academic citations here, such as if you published a paper on this
model, or if readers should read a particular specification or other work.

Usage
*****


Building Symphony
===================
Install all needed tools for NS3, as well TinyOS
Install ns-3 http://shieldroute.blogspot.se/2012/08/install-and-run-ns3-on-amazons-ec2.html
Install TinyOS http://shieldroute.blogspot.se/2012/08/tossim-simulations-on-amazon-aws.html

Additionally install xml parser libxerces-c3.1
$sudo apt-get install libxerces-c3.1*

Then patch TinyOS
patching /usr/lib/ncc/nesc_nx.h:316
Tutorial: http://jungels.net/articles/diff-patch-ten-minutes.html
 ../../helper/nesc_nx.h.symphony.patch

Additionally you will need to set following environment variables,
put them in your .bashrc file and remember to restart terminal

export PATH 
SYMPHONY_NS_VERSION="ns-3.14" 
#only here you need to change
SYMPHONY_BASE="/home/_path_/_to_/symphony"
SYMPHONY_BUILD="$SYMPHONY_BASE/$SYMPHONY_NS_VERSION/build" 
SYMPHONY_SRC="$SYMPHONY_BASE/$SYMPHONY_NS_VERSION/src/symphony" 
TOSROOT_SYMPHONY="$SYMPHONY_BASE/tinyos-2.1.1" 
TOSROOT=$TOSROOT_SYMPHONY 
TOSDIR="$TOSROOT/tos" 
MAKERULES="$TOSROOT/support/make/Makerules" 
CLASSPATH=.:$TOSROOT/support/sdk/java:$TOSROOT/support/sdk/java/tinyos.jar:$CLASSPATH 
PYTHONPATH=$PYTHONPATH:$TOSROOT/support/sdk/python
PYTHONPATH=$PYTHONPATH:$TOSROOT/support/sdk/python
export TOSROOT 
export TOSDIR 
export CLASSPATH 
export MAKERULES 
export PYTHONPATH 
export SYMPHONY_NS_VERSION 
export SYMPHONY_BASE 
export SYMPHONY_BUILD 
export TOSROOT_SYMPHONY 
export SYMPHONY_SRC 
LD_LIBRARY_PATH=/usr/lib:$SYMPHONY_BUILD:$LD_LIBRARY_PATH 
export LD_LIBRARY_PATH 
PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/lib/pkgcofig 
export PKG_CONFIG_PATH

Configure just symphony
./waf --disable-python --disable-tests --enable-modules='symphony' configure

and build it
./waf build

Creating TinyOS Applications
===================
If you have set up your environment properly and have run example applications successfully,
Then you can create your TinyOS application any were. Just copy the Makefile and symphony.xml to 
the same folder were you have your app.
Make sure that the variable TOS_APP in Makefile, have the name of your application.
The Make will build library and copy needed files to ns-3.xx/build directory.

You will also need to create the ns-3 simulation scenario. See examples, for that.
Generally you set up the simulation same way as for wifi app. Expect that you do not need to create 
IP/TCP stack nor application in it, since it is done in your TinyOS app.

Helpers
=======
Most common helpers
TosNodeContainer - given number of nodes creates and stores TosNodes
TosHelper - used to create channel, phy layer, set nodes model, and created 
TosNetDeviceContainer - creates raw connections for communication between TinyOS 
radio and underlying physical/channel.
SymphonySensorContainer - creates a container for the sensors, and connects raw 
readings between OS and sensor model.


Attributes
==========

What classes hold attributes, and what are the key ones worth mentioning?

Output
======

Logging is done in your application as you would do with deploying the system.


Advanced Usage
==============

For debugging within TinyOS you can use __PRETTY_FUNCTION__ variable in order to 
get function name variable.

printf("%s\n",__PRETTY_FUNCTION__);

Examples
========

blink/
gateway/
memory/
sensor/
tos/
tos-hidden-terminal/
time/

remember that running examples you will need to specify the path to the ns3 build directory

Troubleshooting
===============

Make sure you have installed needed components and exporter variables.


Validation
**********
Symphony is tested to work under Ubuntu 11.x, 12.x.

