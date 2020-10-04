#ifndef CON_STRUCT__GAMEBOARD_H_
#define CON_STRUCT__GAMEBOARD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// enum to represent all possible chess board piece.
typedef enum BoardPiece{
	Pawn,
	Bishop,
	Rook,
	Knight,
	Queen,
	King,
	Blank,
}BoardPiece;

/* a struct representing a cell in the game table: include the piece, the color of the cell, x and y
 * values on the board and the char that represent the piece.
 */
typedef struct chess_board_cell {
	BoardPiece piece;
	int color_cell; //the constant color of the table
	char represent;
	int x;
	int y;
}BoardCell;

/*
 * Function build a new cell of game board.
 * @param: BoardPiece piece: get the kind of board piece.
 * 		   int color: it get the color: white or black - 0 mean black player piece, 1 mean white player piece.
 * 		   int x: the x value - vertical value in the Board (0-7)
 * 		   int y: the y value - horizentical value in the board (0-7)
 * 		   the piece can be blank - mean that no piece sit there.
 * @return:
 * 			BoardCell with right parameters according the parameters.
 */
BoardCell makeColored_Piece( BoardPiece piece ,int color, int x, int y);


// the function build new White pawn with the x,y parametrs that we send to the function.
BoardCell makeWhite_Pawn( int x, int y);
// the function build new black pawn with the x,y parametrs that we send to the function.
BoardCell makeBlack_Pawn(int x, int y);

// the function build new White bishop with the x,y parametrs that we send to the function.
BoardCell makeWhite_Bishop( int x, int y);
// the function build new black bishop with the x,y parametrs that we send to the function.
BoardCell makeBlack_Bishop( int x, int y);

// the function build new White rook with the x,y parametrs that we send to the function.
BoardCell makeWhite_Rook( int x, int y);
// the function build new black rook with the x,y parametrs that we send to the function.
BoardCell makeBlack_Rook( int x, int y);

// the function build new White knight with the x,y parametrs that we send to the function.
BoardCell makeWhite_Knight( int x, int y);
// the function build new black knight with the x,y parametrs that we send to the function.
BoardCell makeBlack_Knight( int x, int y);

// the function build new White queen with the x,y parametrs that we send to the function.
BoardCell makeWhite_Queen( int x, int y);
// the function build new black queen with the x,y parametrs that we send to the function.
BoardCell makeBlack_Queen( int x, int y);

// the function build new White king with the x,y parametrs that we send to the function.
BoardCell makeWhite_King( int x, int y);
// the function build new black king with the x,y parametrs that we send to the function.
BoardCell makeBlack_King( int x, int y);

// the function build new blank cell with the x,y parametrs that we send to the function.
BoardCell makeBlank( int x, int y);



//
/**
 * On success, the function prints the board game. If an error occurs, then the
 * function does nothing. The characters: 'm' 'b' 'r' 'n' 'q' 'k' '_'  and  are used to represent
 * the pieces of player 1 and the same characters but in big letters are used to represent player 2.
 *
 * @param src - the target game
 * print relevant message if  - if src==NULL
 * print the board - otherwise
 *
 */
void chessGamePrintBoard2(BoardCell* src);

/* Function cope old_board cells to new_board.
 * @param the function get two refrences to BoardCell
 */
void chessBoardCopy(BoardCell* old_board, BoardCell* new_board);


/* Function initiate new legal beginning chess Board.
 * @param BoradCell* board - refrence to BoardeCell
 *  the function update the board to be legal start board of the game.
*/
void initValidChessBoard( BoardCell* board);

/*
 * Target of the function is to copy BoardCells values from one given cell to another.
 * the function get two BoardCell: old and new.
 * the function copy the values of the old BoardCell to the new.
 */
void update_Board_Cell(BoardCell* old, BoardCell* new);

#endif
