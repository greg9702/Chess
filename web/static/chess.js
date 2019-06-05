let move = ''; // keep move string eg. e3e4
let last_hash; // keep hash of previous board
let turn;      // keep turn

setInterval(function() { sendFake('XD') }, 1000);

function sendFake(move_) {
  /**
   * Polling method, send fake move to server, it response with board data
   * @param move_ string containing move
   */

  var http = new XMLHttpRequest();
  var url = '';
  var params = 'move=' + move_;
  // console.log('params', params);
  http.open('POST', url, true);

  http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
  http.onreadystatechange =
      function() { // Call a function when the state changes.
    if (http.readyState == 4 && http.status == 200) {
      parseNewBoard(http.responseText);
    }
  } 
  http.send(params);
}

function highlightSquare(move_) {
  /**
   * Highlight square which is occuped by piece and was selected by player
   * @param move_ string containing move
   */

  square = document.getElementById(move_);
  square.style.backgroundColor = '#47d147';
}

function undoHighlightSquare(position) {
  /**
   * Undo highlight of square which was previously selected
   * @param position string containing move
   */

  let highlighted_figure = document.getElementById(position);
  if (highlighted_figure.getAttribute('class') == 'white') {
    square.style.backgroundColor = '#eee';
  } else if (highlighted_figure.getAttribute('class') == 'black') {
    square.style.backgroundColor = '#a40f08';
  }
}

function pickSquare(elmnt) {
  /**
   * Selected square by player is added to move string
   * @param elemnt div containing square info
   */

  if (move.length ==
      2) { // if move lenght is 2, player has to choose one more square
    move = move + elmnt.getAttribute('id');
  }
  if (move.length == 0 &&
      elmnt.getAttribute('figure_col') ==
          turn) { // check if piece is picked correct for turn
    move = move + elmnt.getAttribute('id');
    highlightSquare(move);
  }
  if (move.length == 4) {
    sendMove(move);
  }
}

function sendMove(move_) {
  /**
   * Send move as HTTP request to Flask app
   * @param move_ string lenght 4, containing complete move
   */

  move = '';
  undoHighlightSquare(move_.substring(0, 2));
  let figure_position = move_.substring(0, 2);
  let element = document.getElementById(figure_position);
  let figure_row = figure_position.substring(1, 2);

  if (element.getAttribute('figure') == 'Pawn' &&
      element.getAttribute('figure_col') == 'white' && figure_row == '7') {
    // if Pawn has to be promoted
    // ask for details about new figure type
    let a = prompt("Promote to: ", "Q");
    move_ = move_ + a;
  } else if (element.getAttribute('figure') == 'Pawn' &&
             element.getAttribute('figure_col') == 'black' &&
             figure_row == '2') {
    // if Pawn has to be promoted
    // ask for details about new figure type
    let a = prompt("Promote to: ", "Q");
    move_ = move_ + a;
  }

  var http = new XMLHttpRequest();
  var url = '';
  var params = 'move=' + move_;
  http.open('POST', url, true);

  http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
  http.onreadystatechange =
      function() { // Call a function when the state changes.
    if (http.readyState == 4 && http.status == 200) {
      parseNewBoard(http.responseText);
    }
  } 
  http.send(params);
}

function parseNewBoard(json_str) {
  /**
   * Parse recived json from flask app, get board and status data from it
   * @param json_str json recived from flask app
   */

  data = JSON.parse(json_str);
  if (data.hash != last_hash) { // check if hash of recived board if different
                                // from the previous one
    // if it is, replace the content of page, because board has changed
    board = document.getElementById('board')
    board.innerHTML = data.content;
    last_hash = data.hash;
    turn = data.turn;
    mess = document.getElementById('message');
    mess.innerHTML = data.message;
  }
}
