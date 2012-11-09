#!/usr/bin/python

import SocketServer
import commands
import socket
import threading
import logging
import struct
from SocketServer import ThreadingMixIn
from SimJobHandler import *

logger = logging.getLogger('sim-logger')
handler = logging.FileHandler('sim.log')
logger.addHandler(handler)
logger.setLevel(logging.INFO)

jobb_queue = JobQueue()

class LoggingTCPHandler(SocketServer.BaseRequestHandler):
	"""
	Handle incomming requests
	
	host:		host_id
	worker:		thread_id
	type:		1/0 full or summary log
	msg:		message to save
	"""

	
	def handle(self):
		# self.request is the TCP socket connected to the client
		size_1 = (3*32)/8
		header = self.unpackHeader(self.getRawData(size_1))

		print " thread %s type %s msg: %s" %(header['worker'],header['type'], header['msg_sz'])

		raw = self.getRawData(header['msg_sz'])

		string = struct.unpack('!%ds'%header['msg_sz'], raw)
		print "%s" %(string)
		self.sendData(self.getJobbString(jobb_queue.getJob()))
		
	def getJobbString(self, job):
		cmd="build/src/symphony/examples/./ns3-dev-clock-test-debug --simLength=%s --realTime=%s --numNodes=%s" %(job['runtime'],job['real-time'], job['numN'])	
		return cmd
	
	def sendData(self, data):
		self.request.send(data)

	def getRawData(self, size):
		try:
			raw = self.request.recv(size)
			while len(raw) < size:
				tmp = self.request.recv(1)
				if not tmp:
					break
				raw += tmp
		except Exception, e:
			print "Exception %s" %e
			return Null
		return raw
		
	def unpackHeader(self,raw):
		header={}
		data = struct.unpack('!III', raw)
		header['worker'] = data[0]
		header['type'] = data[1]
		header['msg_sz'] = data[2]
		header['host'] ="ok"
		return header

 
class ThreadingServer(ThreadingMixIn, SocketServer.TCPServer):
	pass



