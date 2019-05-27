# Echo client program
import socket
import sys

board = ""

def updateBoard(recived_data):
	squares = recived_data.split(';')
	for el in squares:
		print (el)
		# figure_details = el.split(,)


	return True;


HOST = '0::1'    # The remote host
PORT = 8001              # The same port as used by the server

try:
	# s = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
	# s.connect((HOST, PORT))
	# move = b'None'
	# s.send(move)
	# data = s.recv(2048)			# Return data from server
	# recived_data = str(data, 'utf-8')
	recived_data = "0;0;0;white,white,King,e1,#xDDD;black,black,Queen,b3"
	updateBoard(recived_data[6:]);
	# print('Received:', repr(data))
	# print('len of data', len(data))

	# s.close()

except socket.error as e:
    print ("Socket error({0}): {1}".format(e.errno, e.strerror))
except:
    print ("Unexpected error:", sys.exc_info()[0])
    raise
