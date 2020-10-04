#ifndef CON_FUNC__MINIMAX_H_
#define CON_FUNC__MINIMAX_H_

#include "CON_func__game.h"

//load C:\savedGame\difficulty_3_test_3.xml
// load C:\savedGame\difficulty_3_test_2.xml
typedef enum mini_max_message {
	mini_max_INVALID_ARGUMENT,
	mini_max_SUCCESS,
} mini_max_message;

typedef enum Min_Or_Max{
	min,
	max,
}Min_Or_Max;




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
mini_max_message chMinimaxSuggestMove(ChessGame* currentGame,historyCell* returnCell, int currentplayer);


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
 */
int bestMove(ChessGame *game, historyCell* returnCell, int ,  int , Min_Or_Max, int alpha, int beta);



/**
 * In case the game is at checkmate state, function return the right infinity value
 * according to the caller player.
 * @param
 *			- int currentplayer.
 *			- int user.
 * @return
 * 		INT_MAX-1 - user won
 * 		INT_MIN+1 - user lost
 */
int right_Infinity_Val(int currentPlayer, int userPlayer);



/* the traget of this function is give the value of the piece acording to the MiniMax caller.
 * the function return the relevant value.
 * if the piece is at the same value of the caller the value is positive, else negative.
 */
int update_score (BoardPiece piece, int pieceColor, int userColor);

/* the traget of this method is to calculate the score of the board. we scan all the board, and sum up
 * the value of the board.
 * the function return the score of the table.
 * this function take in advantage the user colour.
 */
int culcu_score(BoardCell*, int);



#endif /* CON_FUNC__MINIMAX_H_ */
