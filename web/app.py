from flask import Flask, render_template, request
import socket
import sys

app = Flask(__name__)

board = []
# store all squares on board
message = "White turn!"
# wrong_move = False

# def setMesssage(info):
# 	# set message to display
# 	print ('info', info)
# 	global message
# 	global game_over
# 	message = ""
# 	if info[1] == '1':
# 		message += "Black turn! "
# 	elif info[1] == '0':
# 		message += "White turn! "
# 	elif info[1] == '2':
# 		game_over = True
#
# 	if info[0] == '0':
# 		message += ""
# 	elif info[0] == '1':
# 		message += "White in check! "
# 	elif info[0] == '2':
# 		message = "White in checkmate! "
# 	elif info[0] == '3':
# 		message += "Black in check! "
# 	elif info[0] == '4':
# 		message = "Black in checkmate! "
# 	elif info[0] == '5':
# 		message += "Statement "
#
# 	global wrong_move
# 	if wrong_move:
# 		message += "Wrong move! "
# 		wrong_move = False
#
# 	return
#
# def moveFigure(move, new_type):
# 	if new_type == None:
# 		move = str(move, 'utf-8')
# 		print ('who move', move[0:2])
# 		print ('type move inside', type(move))
# 		print ('move at 0', move[0])
# 		figure = ""
# 		code = ""
# 		color = ""
# 		for el in board:
# 			if el['position'] == move[0:2]:
# 				figure = el['figure']
# 				code = el['code']
# 				color = el['color']
# 				print ('XDDD', figure, code, color)
# 				el['figure'] = 'None'
# 				el['code'] = 'None'
# 				el['color'] = 'None'
# 				break
#
# 		for el in board:
# 			if el['position'] == move[2:4]:
# 				el['figure'] = figure
# 				el['code'] = code
# 				el['color'] = color
#
# 		return True
#
# 	elif new_type != None:
# 			move = str(move, 'utf-8')
# 			print ('who move', move[0:2])
# 			print ('type move inside', type(move))
# 			print ('move at 0', move[0])
# 			color = ""
# 			for el in board:
# 				if el['position'] == move[0:2]:
# 					color = el['color']
# 					el['figure'] = 'None'
# 					el['code'] = 'None'
# 					el['color'] = 'None'
# 					break
#
# 			# change type of new element
# 			print ('new TYPE:', new_type)
# 			for el in board:
# 				if el['position'] == move[2:4]:
# 					el['color'] = color
# 					if new_type == 'Q':
# 						el['figure'] = 'Queen'
# 						if color == 'whte':
# 							el['code'] = '#9813'
# 						elif color == 'black':
# 							el['code'] = '#9819'
# 					elif new_type == 'N':
# 						el['figure'] = 'Knight'
# 						if color == 'whte':
# 							el['code'] = '#9816'
# 						elif color == 'black':
# 							el['code'] = '#9822'
# 					elif new_type == 'B':
# 						el['figure'] = 'Bishop'
# 						if color == 'whte':
# 							el['code'] = '#9815'
# 						elif color == 'black':
# 							el['code'] = '#9821'
# 					elif new_type == 'R':
# 						el['figure'] = 'Rook'
# 						if color == 'whte':
# 							el['code'] = '#9814'
# 						elif color == 'black':
# 							el['code'] = '#9820'
# 					else:
# 						raise "Error in promoting Pawn"
# 			return True
# 	return False
#
# def moveFigure(move, new_type):
#
# def updateData(move, server_resp):
# 	# update board
# 	# @param 4 long string
#
# 	global message
# 	global wrong_move
#
# 	if len(server_resp) != 4:
# 		raise ValueError("Invalid size of passed string")
#
# 	if server_resp[0] == '0': # wrong move
# 		wrong_move = True;
# 		setMesssage(server_resp[2:4])
# 		return False
#
# 	if server_resp[0] == '1': # correct move
# 		setMesssage(server_resp[2:4])
# 		if server_resp[1] == '0':
# 			if len(move) == 4:
# 				moveFigure(move, None)		#normal move, no castling
# 				return True
# 			elif len(move) == 5:		#move with promotion
# 				moveFigure(move[0:4], move[4])
#
# 		elif server_resp[1] == '1': # white short castling
# 			figure = "" 	# old position
# 			code = ""
# 			color = ""
# 			for el in board:  # move king
# 				if el['position'] == 'e1':   	# TODO move this to seperate function
# 					figure = el['figure']
# 					code = el['code']
# 					color = el['color']
# 					el['figure'] = 'None'
# 					el['code'] = 'None'
# 					el['color'] = 'None'
# 					break
# 			for el in board:
# 				if el['position'] == 'g1':
# 					el['figure'] = figure
# 					el['code'] = code
# 					el['color'] = color
# 					break
#
# 			for el in board:  # move rook
# 				if el['position'] == 'h1':
# 					figure = el['figure']
# 					code = el['code']
# 					color = el['color']
# 					el['figure'] = 'None'
# 					el['code'] = 'None'
# 					el['color'] = 'None'
# 					break
# 			for el in board:
# 				if el['position'] == 'f1':
# 					el['figure'] = figure
# 					el['code'] = code
# 					el['color'] = color
# 					break
# 			return True
#
# 		elif server_resp[1] == '2':	#white long castling
# 			figure = "" 	# old position
# 			code = ""
# 			color = ""
# 			for el in board:  # move king
# 				if el['position'] == 'e1':
# 					figure = el['figure']
# 					code = el['code']
# 					color = el['color']
# 					el['figure'] = 'None'
# 					el['code'] = 'None'
# 					el['color'] = 'None'
# 					break
# 			for el in board:
# 				if el['position'] == 'c1':
# 					el['figure'] = figure
# 					el['code'] = code
# 					el['color'] = color
# 					break
#
# 			for el in board:  # move rook
# 				if el['position'] == 'a1':
# 					figure = el['figure']
# 					code = el['code']
# 					color = el['color']
# 					el['figure'] = 'None'
# 					el['code'] = 'None'
# 					el['color'] = 'None'
# 					break
# 			for el in board:
# 				if el['position'] == 'd1':
# 					el['figure'] = figure
# 					el['code'] = code
# 					el['color'] = color
# 					break
# 			return True
#
# 		elif server_resp[1] == '3':  # black short castling
# 			figure = "" 	# old position
# 			code = ""
# 			color = ""
# 			for el in board:  # move king
# 				if el['position'] == 'e8':
# 					figure = el['figure']
# 					code = el['code']
# 					color = el['color']
# 					el['figure'] = 'None'
# 					el['code'] = 'None'
# 					el['color'] = 'None'
# 					break
# 			for el in board:
# 				if el['position'] == 'g8':
# 					el['figure'] = figure
# 					el['code'] = code
# 					el['color'] = color
# 					break
#
# 			for el in board:  # move rook
# 				if el['position'] == 'h8':
# 					figure = el['figure']
# 					code = el['code']
# 					color = el['color']
# 					el['figure'] = 'None'
# 					el['code'] = 'None'
# 					el['color'] = 'None'
# 					break
# 			for el in board:
# 				if el['position'] == 'f8':
# 					el['figure'] = figure
# 					el['code'] = code
# 					el['color'] = color
# 					break
# 			return True
#
# 		elif server_resp[1] == '4':	# long black castling
# 			figure = "" 	# old position
# 			code = ""
# 			color = ""
# 			for el in board:  # move king
# 				if el['position'] == 'e8':
# 					el['figure'] = figure
# 					el['code'] = code
# 					el['color'] = color
# 					el['figure'] = 'None'
# 					el['code'] = 'None'
# 					el['color'] = 'None'
# 					break
# 			for el in board:
# 				if el['position'] == 'c8':
# 					el['figure'] = figure
# 					el['code'] = code
# 					el['color'] = color
# 					break
#
# 			for el in board:  # move rook
# 				if el['position'] == 'a8':
# 					el['figure'] = figure
# 					el['code'] = code
# 					el['color'] = color
# 					el['figure'] = 'None'
# 					el['code'] = 'None'
# 					el['color'] = 'None'
# 					break
# 			for el in board:
# 				if el['position'] == 'd8':
# 					el['figure'] = figure
# 					el['code'] = code
# 					el['color'] = color
# 					break
# 			return True
#
# 	else:
# 		raise ValueError("Illegal value at position 0")
#
#
# 	return False
#
def updateMessage(staus):
	return False;


def updateBoard(recived_data):
	global board
	status = recived_data[0:6]
	board_data = recived_data[6:]
	updateMessage(status)

	# update board
	board = []
	square = board_data.split(';')
	for el in square:
		field = el.split(',')
		square_col = field[0]
		figure_col = field[1]
		figure = field[2]
		position = field[3]
		code = field[4]

		if figure_col == '':
			figure_col = 'None'
			figure = 'None'
			code = 'None'

		board.append({
			'square_col' : square_col,
			'color' : color,
			'figure' : figure,
			'position' : position,
			'code' : code
		})

	return True



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
		# print('Received from server:', data)
		server_resp = str(data, 'utf-8')
		print ("recived", server_resp) # in string form
		# updateData(move, server_resp)
		updateBoard(server_resp)
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
