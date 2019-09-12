# __Multiplayer Chess__

Chess multiplayer game built using C++ and Python. <br>
Provided full logic and functionallity of chess. <br>

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

Build project by running command <br>
```
./build.sh
```
Then run server  
```
cd build
./server
```
Server run as system daemon on a well known address. <br>
To start a client run in _build_ directory command
```
./client
```
Client connect to server, than its registered by the server. <br>
Server assign new port for the client and then respond to the client with <br>
an address on which will host an application for client. <br>

![Alt Text](/other/respondexample.png) <br>

When server register two new clients, starts two _Flask_ applications, <br>
and clients can start using them by opening web browser.



### __How to play?__
Just click a figure and select where to move it!


### __Tasks TODO__

#### Long term tasks
- [Crazyhouse mode](https://en.wikipedia.org/wiki/Crazyhouse)
