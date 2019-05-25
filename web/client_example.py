# Echo client program
import socket
import sys

argc = len(sys.argv)


if argc > 2:
    #HOST = 'localhost'    # The remote host
    HOST = sys.argv[2]
else:
    HOST = '0::1'    # The remote host

if argc >1:
    PORT = int(sys.argv[1])              # The same port as used by the server
else:
    PORT = 8001              # The same port as used by the server

for c in range( argc):
    print( "Arg" + str(c) + "=" + sys.argv[c] )

try:
	s = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
	s.connect((HOST, PORT))
	move = b'b4'
	s.send(move)
	data = s.recv(1024)			# Return data from server
	print('Received:', repr(data))

	s.close()

except socket.error as e:
    print ("Socket error({0}): {1}".format(e.errno, e.strerror))
except:
    print ("Unexpected error:", sys.exc_info()[0])
    raise
