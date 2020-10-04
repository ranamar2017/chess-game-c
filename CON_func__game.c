#include "CON_func__game.h"





#define new_max(x,y) ((x) >= (y)) ? (x) : (y) // check for max between two values x and y.
#define new_min(x,y) ((x) <= (y)) ? (x) : (y) // check for min between two values x and y.




/**
 * Creates a new chess game with a specified game information size.
 * @historySize - The total number of moves to undo, a player can undo at most historySizeMoves turns.
 * @player_color - the color of the player: white = 1 or black = 0.
 * @playerAmount: decide the numbers of players at the game: 1 or 2.
 * @diffLevel: decide the difficulty level of the game: 1-4.
 * @currentPlayerColor: the color of the current turn player.
 * @return
 * NULL if either a memory allocation failure occurs or historySize <= 0.
 * Otherwise, a new game instant is returned.
 */
ChessGame* initChessGame(int playerAmount, int history_size, int diffLevel, int playerColor, int currentPlayerColor){
	ChessGame *game;
	game = (ChessGame*)malloc(sizeof(ChessGame));// allocated memory to the program.
	if (game == NULL){
		printf("Error: ChessGameCreate has failed\n"); 
		return NULL;
	}


	initValidChessBoard(&game->gameBoard[0][0]);
	game->playerAmount = playerAmount;
	game->history_size = history_size; //decide the historysize.
	game->history_queue = chArrayListCreate(history_size);
	if (game->history_queue == NULL){
		printf("Error: chArrayListCreate has failed\n");
		free(game);
		return NULL;
	}
	game->mode = Settings_Mode;
	game->diffLevel = diffLevel;
	game->currentPlayer = currentPlayerColor;
	game->user_color = playerColor;


	//we need to track both Kings at all time.
	game->white_King = game->gameBoard[0][4];
	game->black_King = game->gameBoard[7][4];

	return game;
}


/**
 * Creates a new chess game with the default game information.
 * default history size: 6.
 * the difficulty level is 2.
 * the default color is white: 1.
 * the default numbers of players is: 1.
 * @return
 * NULL if either a memory allocation failure occurs or historySize <= 0.
 * Otherwise, a new game instant is returned.
 */
ChessGame* initDefaultChessGame(){
	return initChessGame(1,6,2,1,1); ////////////////////////////// set first arg to 2 if you want user vs user
}


/**
 *	Creates a copy of a given game.
 *	The new copy has the same status as the src game.
 *
 *	@param src - the source game which will be copied
 *	@return
 *	NULL if either src is NULL or a memory allocation failure occurred.
 *	Otherwise, an new copy of the source game is returned.
 *
 */
ChessGame* chessGameCopy(ChessGame* src){

	if (src == NULL)return NULL;

	ChessGame *newGame = initChessGame(src->playerAmount, src->history_size, src->diffLevel, src->user_color, src->currentPlayer);
	if (newGame == NULL){printf("Error: chArrayListCreate has failed\n");return NULL;}

	if (chArrayListCopy(src->history_queue, newGame->history_queue)!=CH_ARRAY_LIST_SUCCESS){ free(newGame); return NULL;}

	chessBoardCopy(&src->gameBoard[0][0],&newGame->gameBoard[0][0]);
	newGame->mode = src->mode;

	//we need to track both Kings at all time.
	newGame->white_King = src->white_King;
	newGame->black_King = src->black_King;

	return newGame;
}


/**
 * Frees all memory allocation associated with a given game. If src==NULL
 * the function does nothing.
 *
 * @param src - the source game
 */
void chessGameDestroy(ChessGame* src){
	if(src != NULL){
		chArrayListDestroy(src->history_queue); // from the deep to the outside.
		free(src);
	}
}



/**
 * Sets the next move in a given game by change the two specific Boards cells by the tow Orders pairs.
 * the move is implement only if it legal by all the rules.in addition,
 *  this function update the positions of the king, the history, the board of the game, and change the turn to turn of another player.
 * @param src - The target game
 * @param source - ordered pair that the piece move from.
 * @param des - ordered pair that the piece move to.
 * @return
 * CH_CHESS_GAME_INVALID_ARGUMENT - if src is NULL or the another same color piece sit in the destination
 * CH_CHESS_GAME_INVALID_MOVE - if the move is invalid ( against the law of the game)
 * return CH_CHESS_GAME_SUCCESS - otherwise. it means that the operation finished in success.
 */
Chess_GAME_MESSAGE chessGameSetMove(ChessGame* src, OrderedPair source, OrderedPair des, bool print){

	if (src == NULL) return CH_CHESS_GAME_INVALID_ARGUMENT;
	// settings mode
	if (src->mode == 1)	return CH_CHESS_GAME_INVALID_ARGUMENT;

	BoardCell from = get_BoardCell(src, source); //the source
	BoardCell to = get_BoardCell(src, des); // the destination

	int checkForCheck = 1;

	//second check to ensure legality of the move
	if (!chessGameIsValidMove(src, from, to, print, checkForCheck)) return CH_CHESS_GAME_INVALID_MOVE;

	///update the position if the kings.
	if( from.piece == King || to.piece == King ) updateKingLocation(src,from, to);

	historyCell history = creatHistoryCell (from, to);

	update_Board_Cell(&(src->gameBoard[source.x][source.y]), &(src->gameBoard[des.x][des.y])); //update the board
	src->gameBoard[source.x][source.y]= makeBlank( source.x, source.y); // we earesed the piece that moved from his last place.


	if (chArrayListIsFull(src->history_queue)) {
		chArrayListRemoveLast(src->history_queue);
	}
	chArrayListAddFirst(src->history_queue, history );
	chessGameSwitchPlayer(src); ///change to the turn of the second player.

	return CH_CHESS_GAME_SUCCESS;
}


/*the function get the board, and two BoardCells: from and to that represent the move of one of the kings.
 * so the functions update the place if the king that move.
 * @param: ChessGame* src: an refernce to the board tha game play on.
 * 		   BoardCell from: the Board cell the king was before the move.
 * 		   BoardCell to: the Board cell the king move to.
 * the function update the place of the white_king if he move or update the place of the black king if
 * he move.
 *
 */
void restoreKingLocation(ChessGame* src, BoardCell from, BoardCell to){
	if(from.piece == King){
		if(from.color_cell == 1){
			src->white_King.x = from.x ;
			src->white_King.y = from.y ;
		}
		if(from.color_cell == 0){
			src->black_King.x = from.x ;
			src->black_King.y = from.y ;
		}
	}
	// usually in case of undo after checkmate
	if(to.piece == King){
		if(to.color_cell == 1)
			src->white_King = to;
		if(to.color_cell == 0)
			src->black_King = to;
	}
}

/*the function get the board, and two BoardCells: from and to that represent the move of one of the kings.
 * so the functions update the place the king move to.
 * @param: ChessGame* src: an refernce to the board tha game play on.
 * 		   BoardCell from: the Board cell the king was before the move.
 * 		   BoardCell to: the Board cell the king move to.
 * the function update the board location of whiteking or black king if
 * one moved.
 *
 */
void updateKingLocation(ChessGame* src, BoardCell from, BoardCell to){
	if(from.piece == King){
		if(from.color_cell == 1){
			src->white_King.x = to.x;
			src->white_King.y = to.y;
		}
		if(from.color_cell == 0){
			src->black_King.x = to.x;
			src->black_King.y = to.y;

		}
	}

}






/**
 * The traget of the function is to check some basics rules that in any move we have to check, such as:
 * Checks if a piece can be put in the specified ordered pair - place.
 * Check that the Board Cell that is the source isn't blank.
 * Check that the move isn't from one color to the same color.
 * It also check the player is play is in the right color.
 * Check if a move is valid the move is from borad cell "from"
 * to the destination Board cell: "to" acording to the specific boardPiece.
 *
 * @param src - The source game
 * @param from - The specified source Board Cell.
 * @param to - The specified destination Board Cell.
 * @return
 * true  - if the a piece can be put in the target destination BoardCell.
 * false - otherwise.
 */
bool chessGameIsValidMove( ChessGame* src, BoardCell from, BoardCell to, bool print , bool checkFor_Check){

	if(src == NULL) return 0;
	if( from.x <0 || from.x > 7 || to.x<0 || to.y >7 ) return 0;

	if(from.piece == Blank){ ///the source isn't blank.
		if(print) print_position_not_contain();
		return 0;
	}

	if ( (from.color_cell == to.color_cell)  && (to.piece != Blank)){ ///not from the same color.
		if(print) printIllegal();
		return 0;
	}



	if(src->currentPlayer != from.color_cell){// we know from.piece is not Blank. the right color play.
		if(print)print_position_not_contain();
		return 0;
	}

	if (from.piece == Pawn && !pawnValidMove(src, from,to) ){
		if(print)printIllegal();
		return 0;
	}

	if (from.piece == Bishop && !bishopValidMove(src, from, to) ){
		if(print)printIllegal();
		return 0;
	}

	if (from.piece == Rook && !rookValidMove(src,from, to) ){
		if(print)printIllegal();
		return 0;

	}
	if (from.piece == Knight && !knightValidMove(from, to) ){
		if(print)printIllegal();
		return 0;
	}

	if (from.piece == Queen && !queenValidMove(src, from, to)){
		if(print)printIllegal();
		return 0;
	}
	if (from.piece == King && !kingValidMove(from, to) ){
		if(print)printIllegal();
		return 0;
	}

	if(checkFor_Check){
		if( from.piece == King ) updateKingLocation(src,from, to);

		update_Board_Cell(&(src->gameBoard[from.x][from.y]), &(src->gameBoard[to.x][to.y])); //update the board
		src->gameBoard[from.x][from.y]= makeBlank( from.x, from.y); // we earesed the piece that moved from his last place.

		int illegal_we_Have_Check = check(src);

		update_Board_Cell( &from,  &(src->gameBoard[from.x][from.y]) ); //update the board
		update_Board_Cell( &to,  &(src->gameBoard[to.x][to.y]) ); //update the board

		if( from.piece == King || to.piece == King )restoreKingLocation(src,from, to);

		if(illegal_we_Have_Check){
			if(print)printIllegal();
			return 0;
		}
	}

	return 1;

}

/*
 * the command prints "Illegal move".
 * */
void printIllegal(){printf("Illegal move\n");}


/*
 * The traget of the function is to explore if the game achived a situation of check, tie or checkmate.
 * In case of checkmate or tie game ends. otherwise game continue.
 *
 * @param src - the source game
 *
 * @return true in case of checkmate or tie - end of the game cases.
 * else it return false.
 *
 */
int check_Checkmate_Check_Tie(ChessGame* game, int print){

	if( check(game) ){
		if( checkmate(game) ){
			if(print){print_Checkmate_Message(game->currentPlayer);}
			return 1;
		}
		if(print){print_Check_Message( game->playerAmount, game->user_color, game->currentPlayer);}
		return 0;
	}

	if( tie(game)){
		if(print){print_Tie_Message( game->playerAmount, game->user_color, game->currentPlayer);}
		return 2;
	}
	return 0;

}

// print relevant Tie message
void print_Tie_Message(int playerNum, int userColor, int curPlayer){
	if(playerNum == 1 && curPlayer == userColor){printf("The game ends in a tie\n");  return;}
	printf("The game is tied\n");
}

// print relevant Checkmate message
void print_Checkmate_Message(int curPlayer){
	if(curPlayer){
		printf("Checkmate! black player wins the game\n"); return;
	}
	printf("Checkmate! white player wins the game\n");
}

// print relevant Check message
void print_Check_Message( int playerNum, int userColor, int curPlayer){
	if(playerNum == 1 && curPlayer == userColor){ printf("Check!\n"); return;}
	if(curPlayer == 0) { printf("Check: black King is threatened!\n"); return;}
	printf("Check: white King is threatened!\n");
}



/*
 * the traget of the function is to explore if the game achived a situation is called check:
 * player's king is threatened by the opponent. the king can be threated if there is an opponent's piece that can
 * capture the king in the current settings of the gameboard.
 * this function get ChessGame * src- a chess game.
 * and return true if the king in the current turn in "check", it return false otherwise.
 */
bool check(ChessGame* src){

	BoardCell current_pos;
	BoardCell current_king = src->black_King;

	if (src->currentPlayer == WHITE_PLAYER_SYMBOL_1)
		current_king = src->white_King;

	chessGameSwitchPlayer(src); ///change to the turn of the second player.
	int i, j;
	for ( i = 0 ; i < 8 ; i++){
		for ( j = 0; j <8 ; j++){

			current_pos = src->gameBoard[i][j];
			if (chessGameIsValidMove(src,current_pos, current_king, 0, 0)){
				chessGameSwitchPlayer(src); ///change to the turn of the second player.
				return true;
			}
		}
	}
	chessGameSwitchPlayer(src); ///change to the turn of the second player.
	return false;
}


/**
 * checkmate is when current player's king is in check and there is no way to remove the threat.
 * the logic: if there is a legal move in this situation is means that there is a move that exit from the check.
 *
 * @param src - the source game
 *
 * @return false in case current player's king is in check but there is a valid move to remove the threat
 * else it return true.
 *
 */
bool checkmate(ChessGame* src){

	BoardCell current_pos;
	int i, j;
	for ( i = 0 ; i < 8 ; i++){
		for ( j = 0; j <8 ; j++){

			current_pos = src->gameBoard[i][j];
			if(atLeastOneValidMove(src,current_pos, 1))
				return 0;
		}
	}
	return 1;
}


///**
// * Checks if the game or the game end with a tie: when the current player have any legal moves, but the king is not threatened
// * by the opponent- no "check".
// * if the game ended with a tie, it return 1 else 0.
// * @param src - the source game
// * @return
// * if the game ended (tie) 1
// * else it return 0.
// */
bool tie(ChessGame* src){

	if(check(src)){
		return false;
	}
	int fm_x, fm_y;
	BoardCell from;
	for ( fm_x = 0; fm_x < 8 ; fm_x++){
		for ( fm_y = 0; fm_y < 8 ; fm_y++){	// only if it is current player piece we will check if this piece have a valid move
			from = src->gameBoard[fm_x][fm_y];
			if( atLeastOneValidMove(src, from, 1))
				return 0;
		}}

	return 1;
}


/*
 * the traget of this function is to check that exist even one legal move from a given BoardCell.
 * @param src - a game of chess.
 *  	  from - Board Cell that we check from it that there is at least one legal move from it.
 *  @return true if there is at least one legal move and false if there isn't exist even one legal move.
 */
bool atLeastOneValidMove(ChessGame* src, BoardCell from, bool checkFor_Check){

	BoardCell to;
	int to_x, to_y;
	for ( to_x = 0; to_x < 8 ; to_x++){
		for ( to_y= 0; to_y< 8 ; to_y++){
			to = src->gameBoard[to_x][to_y];
			if (chessGameIsValidMove(src,from,to,0,checkFor_Check)){
				return 1;
			}

		}}
	return 0;
}




/**
 * check the legal of move of piece with type of pawn. it check the order and dicide if the move is legal by the law of chess.
 *
 * @param src - The source game
 * @param from - The specified source Board Cell.
 * @param to - The specified destination Board Cell.
 * @return
 * true  - if the a piece can be put in the target destination BoardCell: if the move of the pawn is legal.
 * false - otherwise.
 */
bool pawnValidMove(ChessGame* game ,BoardCell from, BoardCell to) { //consider change from bool to integer like 1-4...

	int dif = to.x - from.x; //the differce of the raws.
	BoardCell midCell;

	if( to.piece == Blank && from.y == to.y){ //to blank and the same column

		if(from.color_cell == WHITE_PLAYER_SYMBOL_1){
			if( dif == 1) return 1;
			if(from.x == 1 &&  dif == 2){
				midCell = game->gameBoard[from.x+1][from.y];
				if(midCell.piece == Blank) return 1;
				return 0;
			}
		}

		if(from.color_cell == BLACK_PLAYER_SYMBOL_0){
			if( dif == -1) return 1;
			if(from.x == 6 &&  dif == -2 ){
				midCell = game->gameBoard[from.x-1][from.y];
				if(midCell.piece == Blank) return 1;
				return 0;
			}
		}
	}
	// we already checked from and to color are different, if not blank we can capture only on diag forward
	if( to.piece != Blank){
		if(from.color_cell == 1){
			if( dif == 1 && ( abs (to.y - from.y) == 1 )) return 1;
		}
		if(from.color_cell == 0){
			if( dif == -1 && ( abs (to.y - from.y) == 1 )) return 1;
		}
	}

	return 0;
}

/**
 * check the legal of move of piece with type of bishop. it check the order and dicide if the move is legal by the law of chess.
 *there are some situations that it check:
 	       case 1        case 2	        case 3       case 4
//   	|      to     |     fm      | fm         | to
//   	|    /        |    /        |   \        |   \
//	    |   /         |   /         |    \       |    \
//	    | fm          | to          |      to    |      fm
//	      - - - -        - - - -      - - - -      - - - -

 * @param src - The source game
 * @param from - The specified source Board Cell.
 * @param to - The specified destination Board Cell.
 * @return
 * true  - if the a piece can be put in the target destination BoardCell: if the move of the bishop is legal.
 * false - otherwise.
 */

bool bishopValidMove(ChessGame* src, BoardCell from, BoardCell to) {
	//make sure its on  diag
	if(abs(from.x - to.x)!= abs(from.y-to.y)){
		return 0;
	}

	if(from.x > to.x){
		if(from.y > to.y){ // case 2
			return checkBlankUpDiagToRight(src, to.x, to.y, from.x, from.y);
		}// case 3
		return checkBlankUpDiagToLeft(src, from.x,from.y, to.x, to.y);
	}
	if(from.x < to.x){
		if(from.y > to.y){ // case 4
			return checkBlankDownDiagToRight(src, to.x, to.y, from.x,from.y);
		}// case 1
		return checkBlankDownDiagToLeft(src, from.x, from.y, to.x, to.y);
	}
	return 0; //will not reach here.
}
/*
 * the traget of the function is to check if the way, diagonal (not including) source:"from" destination: "to" fill with blank.
 *  	     case 3
//   	| fm         |
//   	|   \        |
//	    |    \       |
//	    |      to    |
 * @param src - The source game.
 * the functions get  left_X,  left_Y,  right_X,  right_Y it means: from.x,from.y, to.x, to.y in the same order.
 * that value are required to do the calculte.
-
 * @return true if the case 3 diagonal is only blank, else otherwise.
 */
bool checkBlankUpDiagToLeft(ChessGame* src, int left_X, int left_Y, int right_X, int right_Y){////case 3
	int i, j;
	for ( i = right_X+1,j = right_Y-1  ; i < left_X  &&  j > left_Y ;  i++, j--){
		if (src->gameBoard[i][j].piece != Blank){
			return 0;
		}}
	return 1;
}

/*
 * the traget of the function is to check if the way, diagonal (not including) source:"from" destination: "to" fill with blank.
 *  	     case 2
//   	|       fm   |
//   	|      /     |
//	    |     /      |
//	    |   to       |
 * @param src - The source game.
 * the functions get  left_X,  left_Y,  right_X,  right_Y it means: to.x, to.y, from.x, from.y in the same order.
 * that value are required to do the calculte.
-
 * @return true if the case 2 diagonal is only blank, else otherwise.
 */
bool checkBlankUpDiagToRight(ChessGame* src, int left_X, int left_Y, int right_X, int right_Y){ ///////case 2
	int i, j;
	for ( i = left_X+1,j= left_Y+1  ; i < right_X && j<right_Y;  i++, j++){
		if (src->gameBoard[i][j].piece != Blank){
			return 0;
		}}
	return 1;
}

/*
 * the traget of the function is to check if the way, diagonal (not including) source:"from" destination: "to" fill with blank.
 *  	     case 1
//   	|       to   |
//   	|      /     |
//	    |     /      |
//	    |   fm       |
 * @param src - The source game.
 * the functions get  left_X,  left_Y,  right_X,  right_Y it means: from.x, from.y, to.x, to.y in the same order.
 * that value are required to do the calculte.
-
 * @return true if the case 1 diagonal is only blank, else otherwise.
 */
bool checkBlankDownDiagToLeft(ChessGame* src, int left_X, int left_Y, int right_X, int right_Y){///////case 1
	int i, j;
	for ( i = right_X-1,j= right_Y-1  ; i > left_X   &&  j > left_Y  ;  i--, j--){
		if (src->gameBoard[i][j].piece != Blank){
			return 0;
		}}
	return 1;
}


/*
 * the traget of the function is to check if the way, diagonal (not including) source:"from" destination: "to" fill with blank.
 *  	     case 4
//   	| to         |
//   	|   \        |
//	    |    \       |
//	    |     fm     |
 * @param src - The source game.
 * the functions get  left_X,  left_Y,  right_X,  right_Y it means: to.x, to.y, from.x,from.y in the same order.
 * that value are required to do the calculte.
-
 * @return true if the case 4 diagonal is only blank, else otherwise.
 */
bool checkBlankDownDiagToRight(ChessGame* src, int left_X, int left_Y, int right_X, int right_Y){///////case 4
	int i, j;
	for ( i = left_X-1, j= left_Y+1 ; i > right_X   &&  j < right_Y  ;  i--, j++){
		if (src->gameBoard[i][j].piece != Blank){
			return 0;
		}}
	return 1;
}

/**
 * check the legal of move of piece with type of rook. it check the order and dicide if the move is legal by the law of chess.
 *
 * @param src - The source game
 * @param from - The specified source Board Cell.
 * @param to - The specified destination Board Cell.
 * @return
 * true  - if the a piece can be put in the target destination BoardCell: if the move of the rook is legal.
 * false - otherwise.
 */
bool rookValidMove(ChessGame* src, BoardCell from, BoardCell to){
	if (from.x != to.x && from.y != to.y) // not in the same coloumn or row.
		return 0;

	if (from.y == to.y){
		if( checkBlankColumn( src, from.y, from.x, to.x) == 1 ){
			return 1;
		}}
	if (from.x == to.x){
		if(checkBlankRow( src, from.x, from.y, to.y) == 1){
			return 1;
		}}
	return 0;
}


/*
 * the traget of the function is to check if the way, the horizantal way, (not including) source:"from" destination: "to" fill with blank.
 *  	  case 1    case 2
//   	| to         fm    |
//   	|  |         |     |
//	    |  |         |     |
//	    | fm         to    |
 * @param src - The source game.
 * the functions get   row,  from,  to: the relevant row, the column of from, the column of to, in the same order.
 * that value are required to do the calculte.
-
 * @return true if the thw horizinatl way only blank, else otherwise.
 */

bool checkBlankColumn(ChessGame* src, int column, int from, int to){

	int smaller, bigger;
	bigger = new_max(from, to);
	smaller = new_min(from, to);
	int i;
	for ( i = smaller+1 ; i < bigger ; i++){
		if (src->gameBoard[i][column].piece != Blank){
			return 0;
		}}
	return 1;
}

/*
 * the traget of the function is to check if the way, the horizantal way, (not including) source:"from" destination: "to" fill with blank.
 *  	     case 1
//   	| to  ------ fm       |
//   	|    case 2           |
//	    | fm ------- to       |
//	    |                     |
 * @param src - The source game.
 * the functions get   row,  from,  to: the relevant row, the column of from, the column of to, in the same order.
 * that value are required to do the calculte.
-
 * @return true if the thw horizinatl way only blank, else otherwise.
 */
bool checkBlankRow(ChessGame* src, int row, int from, int to){

	int smaller, bigger;
	bigger = new_max(from, to);
	smaller = new_min(from, to);
	int i;
		for ( i = smaller+1 ; i < bigger ; i++){
		if (src->gameBoard[row][i].piece != Blank){
			return 0;
		}}
	return 1;
}

/**
 * check the legal of move of piece with type of knight. it check the order and dicide if the move is legal by the law of chess.
 *
 * @param src - The source game
 * @param from - The specified source Board Cell.
 * @param to - The specified destination Board Cell.
 * @return
 * true  - if the a piece can be put in the target destination BoardCell: if the move of the knight is legal.
 * false - otherwise.
 */

bool knightValidMove(BoardCell from, BoardCell to) {
	if((abs (from.x - to.x) == 2 && abs (from.y -to.y) == 1) || (abs (from.x - to.x) == 1 && abs (from.y -to.y) == 2))
		return 1;
	return 0;
}

/**
 * check the legal of move of piece with type of queen. it check the order and dicide if the move is legal by the law of chess.
 *
 * @param src - The source game
 * @param from - The specified source Board Cell.
 * @param to - The specified destination Board Cell.
 * @return
 * true  - if the a piece can be put in the target destination BoardCell: if the move of the queen is legal.
 * false - otherwise.
 */
bool queenValidMove(ChessGame* src, BoardCell from, BoardCell to) {
	if (rookValidMove(src, from, to) == 1 || bishopValidMove(src, from, to) == 1 )
		return 1;

	return 0;
}



/**
 * check the legal of move of piece with type of king. it check the order and dicide if the move is legal by the law of chess.
 *
 * @param from - The specified source Board Cell.
 * @param to - The specified destination Board Cell.
 * @return
 * true  - if the a piece can be put in the target destination BoardCell: if the move of the king is legal.
 * false - otherwise.
 */
// 0 and 0 are not available because we checked it already
bool kingValidMove(BoardCell from, BoardCell to){
	if (abs(from.x - to.x) <= 1 && abs (from.y - to.y) <= 1)
		return 1;
	return 0;
}



/**
 * the traget of this function is to restore a round in the game. it means that it remove and the two turns:
 * the last turn of the computer and the last turn of the player. it restore the board to a situation it was a round ago.
 * in means that the the computer turn and player turn is canceled. at the end of this function the turn is of the human player.
 * If the user invoked this command more than historySize times
 * in a row then an error occurs. the user can restore maximum 3 rounds of the game.
 * @param print - integer that represented the stutus of the print.
 * @param src - The source game
 * @return
 * CH_CHESS_GAME_INVALID_ARGUMENT - if src == NULL
 * CH_CHESS_GAME_NO_HISTORY       - if the user invoked this function more then
 *                                 historySize in a row.
 * CH_CHESS_GAME_SUCCESS          - on success. the last round in game canceled and
 *                                               the situation now is the same as a round ago.
 */
Chess_GAME_MESSAGE undo_Two_Move(ChessGame* src, int print){
	if (src==NULL)return CH_CHESS_GAME_INVALID_ARGUMENT; // appropriate message

	if (src->history_size==0 ||src->history_size < 1 ||src->history_queue->actualSize==0){//maybe i have to change
		if(print){ print_Empty_history();}
		return CH_CHESS_GAME_NO_HISTORY;
	}

	historyCell compTurn, playerTurn;

	compTurn= chArrayListGetFirst(src->history_queue);
	chArrayListRemoveFirst(src->history_queue);
	chessGameSwitchPlayer(src);
	if(print){ print_currentRemoved( src->currentPlayer ,compTurn);}

	BoardCell from,to;
	from = compTurn.fromCell;
	to = compTurn.toCell;
	if(from.piece == King ||to.piece == King ){
		restoreKingLocation(src, compTurn.fromCell, compTurn.toCell);
	}

	playerTurn= chArrayListGetFirst(src->history_queue);
	chArrayListRemoveFirst(src->history_queue);
	chessGameSwitchPlayer(src);
	if(print){ print_currentRemoved (src->currentPlayer, playerTurn);}

	from = playerTurn.fromCell;
	to = playerTurn.toCell;
	if(from.piece == King ||to.piece == King ){
		restoreKingLocation(src, playerTurn.fromCell, playerTurn.toCell);
	}

	returnHistoryBoard(&src->gameBoard[0][0], compTurn);
	returnHistoryBoard(&src->gameBoard[0][0], playerTurn);

	//change the turn
	return CH_CHESS_GAME_SUCCESS;




}



/**
 * The traget of this function is to restore the last turn of the computer or the last turn of the player.
 * The main use of this function is during the MiniMAx algorithm which use one insert followed by one undo commonly.
 * @param src - The source game
 * @return
 * CH_CHESS_GAME_INVALID_ARGUMENT - if src == NULL
 * CH_CHESS_GAME_NO_HISTORY       - if the user invoked this function more then
 *                                  historySize.
 * CH_CHESS_GAME_SUCCESS          - on success. the last turn in game canceled and
 *                                  the situation now is the same as a turn ago.
 */
Chess_GAME_MESSAGE undo_One_Move(ChessGame* src){
	if (src==NULL){
		return CH_CHESS_GAME_INVALID_ARGUMENT; // appropriate message
	}

	if (src->history_size==0 ||src->history_queue->actualSize==0)//maybe i have to change
		return CH_CHESS_GAME_NO_HISTORY;

	historyCell turn= chArrayListGetFirst(src->history_queue);
	chArrayListRemoveFirst(src->history_queue);
	chessGameSwitchPlayer(src);

	if(turn.fromCell.piece == King ||turn.toCell.piece == King ){
		restoreKingLocation(src, turn.fromCell, turn.toCell);
	}

	returnHistoryBoard(&src->gameBoard[0][0], turn);

	return CH_CHESS_GAME_SUCCESS;
}




/*
 *the traget of the function is to restore one move - we take the board and one cell history and restore that move.
 * @param: BoardCell * board - the game board.
 * historyCell history - one history cell
 * the function put on the board the cell called: history.
 */
void returnHistoryBoard(BoardCell* board, historyCell history){
	BoardCell from = history.fromCell;
	BoardCell to = history.toCell;

	*(board+from.x*8+from.y) = from;
	*(board+to.x*8+to.y) = to;
}




/**
 * the function print the current undo/current removed that took action.
 *
 * @param current - The player who call the function
 * @param move - the disc that removed.
 *
 */
void print_currentRemoved(int color, historyCell turn){
	BoardCell to ,from;
	to = turn.toCell;
	from = turn.fromCell;
	if (color== 1)
		printf("Undo move for player white : <%d,%c> -> <%d,%c>\n", to.x+1,   to.y+65,  from.x+1, from.y+65);
	if(color== 0)
		printf("Undo move for player black : <%d,%c> -> <%d,%c>\n",  to.x+1,   to.y+65,  from.x+1, from.y+65);
}


/*
 * changes the current player's turn.
 *
 * @param src - The source game
 *
 */
void chessGameSwitchPlayer(ChessGame* src){
	if (src->currentPlayer == WHITE_PLAYER_SYMBOL_1){ //according to cases.
		src->currentPlayer = BLACK_PLAYER_SYMBOL_0;
	}
	else{
		src->currentPlayer = WHITE_PLAYER_SYMBOL_1;
	}
}




/*
 * the traget of the function is to return the user the Board cell that exist at the place mentioned in the Ordered pair: pair.
 * @ param: ChessGame * src - refernce to the game.
 * 			OrderedPair pair- Order pair that we take the Board cell from there.
 * @return BoardeCell : at the place in the Ordered pair.
 */
BoardCell get_BoardCell(ChessGame* src, OrderedPair pair){
	assert(src);
	return src->gameBoard[pair.x][pair.y];
}




/*
 * the command prints the current game settings to the console.
 * */
void print_settings(ChessGame* game){
	printf("SETTINGS:\n");
	printf("GAME_MODE: %d\n",game->playerAmount);
	if (game->playerAmount == 1){
		printf("DIFFICULTY_LVL: %d\n",game->diffLevel);
		if (game->user_color == 0) ///////////////////////don't forget to add the field of user_color to chess_game struct.
			printf("USER_CLR: BLACK\n");
		else
			printf("USER_CLR: WHITE\n");
	}
}

/*
 * the command prints "enter your move" message of the relevant player.
 * */
void prt_next_move(int color){
	if(color == 1)
		printf("white player - enter your move:\n");
	else// black
		printf("black player - enter your move:\n");
}

/*
 * the command prints "Empty history, move cannot be undone".
 * */
void print_Empty_history(){printf("Empty history, move cannot be undone\n");}

/*
 * the command prints "Error: invalid command".
 * */
void print_InvalidCommand(){printf("Error: invalid command\n");}

/*
 * the command prints "The specified position does not contain your piece".
 * */
void print_position_not_contain(){
	printf("The specified position does not contain your piece\n");
}
