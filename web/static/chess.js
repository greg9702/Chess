let move = ''; // keep move string eg. e3e4
let last_hash; // keep hash of previous board
let turn;      // keep turn
// let player_color;     // keep color (one for each client)
let premove_flag = false;

// delay
const sleep = (milliseconds) => {
    return new Promise(resolve => setTimeout(resolve, milliseconds))
}

setInterval(function () {
    sendFake('XD')
}, 1000);

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
        function () { // Call a function when the state changes.
            if (http.readyState === 4 && http.status === 200) {
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
    if (highlighted_figure.classList.contains('white')) {
        square.style.backgroundColor = '#eaeeae';
    } else if (highlighted_figure.classList.contains('black')) {
        square.style.backgroundColor = '#996335';
    }
}

function pickSquare(elmnt) {
    /**
     * Selected square by player is added to move string
     * @param elemnt div containing square info
     */

    if (move.length === 2) { // if move lenght is 2, player has to choose one more square
        move = move + elmnt.getAttribute('id');
    }
    if (move.length === 0 &&
        elmnt.getAttribute('figure_col') === player_color) { // check if piece is picked correct for color that user is playing
        move = move + elmnt.getAttribute('id');
        highlightSquare(move);
    }
    if (move.length === 4) {
        if (!premove_flag) {
            sendMove(move);
        }
    }
}

function sendMove(move_) {
    /**
     * Send move as HTTP request to Flask app
     * @param move_ string lenght 4, containing complete move
     */

    undoHighlightSquare(move_.substring(0, 2));
    let figure_position = move_.substring(0, 2);
    let element = document.getElementById(figure_position);
    let figure_row = figure_position.substring(1, 2);
    // premove
    if (element.getAttribute('figure_col') === player_color && element.getAttribute('figure_col') !==
        turn) {
        premove_flag = true;
        highlightSquare(move_.substring(0, 2));
        highlightSquare(move_.substring(2, 4));
        console.log(move_);
        // try to do premove
        sleep(500).then(() => {
            sendMove(move_);
        });
        return
    }
    // normal move (not premove)
    move = '';
    premove_flag = false;
    if (element.getAttribute('figure') === 'Pawn' &&
        element.getAttribute('figure_col') === 'white' && figure_row === '7') {
        // if Pawn has to be promoted
        // ask for details about new figure type
        let a = prompt("Promote to: ", "Q");
        move_ = move_ + a;
    } else if (element.getAttribute('figure') === 'Pawn' &&
        element.getAttribute('figure_col') === 'black' &&
        figure_row === '2') {
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
        function () { // Call a function when the state changes.
            if (http.readyState === 4 && http.status === 200) {
                parseNewBoard(http.responseText);
            }
        };
    http.send(params);
}

function parseNewBoard(json_str) {
    /**
     * Parse recived json from flask app, get board and status data from it
     * @param json_str json recived from flask app
     */

    data = JSON.parse(json_str);
    if (data.hash !== last_hash) { // check if hash of recived board if different
        // from the previous one
        // if it is, replace the content of page, because board has changed
        board = document.getElementById('board')
        board.innerHTML = data.content;
        last_hash = data.hash;
        turn = data.turn;
        player_color = data.player_color;
        mess = document.getElementById('message');
        mess.innerHTML = data.message;

        if (player_color === 'black') {
            flipBoard();
        }
    }
}

flipBoard = () => {
    let chess_board_table = document.getElementsByClassName('chess-board')[0];
    flipWholeBoard(chess_board_table);
    flipFiguresAndLineNrsOnBoard(chess_board_table);
};

function flipWholeBoard(chess_board_tbody) {
    addNewClass(chess_board_tbody, 'black-rotation');
}

flipFiguresAndLineNrsOnBoard = (chess_board_table) => {
    let chess_board_rows = chess_board_table.children[0].children;
    for (let i = 0; i < chess_board_rows.length; i++) {
        let chess_board_elems = chess_board_rows[i].children;
        for (let j = 0; j < chess_board_elems.length; j++) {
            console.log(chess_board_elems[j]);
            addNewClass(chess_board_elems[j], 'black-rotation');
        }
    }
};

addNewClass = (elem, newClassName) => {
    let classString = elem.className;
    elem.className = classString.concat(' ' + newClassName);
};