# __Multiplayer Chess__

Chess multiplayer game built using C++ and Python. <br>
It provides full logic and functionality of chess. <br>

### __Features:__
- [Castlings](https://en.wikipedia.org/wiki/Castling)
- [En passant](https://en.wikipedia.org/wiki/En_passant)
- [Pawn promotions](https://en.wikipedia.org/wiki/Promotion_(chess))
- [Premoves](https://en.wikipedia.org/wiki/Premove)
- Many pairs of players can play with each other at the same time.
- Server using _syslog_ for logging.

### Demo: <br>

![Alt Text](/other/demo/Chess_demo.gif)

### __Requirements:__
- CMake
- g++
- Python3
- pip
- virtualenv

### How to run and how it works?

Build project by running command: <br>
```
./build.sh
```
Then run server:
```
cd build
./server
```
Now server runs as system daemon on _127.0.0.1:4444_. <br>
To start a client run following command in _build_ directory:
```
./client
```
Client connects to server, than it's registered by the server. <br>
Server assigns new port for the client and then sends back <br>
an address and port on which application will be hosted. <br>

![Alt Text](/other/respondexample.png) <br>

When server registers two new clients, it starts two _Flask_ applications, <br>
and clients can start using them after opening web browser.



### __How to play?__
Just click a figure and select where to move it!


### __Tasks TODO__

#### Long term tasks
- [Crazyhouse mode](https://en.wikipedia.org/wiki/Crazyhouse)
