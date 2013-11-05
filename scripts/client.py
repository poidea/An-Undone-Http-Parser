import socket
import time
import sys, os

if len(sys.argv) == 2:
	server = 'localhost'
	port   = int(sys.argv[1])
else:
	print "correct format: (...).py [port]\n";
	sys.exit(0)

sock = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
sock.connect( (server, port) )

time.sleep(2)

sock.send('1')
print sock.recv(1024)

sock.close()
