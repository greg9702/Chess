let move = "";

setInterval(function(){ sendFake('b4') }, 3000);

function sendFake(move_) {
	document.body.innerHTML += '<form id="send_fake" action="" method="post"><input type="hidden" name="move" value="' + move_ + '"></form>';
	document.getElementById("send_fake").submit();
}


function highlightSquare(move) {
	square = document.getElementById(move);
	console.log(square);
	square.style.backgroundColor = '#47d147';
}

function pickSquare(elmnt) {
	console.log(elmnt.getAttribute('id'));
	let turn = document.getElementById("turn").getAttribute('turn');
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
		document.body.innerHTML += '<form id="send_move" action="" method="post"><input type="hidden" name="move" value="' + move_ + a + '"></form>';
	} else if (element.getAttribute('figure') == 'Pawn' && element.getAttribute('figure_col') == 'black'&& figure_row == '2') {
		// ask for details about new figure type
		let a = prompt("Promote to: ","Q");
		document.body.innerHTML += '<form id="send_move" action="" method="post"><input type="hidden" name="move" value="' + move_ + a +'"></form>';
	} else {
		document.body.innerHTML += '<form id="send_move" action="" method="post"><input type="hidden" name="move" value="' + move_ + '"></form>';
	}
	console.log(document.getElementById("send_move"));
	document.getElementById("send_move").submit();
}
