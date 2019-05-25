from flask import Flask, render_template, request
import socket
import sys




app = Flask(__name__)

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
		if server_resp == "true":
			print ('Update board')
		elif server_resp == "false":
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
		if send_data(move) == False:
			print ('Could not send string')
		# upadate board()
		# return render_template("board, index.html")
		return render_template("index.html")
	else:
		return render_template("index.html")


if __name__ == "__main__":
	app.run(use_reloader = True)
