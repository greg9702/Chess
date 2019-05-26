let move = ""

function pickSquare(elmnt) {
	console.log(elmnt.id);
	move = move + elmnt.id;
	// console.log(game_over);
	if (move.length == 4) {
		sendMove(move, elmnt);
	}
}

function sendMove(move_, elmnt) {
	// console.log(move_);
	move = "";
	console.log(move);
	document.body.innerHTML += '<form id="send_move" action="" method="post"><input type="hidden" name="move" value="' + move_ + '"></form>';
	// let a = prompt("Promote to: ","Q");
	// console.log(a);
	document.getElementById("send_move").submit();
}
