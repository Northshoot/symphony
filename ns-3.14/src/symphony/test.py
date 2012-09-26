#!/usr/bin/env python
from proxy_generator import *

def main():
    print "running proxy generation test file main"
    Ns3ToTosProxyGenerator("/home/lauril/dev/symphony/ns-3.11/build/debug/symphony.xml")

if __name__ == "__main__":
    main()