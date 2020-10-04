#ifndef CON_FUNC__GAME_H_
#define CON_FUNC__GAME_H_

#include <limits.h>
#include <math.h>
#include <assert.h>

#include "CON_struct__ArrayList.h"
#include "CON_struct__OrderedPair.h"



#define WHITE_PLAYER_SYMBOL_1 1 
#define BLACK_PLAYER_SYMBOL_0 0 
#define CH_CHESS_TIE_SYMBOL '-' 
#define CH_CHESS_GAME_EMPTY_ENTRY '_'


/**
 * Type used for returning error codes from game functions
 */
typedef enum chess_game_message_t {
	CH_CHESS_GAME_INVALID_MOVE,
	CH_CHESS_GAME_INVALID_ARGUMENT,
	CH_CHESS_GAME_NO_HISTORY,
	CH_CHESS_GAME_SUCCESS,
//You may add any message you like
} Chess_GAME_MESSAGE;


typedef enum consolMode {
	game_Mode,
	Settings_Mode,
}Consol_Mode;


typedef enum playerColor {
	black,
	white,
}playerColor;


/*
 * a struct that define chess game, it include:
 * gameBoard: the board that the game played on.
 * history queue: the queue of that saves some cycles ago of the game.
 * playerAmount: save the numbers of human beings that play the game: 1 or 2.
 * currentPlayer: o represent the turn of black player. 1 represent the turn of the white player.
 * diffLevel: represnt the difficulty level of the game: 1-4.
 * white_King: Board cell that follow the white king, every time the white king move it update.
 * black_king: Board cell that follow the black king, every time the black king move it update.
 */
typedef struct chess_game {
	BoardCell gameBoard[8][8];
	CHArrayList *history_queue;
	int history_size;
	int playerAmount;
	int currentPlayer;   // black: 0, white: 1.
	int diffLevel;
	int user_color;
	Consol_Mode mode;
	BoardCell white_King;
	BoardCell black_King;
} ChessGame;


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
ChessGame* initChessGame(int playerAmount, int history_size, int diffLevel, int playerColor, int currentPlayerColor);


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
ChessGame* initDefaultChessGame();

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
ChessGame* chessGameCopy(ChessGame* src);


/**
 * Frees all memory allocation associated with a given game. If src==NULL
 * the function does nothing.
 *
 * @param src - the source game
 */
void chessGameDestroy(ChessGame* src);


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
Chess_GAME_MESSAGE chessGameSetMove(ChessGame* src, OrderedPair source, OrderedPair des, bool print);



/*the function get the board, and two BoardCells: from and to that represent the move of one of the kings.
 * so the functions update the place the king move to.
 * @param: ChessGame* src: an refernce to the board tha game play on.
 * 		   BoardCell from: the Board cell the king was before the move.
 * 		   BoardCell to: the Board cell the king move to.
 * the function update the board location of whiteking or black king if
 * one moved.
 *
 */
void updateKingLocation(ChessGame* src, BoardCell from, BoardCell to);

/*the function get the board, and two BoardCells: from and to that represent the move of one of the kings.
 * so the functions update the place if the king that move.
 * @param: ChessGame* src: an refernce to the board tha game play on.
 * 		   BoardCell from: the Board cell the king was before the move.
 * 		   BoardCell to: the Board cell the king move to.
 * the function update the place of the white_king if he move or update the place of the black king if
 * he move.
 *
 */
void restoreKingLocation(ChessGame* src, BoardCell from, BoardCell to);




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
bool chessGameIsValidMove( ChessGame* src, BoardCell from, BoardCell to, bool print , bool checkFor_Check);



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
int check_Checkmate_Check_Tie(ChessGame* game, int print);

/*
 * the traget of the function is to explore if the game achived a situation is called check:
 * player's king is threatened by the opponent. the king can be threated if there is an opponent's piece that can
 * capture the king in the current settings of the gameboard.
 * this function get ChessGame * src- a chess game.
 * and return true if the king in the current turn in "check", it return false otherwise.
 */
bool check(ChessGame* src);

// print relevant Check message
void print_Check_Message( int playerNum, int userColor, int curPlayer);



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
bool checkmate(ChessGame* src);

// print relevant Checkmate message
void print_Checkmate_Message(int curPlayer);



///**
// * Checks if the game or the game end with a tie: when the current player have any legal moves, but the king is not threatened
// * by the opponent- no "check".
// * if the game ended with a tie, it return 1 else 0.
// * @param src - the source game
// * @return
// * if the game ended (tie) 1
// * else it return 0.
// */
bool tie(ChessGame* src);

// print relevant Tie message
void print_Tie_Message(int playerNum, int userColor, int curPlayer);





/*
 * the traget of this function is to check that exist even one legal move from a given BoardCell.
 * @param src - a game of chess.
 *  	  from - Board Cell that we check from it that there is at least one legal move from it.
 *  @return true if there is at least one legal move and false if there isn't exist even one legal move.
 */
bool atLeastOneValidMove(ChessGame* src, BoardCell from, bool checkFor_Check);


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
bool pawnValidMove(ChessGame* game ,BoardCell from, BoardCell to);


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

bool bishopValidMove(ChessGame* src, BoardCell from, BoardCell to);

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
bool checkBlankUpDiagToLeft(ChessGame* src, int left_X, int left_Y, int right_X, int right_Y);

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
bool checkBlankUpDiagToRight(ChessGame* src, int left_X, int left_Y, int right_X, int right_Y);

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
bool checkBlankDownDiagToLeft(ChessGame* src, int left_X, int left_Y, int right_X, int right_Y);

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
bool checkBlankDownDiagToRight(ChessGame* src, int left_X, int left_Y, int right_X, int right_Y);

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
bool rookValidMove(ChessGame* src, BoardCell from, BoardCell to);



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

bool checkBlankColumn(ChessGame* src, int column, int from, int to);

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
bool checkBlankRow(ChessGame* src, int row, int from, int to);

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

bool knightValidMove(BoardCell from, BoardCell to) ;
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
bool queenValidMove(ChessGame* src, BoardCell from, BoardCell to);



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
bool kingValidMove(BoardCell from, BoardCell to);



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
Chess_GAME_MESSAGE undo_Two_Move(ChessGame* src, int print);



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
Chess_GAME_MESSAGE undo_One_Move(ChessGame* src);



/*
 *the traget of the function is to restore one move - we take the board and one cell history and restore that move.
 * @param: BoardCell * board - the game board.
 * historyCell history - one history cell
 * the function put on the board the cell called: history.
 */
void returnHistoryBoard(BoardCell* board, historyCell history);


/**
 * the function print the current undo/current removed that took action.
 *
 * @param current - The player who call the function
 * @param move - the disc that removed.
 *
 */
void print_currentRemoved(int color, historyCell turn);

/*
 * changes the current player's turn.
 *
 * @param src - The source game
 *
 */
void chessGameSwitchPlayer(ChessGame* src);


/*
 * the traget of the function is to return the user the Board cell that exist at the place mentioned in the Ordered pair: pair.
 * @ param: ChessGame * src - refernce to the game.
 * 			OrderedPair pair- Order pair that we take the Board cell from there.
 * @return BoardeCell : at the place in the Ordered pair.
 */
BoardCell get_BoardCell(ChessGame* src, OrderedPair pair);


/*
 * the command prints the current game settings to the console.
 * */
void print_settings(ChessGame* game);
/*
 * the command prints "enter your move" message of the relevant player.
 * */
void prt_next_move(int color);

/*
 * the command prints "Empty history, move cannot be undone".
 * */
void print_Empty_history();

/*
 * the command prints "Error: invalid command".
 * */
void print_InvalidCommand();

/*
 * the command prints "Illegal move".
 * */
void printIllegal();

/*
 * the command prints "The specified position does not contain your piece".
 * */
void print_position_not_contain();

#endif
