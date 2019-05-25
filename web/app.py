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
message = "White turn!"

def setMesssage(info):
	# set message to display
	print ('info', info)
	global message
	message = ""
	if info[1] == '1':
		message += "Black turn!"
	elif info[0] == '0':
		message += "White turn!"

	return

def moveFigure(move):
	move = str(move, 'utf-8')
	print ('who move', move[0:2])
	print ('type move inside', type(move))
	print ('move at 0', move[0])
	for el in board:
		figure = ""
		code = ""
		color = ""
		if el['position'] == move[0:2]:
			figure = el['figure']
			code = el['code']
			color = el['color']
			print ('XDDD', figure, code, color)
			el['figure'] = 'None'
			el['code'] = 'None'
			el['color'] = 'None'
			break

	for el in board:
		if el['position'] == move[2:4]:
			el['figure'] = figure
			el['code'] = code
			el['color'] = color

	return

def updateData(move, server_resp):
	# update board
	# @param 4 long string

	global message
	if len(server_resp) != 4:
		raise "Invalid size of passed string"

	if server_resp[0] == '0': # wrong move
		message += " Wrong move!"
		return False

	if server_resp[0] == '1': # correct move
		setMesssage(server_resp[2:4])
		if server_resp[1] == '0':
			moveFigure(move)		#normal move, no castling
			return True

		elif server_resp[1] == '1': # white short castling
			figure = "" 	# old position
			code = ""
			color = ""
			for el in board:  # move king
				if el['position'] == 'e1':
					figure = el['figure']
					code = el['code']
					color = el['color']
					el['figure'] = 'None'
					el['code'] = 'None'
					el['color'] = 'None'
					break
			for el in board:
				if el['position'] == 'g1':
					el['figure'] = figure
					el['code'] = code
					el['color'] = color
					break

			for el in board:  # move rook
				if el['position'] == 'h1':
					figure = el['figure']
					code = el['code']
					color = el['color']
					el['figure'] = 'None'
					el['code'] = 'None'
					el['color'] = 'None'
					break
			for el in board:
				if el['position'] == 'f1':
					el['figure'] = figure
					el['code'] = code
					el['color'] = color
					break
			return True

		elif server_resp[1] == '2':	#white long castling
			figure = "" 	# old position
			code = ""
			color = ""
			for el in board:  # move king
				if el['position'] == 'e1':
					figure = el['figure']
					code = el['code']
					color = el['color']
					el['figure'] = 'None'
					el['code'] = 'None'
					el['color'] = 'None'
					break
			for el in board:
				if el['position'] == 'c1':
					el['figure'] = figure
					el['code'] = code
					el['color'] = color
					break

			for el in board:  # move rook
				if el['position'] == 'a1':
					figure = el['figure']
					code = el['code']
					color = el['color']
					el['figure'] = 'None'
					el['code'] = 'None'
					el['color'] = 'None'
					break
			for el in board:
				if el['position'] == 'd1':
					el['figure'] = figure
					el['code'] = code
					el['color'] = color
					break
			return True

		elif server_resp[1] == '3':  # black short castling
			figure = "" 	# old position
			code = ""
			color = ""
			for el in board:  # move king
				if el['position'] == 'e1':
					figure = el['figure']
					code = el['code']
					color = el['color']
					el['figure'] = 'None'
					el['code'] = 'None'
					el['color'] = 'None'
					break
			for el in board:
				if el['position'] == 'g1':
					el['figure'] = figure
					el['code'] = code
					el['color'] = color
					break

			for el in board:  # move rook
				if el['position'] == 'h8':
					figure = el['figure']
					code = el['code']
					color = el['color']
					el['figure'] = 'None'
					el['code'] = 'None'
					el['color'] = 'None'
					break
			for el in board:
				if el['position'] == 'f8':
					el['figure'] = figure
					el['code'] = code
					el['color'] = color
					break
			return True

		elif server_resp[1] == '4':	# long black castling
			figure = "" 	# old position
			code = ""
			color = ""
			for el in board:  # move king
				if el['position'] == 'e1':
					el['figure'] = figure
					el['code'] = code
					el['color'] = color
					el['figure'] = 'None'
					el['code'] = 'None'
					el['color'] = 'None'
					break
			for el in board:
				if el['position'] == 'c8':
					el['figure'] = figure
					el['code'] = code
					el['color'] = color
					break

			for el in board:  # move rook
				if el['position'] == 'a8':
					el['figure'] = figure
					el['code'] = code
					el['color'] = color
					el['figure'] = 'None'
					el['code'] = 'None'
					el['color'] = 'None'
					break
			for el in board:
				if el['position'] == 'd8':
					el['figure'] = figure
					el['code'] = code
					el['color'] = color
					break
			return True

	else:
		raise "Illegal value at position 0"


	return False

def sendData(move):
	# send data to cpp socket
	HOST = '0::1'    # The remote host
	PORT = 8001      # The same port as used by the server
	try:
		s = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
		s.connect((HOST, PORT))
		if move != None:
			move = move.encode()
		else:
			return False
		s.send(move)
		data = s.recv(1024)			# Return data from server in binary stream
		print('Received from server:', data)
		server_resp = str(data, 'utf-8')
		print ("recived", server_resp) # in string form
		updateData(move, server_resp)
		s.close()

	except socket.error as e:
	    print ("Socket error({0}): {1}".format(e.errno, e.strerror))
	except:
	    print ("Unexpected error:", sys.exc_info()[0])
	    raise
	return

def printer():
	for el in board:
		print (el)

@app.route("/", methods = ['GET', 'POST'])
def function():
	if request.method == 'POST':
		move = request.form.get('move')
		print ("move:" , move)
		print ('type move before function', type(move))
		if move != "":
			if sendData(move) == False:
				print ('Could not send string')
		# printer()
		return render_template("index.html", board = board, len = len(board), message = message)
	else:
		return render_template("index.html", board = board, len = len(board), message = message)


if __name__ == "__main__":
	app.run()
