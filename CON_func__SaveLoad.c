#include "CON_func__SaveLoad.h"
#include <ctype.h>

#define MAX_LOAD_LINE 100
#define BOARD_LINE 9
//load C:\savedGame\test2.xml


/**
 * Function save current game details in xml form in such order and manner
 * that give the user the ability to return the same game position in future.
 *
 *@param from
 *		- ChessGame* game - game to be saved
 *		- char* out_path  - file contain game information will be created at this address.
 *
 *@return save_load_message:
 * 				invalid_argument - in case function got invalid_argument
 * 				action_faild in case of allocation error
 * 				else que_action_success
 */
save_load_message save_board(ChessGame* game, char* out_path){

	if(game == NULL || out_path == NULL){ print_saveError(); return invalid_argument;}

	FILE *ofp;
	ofp = fopen(out_path, "w");
	if (ofp == NULL){ print_saveError(); return action_faild;}

	char c;


	fprintf(ofp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(ofp, "<game>\n");
	fprintf(ofp, "\t<current_turn>%d</current_turn>\n",game->currentPlayer); // the currnt player.
	fprintf(ofp, "\t<game_mode>%d</game_mode>\n",game->playerAmount);//game_mode is the amount of players in the game.
	if (game->playerAmount == 1){// only in game with the computer
		fprintf(ofp,"\t<difficulty>%d</difficulty>\n",game->diffLevel); // the difficulty of the game.
		fprintf(ofp,"\t<user_color>%d</user_color>\n",game->user_color); // the color of the user.
	}
	BoardCell* boardPointer = &game->gameBoard[0][0];
	int row, colom;
	fprintf(ofp, "\t<board>\n");
	for(  row = 7; 0 <= row; row--){//the printing method
		fprintf(ofp, "\t\t<row_%d>",row + 1);
		for(  colom = 0; colom < 8; colom++){
			c = (char)(boardPointer+row*8+colom)->represent;
			fprintf(ofp,"%c",c);
		}
		fprintf(ofp,"</row_%d>\n",row+1);
	}
	fprintf(ofp, "\t</board>\n");
	fprintf(ofp, "</game>\n");

	if (fclose(ofp) == EOF){ print_saveError(); return action_faild;}
	return action_success;
}



//load C:\savedGame\test2.xml

/**
 * Function load game save at xml form from a given address.
 *@param from
 *		- ChessGame* game - game to be update with the loaded game info
 *		- char* in_path  - addres of the file that contain the game information.
 *
 *@return save_load_message:
 * 				invalid_argument - in case function got invalid_argument
 * 				action_faild in case of allocation error or the file hold the game information in the wrong form.
 * 				else que_action_success
 */
save_load_message load_game( ChessGame* src, char* in_path){

	if(src == NULL ||in_path == NULL ) return invalid_argument;

	FILE *ifp;
	ifp = fopen(in_path, "r");
	if(!ifp){ print_loadError();  return action_faild; }

	ChessGame* game = initDefaultChessGame();
	if(game==NULL){  return invalid_argument; }


	if(load_first_settings(game, ifp)){
		print_loadError();
		fclose(ifp);
		chessGameDestroy(game);
		return action_faild;
	}

	if(load_board(game, ifp)){
		print_loadError();
		fclose(ifp);
		chessGameDestroy(game);
		return action_faild;
	}

	fclose(ifp);
	updateGame_From_loaded_Game(src,game);
	chessGameDestroy(game);
	return action_success;
}


//load C:\savedGame\test2.xml

/**
 * Function get  reference of a chess game and reference of a File.
 * The function update the given game settings fields according to the
 * chess game details stored in the file.
 *
 *	@param from
 *		- ChessGame* src - game to be update
 *		- FILE* ifp      - file that contain game settings information.
 *
 * @return
 * 	int 1 in case of a problem
 * 	int 0 in case of success
 */
int load_first_settings(ChessGame* game, FILE* ifp){
	char this_line[MAX_LOAD_LINE];
	int flag = 0, len, arg;
	char* line_index;



	while( fgets(this_line, MAX_LOAD_LINE, ifp) != NULL){// every cycle we take a word and compare the begging, if the begging equal, so the next is the requeired.

		line_index = this_line;
		while(isspace(*line_index)){
			++line_index;
		}

		if(flag == 0){
			len = strlen("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
			if( strncmp(line_index,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>", len)!= 0) return 1;
			flag = 1;
			continue;
		}

		if (flag == 1){
			if( strncmp(line_index,"<game>",  strlen("<game>"))!= 0)  return 1;
			flag = 2;
			continue;
		}

		if (flag == 2){
			len = strlen("<current_turn>");
			if( strncmp(line_index, "<current_turn>", len )!= 0) return 1;
			arg = line_index[len] -'0';
			if (arg > 1 || arg < 0) return 1;
			game->currentPlayer =  arg;
			flag = 3;
			continue;
		}

		if (flag == 3){//equals to 1
			len = strlen("<game_mode>");
			if( strncmp(line_index, "<game_mode>", len )!= 0)  return 1;
			arg = line_index[len] -'0';
			if (arg > 2 || arg < 1) return 1;
			game->playerAmount =  arg;
			if(	game->playerAmount == 2)  return 0;
			flag = 4;
			continue;
		}

		if (flag == 4){
			len = strlen("<difficulty>");
			if( strncmp(line_index, "<difficulty>", len )!= 0)  return 1;
			arg = line_index[len] -'0';
			if (arg > 4 || arg <0) return 1;
			game->diffLevel =  arg;
			flag = 5;
			continue;
		}
		if (flag == 5){
			len = strlen("<user_color>");
			if( strncmp(line_index,"<user_color>", len)!= 0) return 1;
			arg = line_index[len] -'0';
			if (arg>1 || arg <0) return 1;
			game->user_color = arg;
			return 0;
		}

		return 1;
	}

	return 1;
}

/**
 * Function get  reference of a chess game and reference of a File.
 * The function update the given game board according to the
 * chess game details stored in the file.
 *
 *	@param from
 *		- ChessGame* src - game to be update
 *		- FILE* ifp      - file that contain game board information.
 *
 * @return
 * 	int 1 in case of a problem
 * 	int 0 in case of success
 */
int load_board(ChessGame* game, FILE* ifp){

	char line[MAX_LOAD_LINE], boardLine[BOARD_LINE];; //araay to read lines.
	BoardPiece piece;
	int color, flag = 0, conter = 8;
	char* line_index;



	while( fgets(line, MAX_LOAD_LINE, ifp) != NULL){// every cycle we take a word and compare the begging, if the begging equal, so the next is the requeired.

		line_index = line;
		while(isspace(*line_index)){
			++line_index;
		}

		if(flag == 0){
			if( strncmp(line_index,"<board>", strlen("<board>") )!=0) return 1;
			flag = 1;
			continue;
		}
		if (flag == 1 && conter > 0){
			if ( strncmp(line_index, "<row_",5) != 0){ return 1;}
			line_index += strlen("<row_")+2;
			if( memcpy(boardLine, line_index ,BOARD_LINE) == NULL) return 1;
			int j;
			for ( j = 0 ; j < 8 ; j++){
				piece = get_board_piece( boardLine[j] );
				color = get_color_piece( boardLine[j] );
				game->gameBoard[conter-1][j].color_cell = color;
				game->gameBoard[conter-1][j].represent = boardLine[j];
				game->gameBoard[conter-1][j].piece = piece;
				if(piece == King){
					updateKingLocation(game,game->gameBoard[conter-1][j],game->gameBoard[conter-1][j]);
				}
			}
			conter--;
			continue;
		}
		break;
	}
	if(conter > 0) return 1;
	return 0;
}

/**
 * Function get two chess game reference and update one game according to other game information.
 *	@param from
 *		- ChessGame* toGame   - the game to be update
 *		- ChessGame* fromGame - a game that contain the relevant info.
 *
 */
save_load_message updateGame_From_loaded_Game(ChessGame* toGame, ChessGame* fromGame){
	toGame->playerAmount = fromGame->playerAmount;
	toGame->history_size = fromGame->history_size; //decide the historysize.
	chArrayListClear(toGame->history_queue);
	toGame->mode = fromGame->mode;
	toGame->diffLevel = fromGame->diffLevel;
	toGame->currentPlayer  = fromGame->currentPlayer;
	toGame->user_color  = fromGame->user_color;

	chessBoardCopy(&fromGame->gameBoard[0][0],&toGame->gameBoard[0][0]);

	toGame->white_King = fromGame->white_King;
	toGame->black_King = fromGame->black_King;

	return action_success;
}

/**
 * Function get  char that represent a chess game piece ant return the right BoardPiece.
 *
 *	@param from
 *		- char piece - represent BoardPiece
 * @return
 * 		represented BoardPiece
 *
 */
BoardPiece  get_board_piece(char piece){
	if (piece == 'm' || piece == 'M')
		return Pawn;
	if (piece =='b' || piece =='B' )
		return Bishop;
	if (piece =='r' || piece =='R' )
		return Rook;
	if (piece =='n' || piece =='N' )
		return Knight;
	if (piece =='q' || piece =='Q' )
		return Queen;
	if (piece =='k' || piece =='K' )
		return King;
	return Blank;
}

/**
 * Function get  char that represent a chess game piece and color ant return the right piece color.
 *
 * @param from
 *		- char piece - represent BoardPiece
 * @return
 * 		BoardPiece color
 *
 */
int get_color_piece (char piece){/////////////////////need to return the default color of blank
	if (piece == 'm' || piece == 'b' || piece == 'r' || piece == 'n' || piece == 'q' || piece == 'k' || piece == '_')// i guess blank is here
		return 1;
	if(piece == 'M' || piece == 'B' || piece == 'R' || piece == 'N' || piece == 'Q' || piece == 'k')
		return 0;
	return 0; /// because the input is legal it would not get here.
}

// Function print relevant save error message
void print_saveError(){printf("File cannot be created or modified\n");}


// Function print relevant load error message
void print_loadError(){printf("Error: File doesn't exist or cannot be opened\n");}
