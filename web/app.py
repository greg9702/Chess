#!/usr/bin/python3

from flask import Flask, render_template, request
import socket
import sys
import json
import hashlib
from argparse import ArgumentParser

app = Flask(__name__)

# store all squares on board
board = []

# boolean flag to indicate if first move was performed
start_game = True
# keep value what player color has move
turn = 'white'
# message displayed to players
message = "White turn!"


def updateMessage(staus):
    '''
    Update displayed message to players, based on server response
    @param status: array contaning 3 values
    @return: true if message was set sucessfully, false otherwise
    '''

    status = staus.split(';')
    # print ("STATUS", status)
    global turn
    global message
    message = ''

    if status[2] == '1':
        message += 'Black turn! '
        turn = 'black'
    elif status[2] == '0':
        message += 'White turn! '
        turn = 'white'

    if status[0] == '0':
        message += 'Wrong move! '
    elif status[0] == '1':
        # correct move
        message += ''

    if status[1] == '0':
        message += ''
    elif status[1] == '1':
        message += 'White in check! '
    elif status[1] == '2':
        message += 'White in checkmate! '
    elif status[1] == '3':
        message += 'Black in check! '
    elif status[1] == '4':
        message += 'Black in checkmate! '
    elif status[1] == '5':
        message = 'Stale mate '
    else:
        return False
    return True


def updateBoard(recived_data):
    '''
    Update board dictionary
    @param recived_data: dictionary contaning values for each square on board
    @return: true if board was updated sucessfully
    '''

    global board
    status = recived_data[0:5]
    board_data = recived_data[6:]

    global start_game
    if start_game == True:
        start_game = False
    else:
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
            'square_color': square_col,
            'color': figure_col,
            'figure': figure,
            'position': position,
            'code': code
        })

    # for el in board:
    # 	print (el)
    return True


def sendData(move):
    '''
    Send move to the server, and wait for response containing info about game status
    and pieces position, create short TCP session with server
    @param move: string 4 chars long
    @return: True if move was send sucessfully and got server response, False otherwise
    '''

    HOST = '0::1'  # The remote host
    # PORT = 8001  # The port as used by the server
    PORT = int(app.config['server_port'])
    print("server port: " + str(PORT))
    try:
        s = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
        s.connect((HOST, PORT))

        if move != None:
            move = move.encode()  # we need encode string to binary stream to send it
        else:
            return False  # if move is None, do not send it

        s.send(move)
        data = s.recv(2048)  # Return data from server in binary stream
        s.close()
        server_resp = str(data, 'utf-8')  # data from server in string form
        updateBoard(server_resp)

    except socket.error as e:
        print ("Socket error({0}): {1}".format(e.errno, e.strerror))
    except:
        print ("Unexpected error:", sys.exc_info()[0])
        raise
    return True


def printer():
    '''
    Print all board dictionary elements to console
    @return:
    '''

    for el in board:
        print (el)

    return


@app.route("/", methods=['GET', 'POST'])
def function():
    '''
    Flask function trigerred when got POST or GET request from application
    @return: json containing info to application about board and game status
    @return: render index.html when got GET request
    @return: False when passed move is empty string
    '''
    global player_color
    # if request.host == '127.0.0.1:5000':
    #     player_color = 'white'
    # else:
    #     player_color = 'black'
    player_color = app.config['player_color']
    global start_game
    if start_game == True:
        print ('Start game')
        move = 'XD'  # send wrong move to synchronize board
        sendData(move)
    if request.method == 'POST':  # we got POST request when move has been performed
        move = request.form.get('move')
        # print ("move:" , move)
        # print ('type move before function', type(move))
        if move != '':
            if sendData(move) == False:
                print ('Could not send string')
        else:
            return False

        render = render_template("board.html", board=board,
                                 len=len(board))  # after we got board updated, render new board template
        m = hashlib.sha256()  # hash value of board
        m.update(render.encode())
        ren_j = {'content': render, 'hash': m.hexdigest(), 'message': message, 'turn': turn,
                 'player_color': player_color}
        return json.dumps(ren_j)  # return json to application
    else:
        return render_template("index.html", player_color=player_color)


if __name__ == '__main__':
    parser = ArgumentParser()
    parser.add_argument('-s')
    parser.add_argument('-p')
    parser.add_argument('-c')
    args = parser.parse_args()
    port = args.p
    player_color = args.c
    server_port = args.s
    app.config['server_port'] = server_port
    app.config['player_color'] = player_color
    print('xd')
    app.run(port = port)
