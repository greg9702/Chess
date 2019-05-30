let move = "";
let last_hash;
let turn;

setInterval(function(){ sendFake('b4c') }, 1000);

function sendFake(move_) {
	var http = new XMLHttpRequest();
	var url = '';
	var params = 'move=' + move_;
	console.log('params', params);
	http.open('POST', url, true);

	http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
	http.onreadystatechange = function() {//Call a function when the state changes.
		if(http.readyState == 4 && http.status == 200) {
			parseNewBoard(http.responseText);
		}
	}
	http.send(params);
}

function highlightSquare(move) {
	square = document.getElementById(move);
	console.log(square);
	square.style.backgroundColor = '#47d147';
}

function pickSquare(elmnt) {
	console.log(elmnt.getAttribute('id'));
	console.log('turn', turn);
	if (move.length == 2) {
	move = move + elmnt.getAttribute('id');
	}
	if (move.length == 0 && elmnt.getAttribute('figure_col') == turn) {
		move = move + elmnt.getAttribute('id');
		highlightSquare(move);
	}
	if (move.length == 4) {
		sendMove(move);
	}
}

function sendMove(move_) {
	move = "";
	let figure_position = move_.substring(0, 2);
	let element = document.getElementById(figure_position);
	let figure_row = figure_position.substring(1,2);
	console.log(element)
	if (element.getAttribute('figure') == 'Pawn' && element.getAttribute('figure_col') == 'white' && figure_row == '7') {
		// ask for details about new figure type
		let a = prompt("Promote to: ","Q");
		move_ = move_ + a;
	} else if (element.getAttribute('figure') == 'Pawn' && element.getAttribute('figure_col') == 'black'&& figure_row == '2') {
		// ask for details about new figure type
		let a = prompt("Promote to: ","Q");
		move_ = move_ + a;
	}

	var http = new XMLHttpRequest();
	var url = '';
	var params = 'move=' + move_;
	console.log('params', params);
	http.open('POST', url, true);


	http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
	http.onreadystatechange = function() {//Call a function when the state changes.
		if(http.readyState == 4 && http.status == 200) {
			parseNewBoard(http.responseText);
		}
	}
	http.send(params);

}

function parseNewBoard(json_str) {
			data = JSON.parse(json_str);
			if (data.hash != last_hash) {
				board = document.getElementById("board")
				board.innerHTML = data.content;
				last_hash = data.hash;
				turn = data.turn;
				mess = document.getElementById('message');
				mess.innerHTML = data.message;
			}

}
