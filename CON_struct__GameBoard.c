#include "CON_struct__GameBoard.h"


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
BoardCell makeColored_Piece( BoardPiece piece ,int color, int x, int y){

	BoardCell newPiece;
	char rep = '_';

	switch (piece){
	case Pawn:
		if(color == 1){ rep = 'm'; break;}
		rep ='M'; break;

	case Bishop:
		if(color == 1){ rep = 'b' ; break;}
		rep ='B'; break;

	case Rook:
		if(color == 1){ rep = 'r' ; break;}
		rep ='R'; break;

	case Knight:
		if(color == 1){ rep = 'n' ; break;}
		rep ='N'; break;

	case Queen:
		if(color == 1){ rep = 'q' ; break;}
		rep ='Q'; break;
	case King:
		if(color == 1){ rep = 'k' ; break;}
		rep ='K'; break;

	case Blank:
		rep ='_'; break;
	}

	newPiece = (BoardCell){piece,color,rep, x,y};
	return newPiece;
}


// the function build new White pawn with the x,y parametrs that we send to the function.
BoardCell makeWhite_Pawn( int x, int y){
	return makeColored_Piece(Pawn,1,x,y);}

// the function build new black pawn with the x,y parametrs that we send to the function.
BoardCell makeBlack_Pawn(int x, int y){
	return makeColored_Piece(Pawn,0,x,y);}

// the function build new White bishop with the x,y parametrs that we send to the function.
BoardCell makeWhite_Bishop( int x, int y){
	return makeColored_Piece(Bishop,1,x,y);}
// the function build new black bishop with the x,y parametrs that we send to the function.
BoardCell makeBlack_Bishop( int x, int y){
	return makeColored_Piece(Bishop,0,x,y);}

// the function build new White rook with the x,y parametrs that we send to the function.
BoardCell makeWhite_Rook( int x, int y){
	return makeColored_Piece(Rook,1,x,y);}
// the function build new black rook with the x,y parametrs that we send to the function.
BoardCell makeBlack_Rook( int x, int y){
	return makeColored_Piece(Rook,0,x,y);}

// the function build new White knight with the x,y parametrs that we send to the function.
BoardCell makeWhite_Knight( int x, int y){
	return makeColored_Piece(Knight,1,x,y);}
// the function build new black knight with the x,y parametrs that we send to the function.
BoardCell makeBlack_Knight( int x, int y){
	return makeColored_Piece(Knight,0,x,y);}

// the function build new White queen with the x,y parametrs that we send to the function.
BoardCell makeWhite_Queen( int x, int y){
	return makeColored_Piece(Queen,1,x,y);}
// the function build new black queen with the x,y parametrs that we send to the function.
BoardCell makeBlack_Queen( int x, int y){
	return makeColored_Piece(Queen,0,x,y);}

// the function build new White king with the x,y parametrs that we send to the function.
BoardCell makeWhite_King( int x, int y){
	return makeColored_Piece(King,1,x,y);}
// the function build new black king with the x,y parametrs that we send to the function.
BoardCell makeBlack_King( int x, int y){
	return makeColored_Piece(King,0,x,y);}

// the function build new blank cell with the x,y parametrs that we send to the function.
BoardCell makeBlank( int x, int y){
	return makeColored_Piece(Blank,1,x,y);}




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
void chessGamePrintBoard2(BoardCell* src){

	if (src == NULL){
		printf("ChessGamePrintBoard got NULL");
	}
	int row, colom;
	for( row = 7; 0 <= row; row--){//the printing method
		printf("%d| ",row + 1);
		for(  colom = 0; colom <= 7; colom++){
			printf("%c ",(*(src+row*8+colom)).represent);
		}
		printf("|\n");
	}
	printf("  -----------------\n");
	printf("   A B C D E F G H\n");
	fflush(stdout);

}

/* Function cope old_board cells to new_board.
 * @param the function get two refrences to BoardCell
 */
void chessBoardCopy(BoardCell* old_board, BoardCell* new_board){
	int i,j;
	for (i = 0 ; i <8 ; i++){
		for (j = 0 ; j < 8; j++){
			*(new_board + 8 * i + j) =  *(old_board + 8  * i + j);
		}}
}


/* Function initiate new legal beginning chess Board.
 * @param BoradCell* board - refrence to BoardeCell
 *  the function update the board to be legal start board of the game.
*/
void initValidChessBoard( BoardCell* board){

	BoardPiece firstRow[8] = {Rook ,Knight ,Bishop, Queen, King, Bishop, Knight, Rook};
	int i,j;
	for(i = 2; i<6; i++){
		for( j = 0; j<8; j++){
			*(board+i*8+j)=  makeBlank(i,j);
		}}

	for( j = 0; j<8; j++){
		*(board+7*8+j) =  makeColored_Piece( firstRow[j] ,0, 7, j);
		*(board+6*8+j) =   makeBlack_Pawn(6, j);

		*(board+8+j) =   makeWhite_Pawn( 1, j);
		*(board+j) =      makeColored_Piece( firstRow[j] ,1, 0, j);

	}
}

/*
 * Target of the function is to copy BoardCells values from one given cell to another.
 * the function get two BoardCell: old and new.
 * the function copy the values of the old BoardCell to the new.
 */
void update_Board_Cell(BoardCell* old, BoardCell* new){
	new->color_cell = old->color_cell;
	new->piece = old->piece;
	new->represent = old->represent;
}

