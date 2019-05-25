from flask import Flask, render_template, request
import socket
import sys

app = Flask(__name__)

# store all squares on board
board = [
	{
		'square_color' : 'white',
		'color': 'black',
		'figure': 'Rook',
		'position': 'a8',
		'code': '#9820'
	},
	{
		'square_color' : 'black',
		'color': 'black',
		'figure': 'Knight',
		'position': 'b8',
		'code': '#9822'
	},
	{
		'square_color' : 'white',
		'color': 'black',
		'figure': 'Bishop',
		'position': 'c8',
		'code': '#9821'
	},
	{

		'square_color' : 'black',
		'color': 'black',
		'figure': 'Queen',
		'position': 'd8',
		'code': '#9819'
	},
	{
		'square_color' : 'white',
		'color': 'black',
		'figure': 'King',
		'position': 'e8',
		'code': '#9818'
	},
	{
		'square_color' : 'black',
		'color': 'black',
		'figure': 'Bishop',
		'position': 'f8',
		'code': '#9821'
	},
	{
		'square_color' : 'white',
		'color': 'black',
		'figure': 'Knight',
		'position': 'g8',
		'code': '#9822'
	},
	{
		'square_color' : 'black',
		'color': 'black',
		'figure': 'Rook',
		'position': 'h8',
		'code': '#9820'
	},
	{
		'square_color' : 'black',
		'color': 'black',
		'figure': 'Pawn',
		'position': 'a7',
		'code': '#9823'
	},
	{
		'square_color' : 'white',
		'color': 'black',
		'figure': 'Pawn',
		'position': 'b7',
		'code': '#9823'
	},
	{
		'square_color' : 'black',
		'color': 'black',
		'figure': 'Pawn',
		'position': 'c7',
		'code': '#9823'
	},
	{
		'square_color' : 'white',
		'color': 'black',
		'figure': 'Pawn',
		'position': 'd7',
		'code': '#9823'
	},
	{

		'square_color' : 'black',
		'color': 'black',
		'figure': 'Pawn',
		'position': 'e7',
		'code': '#9823'
	},
	{
		'square_color' : 'white',
		'color': 'black',
		'figure': 'Pawn',
		'position': 'f7',
		'code': '#9823'
	},
	{
		'square_color' : 'black',
		'color': 'black',
		'figure': 'Pawn',
		'position': 'g7',
		'code': '#9823'
	},
	{
		'square_color' : 'white',
		'color': 'black',
		'figure': 'Pawn',
		'position': 'h7',
		'code': '#9823'
	},
	{
		'square_color' : 'white',
		'color': 'None',
		'figure': 'None',
		'position': 'a6',
		'code': 'None'
	},
	{
		'square_color' : 'black',
		'color': 'None',
		'figure': 'None',
		'position': 'b6',
		'code': 'None'
	},
	{
		'square_color' : 'white',
		'color': 'None',
		'figure': 'None',
		'position': 'c6',
		'code': 'None'
	},
	{
		'square_color' : 'black',
		'color': 'None',
		'figure': 'None',
		'position': 'd6',
		'code': 'None'
	},
	{
		'square_color' : 'white',
		'color': 'None',
		'figure': 'None',
		'position': 'e6',
		'code': 'None'
	},
	{
		'square_color' : 'black',
		'color': 'None',
		'figure': 'None',
		'position': 'f6',
		'code': 'None'
	},
	{
		'square_color' : 'white',
		'color': 'None',
		'figure': 'None',
		'position': 'g6',
		'code': 'None'
	},
	{
		'square_color' : 'black',
		'color': 'None',
		'figure': 'None',
		'position': 'h6',
		'code': 'None'
	},
	{
		'square_color' : 'black',
		'color': 'None',
		'figure': 'None',
		'position': 'a5',
		'code': 'None'
	},
	{
		'square_color' : 'white',
		'color': 'None',
		'figure': 'None',
		'position': 'b5',
		'code': 'None'
	},
	{
		'square_color' : 'black',
		'color': 'None',
		'figure': 'None',
		'position': 'c5',
		'code': 'None'
	},
	{
		'square_color' : 'white',
		'color': 'None',
		'figure': 'None',
		'position': 'd5',
		'code': 'None'
	},
	{
		'square_color' : 'black',
		'color': 'None',
		'figure': 'None',
		'position': 'e5',
		'code': 'None'
	},
	{
		'square_color' : 'white',
		'color': 'None',
		'figure': 'None',
		'position': 'f5',
		'code': 'None'
	},
	{
		'square_color' : 'black',
		'color': 'None',
		'figure': 'None',
		'position': 'g5',
		'code': 'None'
	},
	{
		'square_color' : 'white',
		'color': 'None',
		'figure': 'None',
		'position': 'h5',
		'code': 'None'
	},
	{
		'square_color' : 'white',
		'color': 'None',
		'figure': 'None',
		'position': 'a4',
		'code': 'None'
	},
	{
		'square_color' : 'black',
		'color': 'None',
		'figure': 'None',
		'position': 'b4',
		'code': 'None'
	},
	{
		'square_color' : 'white',
		'color': 'None',
		'figure': 'None',
		'position': 'c4',
		'code': 'None'
	},
	{
		'square_color' : 'black',
		'color': 'None',
		'figure': 'None',
		'position': 'd4',
		'code': 'None'
	},
	{
		'square_color' : 'white',
		'color': 'None',
		'figure': 'None',
		'position': 'e4',
		'code': 'None'
	},
	{
		'square_color' : 'black',
		'color': 'None',
		'figure': 'None',
		'position': 'f4',
		'code': 'None'
	},
	{
		'square_color' : 'white',
		'color': 'None',
		'figure': 'None',
		'position': 'g4',
		'code': 'None'
	},
	{
		'square_color' : 'black',
		'color': 'None',
		'figure': 'None',
		'position': 'h4',
		'code': 'None'
	},
	{
		'square_color' : 'black',
		'color': 'None',
		'figure': 'None',
		'position': 'a3',
		'code': 'None'
	},
	{
		'square_color' : 'white',
		'color': 'None',
		'figure': 'None',
		'position': 'b3',
		'code': 'None'
	},
	{
		'square_color' : 'black',
		'color': 'None',
		'figure': 'None',
		'position': 'c3',
		'code': 'None'
	},
	{
		'square_color' : 'white',
		'color': 'None',
		'figure': 'None',
		'position': 'd3',
		'code': 'None'
	},
	{
		'square_color' : 'black',
		'color': 'None',
		'figure': 'None',
		'position': 'e3',
		'code': 'None'
	},
	{
		'square_color' : 'white',
		'color': 'None',
		'figure': 'None',
		'position': 'f3',
		'code': 'None'
	},
	{
		'square_color' : 'black',
		'color': 'None',
		'figure': 'None',
		'position': 'g3',
		'code': 'None'
	},
	{
		'square_color' : 'white',
		'color': 'None',
		'figure': 'None',
		'position': 'h3',
		'code': 'None'
	},
	{
		'square_color' : 'white',
		'color': 'white',
		'figure': 'Pawn',
		'position': 'a2',
		'code': '#9817'
	},
	{
		'square_color' : 'black',
		'color': 'white',
		'figure': 'Pawn',
		'position': 'b2',
		'code': '#9817'
	},
	{
		'square_color' : 'white',
		'color': 'white',
		'figure': 'Pawn',
		'position': 'c2',
		'code': '#9817'
	},
	{
		'square_color' : 'black',
		'color': 'white',
		'figure': 'Pawn',
		'position': 'd2',
		'code': '#9817'
	},
	{
		'square_color' : 'white',
		'color': 'white',
		'figure': 'Pawn',
		'position': 'e2',
		'code': '#9817'
	},
	{
		'square_color' : 'black',
		'color': 'white',
		'figure': 'Pawn',
		'position': 'f2',
		'code': '#9817'
	},
	{
		'square_color' : 'white',
		'color': 'white',
		'figure': 'Pawn',
		'position': 'g2',
		'code': '#9817'
	},
	{
		'square_color' : 'black',
		'color': 'white',
		'figure': 'Pawn',
		'position': 'h2',
		'code': '#9817'
	},
	{
		'square_color' : 'black',
		'color': 'white',
		'figure': 'Rook',
		'position': 'a1',
		'code': '#9814'
	},
	{
		'square_color' : 'white',
		'color': 'white',
		'figure': 'Knight',
		'position': 'b1',
		'code': '#9816'
	},
	{
		'square_color' : 'black',
		'color': 'white',
		'figure': 'Bishop',
		'position': 'c1',
		'code': '#9815'
	},
	{
		'square_color' : 'white',
		'color': 'white',
		'figure': 'Queen',
		'position': 'd1',
		'code': '#9813'
	},
	{
		'square_color' : 'black',
		'color': 'white',
		'figure': 'King',
		'position': 'e1',
		'code': '#9812'
	},
	{
		'square_color' : 'white',
		'color': 'white',
		'figure': 'Bishop',
		'position': 'f1',
		'code': '#9815'
	},
	{
		'square_color' : 'black',
		'color': 'white',
		'figure': 'Knight',
		'position': 'g1',
		'code': '#9816'
	},
	{
		'square_color' : 'white',
		'color': 'white',
		'figure': 'Rook',
		'position': 'h1',
		'code': '#9814'
	},
]

def udpdate_data():
	# update board
	# TODO

	return

def send_data(move):
	# send data to cpp socket
	argc = len(sys.argv)
	HOST = '0::1'    # The remote host
	PORT = 8001              # The same port as used by the server
	try:
		s = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
		s.connect((HOST, PORT))
		if move != None:
			move = move.encode()
		else:
			return False
		s.send(move)
		data = s.recv(1024)			# Return data from server
		print('Received from server:', data)
		server_resp = str(data, 'utf-8')
		print ("recived", server_resp)
		if server_resp == 'true':
			# upadate_data()
			print ('Update board')
		elif server_resp == 'false':
			print ('Do not update board')
		s.close()

	except socket.error as e:
	    print ("Socket error({0}): {1}".format(e.errno, e.strerror))
	except:
	    print ("Unexpected error:", sys.exc_info()[0])
	    raise
	return

@app.route("/", methods = ['GET', 'POST'])
def function():
	if request.method == 'POST':
		move = request.form.get('move')
		print ("move:" , move)
		if move != "":
			if send_data(move) == False:
				print ('Could not send string')
		return render_template("index.html", board = board, len = len(board))
	else:
		return render_template("index.html", board = board, len = len(board))


if __name__ == "__main__":
	app.run()
