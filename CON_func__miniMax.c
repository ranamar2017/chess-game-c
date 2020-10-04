#include "CON_func__miniMax.h"






/**
 * Given a game state, this function evaluates the best move according to
 * the current player. The function initiates a MiniMax algorithm up to a
 * specified depth given by maxDepth. The current game state doesn't change
 * by this function including the history of previous moves.
 *
 * @param
 * 			- ChessGame * game - current game
 *			- historyCell* returnCell - The address to update best move values.
 *			- int currentDept - the current dept in the recursive tree.
 *			- int currentplayer - function will calculate the best move for this player.
 *			- Min_Or_Max Max - state if this level is min level or max level.
 *			- int curr_alpha -values in order to implement pruning algorithm
 *			- int curr_beta - values in order to implement pruning algorithm
 * @return
 * 		int bestScore - level bestScore
 *
 */
int bestMove(ChessGame *game, historyCell* returnCell, int currentDept, int currentPlayer, Min_Or_Max Max, int curr_alpha, int curr_beta){

	int gameScore, bestScore,check_or_tie, to_X, to_Y,fm_X, fm_Y;
	int maxDept = game->diffLevel;
	OrderedPair from_pair, to_pair;
	historyCell bestCell;

	check_or_tie = check_Checkmate_Check_Tie(game,0);
	if(currentDept < maxDept  && !check_or_tie){

		if(Max){
			bestScore = INT_MIN;
			for(  fm_X=0; fm_X<8 ; fm_X++){
				for( fm_Y=0; fm_Y<8 ; fm_Y++){


					if(game->gameBoard[fm_X][fm_Y].piece == Blank ){ continue;}
					from_pair = setOrderedPair(fm_X,fm_Y);

					for( to_X=0; to_X<8 ; to_X++){
						for( to_Y=0; to_Y<8 ; to_Y++){

							to_pair = setOrderedPair(to_X,to_Y);
							bestCell = creatHistoryCell(game->gameBoard[fm_X][fm_Y], game->gameBoard[to_X][to_Y]);

							if(curr_alpha >= curr_beta){return bestScore;}

							if( chessGameSetMove(game,from_pair, to_pair, 0) == CH_CHESS_GAME_SUCCESS){
								gameScore = bestMove(game, returnCell, currentDept+1, currentPlayer, min, curr_alpha, curr_beta);
								if ( gameScore > bestScore){
									bestScore = gameScore;
									if(currentDept == 0){(*returnCell) = bestCell;}
									if( bestScore > curr_alpha){ curr_alpha = bestScore;} // prunning
								}
								undo_One_Move(game);
							}
						}
					}
				}
			}
		}

		else{
			bestScore = INT_MAX;
			for(  fm_X=0; fm_X<8 ; fm_X++){
				for( fm_Y=0; fm_Y<8 ; fm_Y++){

					if(game->gameBoard[fm_X][fm_Y].piece == Blank ){ continue;}
					from_pair = setOrderedPair(fm_X,fm_Y);

					for( to_X=0; to_X<8 ; to_X++){
						for( to_Y=0; to_Y<8 ; to_Y++){

							to_pair = setOrderedPair(to_X,to_Y);
							bestCell = creatHistoryCell(game->gameBoard[fm_X][fm_Y], game->gameBoard[to_X][to_Y]);

							if(curr_alpha >= curr_beta){return bestScore;}
							if( chessGameSetMove(game,from_pair,to_pair,0) == CH_CHESS_GAME_SUCCESS){
								gameScore = bestMove(game, returnCell, currentDept+1, currentPlayer, max, curr_alpha, curr_beta);
								if ( gameScore < bestScore){
									bestScore = gameScore;
									if( bestScore < curr_beta){	curr_beta = bestScore;	} // prunning
								}
								undo_One_Move(game);
							}
						}}
				}}
		}
		/// we already update (*returnCell) to bestCell
		if(currentDept == 0){ return 1;}
		return bestScore; 	/// currentDept > 0 and firstTime == 0  then at least one move is valid.
	}

	if(check_or_tie == 1) return right_Infinity_Val(game->currentPlayer,game->user_color);
	return culcu_score(&game->gameBoard[0][0],currentPlayer);
}


/**
 * Given a game state, this function evaluates the best move according to
 * the current player. The function initiates a MiniMax algorithm up to a
 * specified depth given by maxDepth. The current game state doesn't change
 * by this function including the history of previous moves.
 *
 * @param
 * 			- currentGame - The current game state
 *			- historyCell* returnCell - The address to update best move values.
 *			- int currentplayer - function will calculate the best move for this player.
 * @return
 * 		-mini_max_INVALID_ARGUMENT either currentGame is NULL or maxDepth is not in range.
 *		-minimax SUCCESS message in case of success, more over the function will update the
 * 		 returnCell reference to the best move values according to the current player.
 */
mini_max_message chMinimaxSuggestMove(ChessGame* currentGame, historyCell* returnCell, int currentplayer){
	if( currentGame == NULL || returnCell == NULL ) return mini_max_INVALID_ARGUMENT;
	if( currentGame->diffLevel < 1 || currentGame->diffLevel > 4  ) return mini_max_INVALID_ARGUMENT;

	ChessGame* gameCopy = chessGameCopy(currentGame);    /// We made a copy in order to keep the right player last moves values saved in the list.
	if(gameCopy == NULL) return mini_max_INVALID_ARGUMENT;

	bestMove(gameCopy, returnCell, 0, currentplayer,  1, INT_MIN,INT_MAX);
	chessGameDestroy(gameCopy);

	return mini_max_SUCCESS;

}





/* the traget of this function is give the value of the piece acording to the MiniMax caller.
 * the function return the relevant value.
 * if the piece is at the same value of the caller the value is positive, else negative.
 */
int update_score (BoardPiece piece, int pieceColor, int userColor){

	int returnVal = 0; //blank

	if (piece == Pawn)
		returnVal = 1;
	else if (piece == Knight)
		returnVal = 3;
	else if (piece == Bishop)
		returnVal = 3;
	else if (piece == Rook)
		returnVal = 5;
	else if (piece == Queen)
		returnVal = 9;
	else if (piece == King)
		returnVal = 100;

	if(pieceColor != userColor)
		returnVal*=(-1);

	return returnVal; // should not get here
}


/* the traget of this method is to calculate the score of the board. we scan all the board, and sum up
 * the value of the board.
 * the function return the score of the table.
 * this function take in advantage the user colour.
 */
int culcu_score (BoardCell* src, int userColor){

	BoardPiece piece;
	int pieceColor, sum = 0, i ,j;

	for ( i = 0 ; i < 8 ; i++)
		for ( j = 0 ; j < 8 ; j++){//running on every cell in the board
			piece = (src+i*8+j)->piece;
			pieceColor = (src+i*8+j)->color_cell;
			if (piece != Blank){// we did something when there is a relevant piece
				sum += update_score(piece, pieceColor, userColor);
			}
		}
	return sum;
}

/**
 * In case the game is at checkmate state, function return the right infinity value
 * according to the caller player.
 * @param
 *			- int currentplayer.
 *			- int user.
 * @return
 * 		INT_MAX - user won
 * 		INT_MIN - user lost
 */
int right_Infinity_Val(int currentPlayer, int userPlayer){
	if(currentPlayer == userPlayer){
		return INT_MAX-1;
	}
	return INT_MIN+1;
}
