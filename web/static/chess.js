let move = ""

function pickSquare(elmnt) {
	console.log(elmnt.id);
	move = move + elmnt.id;
	if (move.length == 4) {
		sendMove(move);
	}
}

function sendMove(move_) {
	// console.log(move_);
	move = "";
	console.log(move);
	document.body.innerHTML += '<form id="send_move" action="" method="post"><input type="hidden" name="move" value="' + move_ + '"></form>';
	document.getElementById("send_move").submit();
}
