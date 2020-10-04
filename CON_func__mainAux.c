#include "CON_func__mainAux.h"

// load C:\savedGame\difficulty_2_test_2.xml




/**
 * Function update game according to the prefered user game settings.
 * Function keep updating settings until user presse 'start' or 'quit'.
 * @ChessGame** game - the game to be updated.
 * @return
 *		-startGame -user finished typing game settings and pressed start
 *		-quitGame  -user pressed quit
 */
start_Quit_Settings setGameSettings(ChessGame** game){

	while(1){
		Setting_Command command = userCommand((*game));
		if(command.cmd == CH_START){	        (*game)->mode = game_Mode; return startGame;}
		else if(command.cmd == CH_QUIT){	    return quitGame;}
		else if(command.cmd == CH_GAME_MODE){   (*game)->playerAmount = command.arg; continue;}
		else if(command.cmd == CH_USER_COLOR){  (*game)->currentPlayer= (*game)->user_color = command.arg; continue;}
		else if(command.cmd == CH_DIFFICULTY){  (*game)->diffLevel = command.arg; continue;}
		else if(command.cmd == CH_DEFAULT){
			ChessGame* temp = (*game);
			*game = initDefaultChessGame();
			chessGameDestroy(temp);
			continue;
		}
		else if(command.cmd == CH_LOAD){ load_game((*game),command.path); continue;	}
	}
	return 	startGame;
}


/**
 * Function get user command and filter relevant command according to the consol mode.
 * Function keep updating settings until user provide a valid command.
 * @ChessGame* game - the game to be updated.
 * @return
 *		-Setting_Command
 */
Setting_Command userCommand(ChessGame* game) {
	Setting_Command command;
	char user_choice[1024];

	while (1){

		while(fgets(user_choice, 1024, stdin)==NULL){
			fgets(user_choice, 1024, stdin);
		}

		command = chParseLine(user_choice, game->mode == Settings_Mode, game->mode == game_Mode);

		if(game->mode == Settings_Mode){

			if(command.cmd == CH_INVALID_LINE || command.cmd == CH_MOVE ||command.cmd ==  CH_UNDO \
					||command.cmd == CH_SAVE || command.cmd == CH_RESET){continue;}

			if(command.cmd == CH_USER_COLOR ){
				if(command.validArg == 0 || game->playerAmount == 2) continue;
			}
			if(command.cmd == CH_DIFFICULTY){
				if(game->playerAmount == 1 && command.validArg == 1 && command.arg != 5 ) return command;
				if(game->playerAmount == 2 ) continue;
				if(command.validArg == 0){ printf("Wrong difficulty level. The value should be between 1 to 5\n"); continue;}
				if(command.arg == 5){ printf("Expert level not supported, please choose a value between 1 to 4:\n"); continue; 	}
			}

			if(command.cmd == CH_PRINT_SETTING){
				print_settings(game);
				continue;
			}
			return command;
		}



		else{ //game->mode == game_Mode
			if(command.cmd == CH_INVALID_LINE || command.cmd == CH_DEFAULT || command.cmd == CH_START ||command.cmd ==  CH_GAME_MODE
					||command.cmd == CH_USER_COLOR||command.cmd == CH_DIFFICULTY ||command.cmd == CH_PRINT_SETTING || command.cmd == CH_LOAD){
//				print_InvalidCommand(); // we are at game mode1
				continue;
			}
			if(command.cmd == CH_UNDO && game->playerAmount == 2){
				printf("Undo command not available in 2 players mode\n");
				continue;
			}
			return command;
		}
	}
	return command; // won't reach here;
}




/**
 * Function execute the user command.
 * @ChessGame* game - the game to be updated.
 * @return
 *		-int 1 - user command is quit.
 *		-int 2 - user command is RESET
 *		-int 3 - user command is undo
 */
int playerTurn(ChessGame* game){

	Setting_Command command;

	while(1){
		prt_next_move(game->currentPlayer);
		command = userCommand(game); // return only the relevant command for game mode
		if(command.validArg){        // we are at game mode not setting mode
			if( command.cmd == CH_QUIT){ return 1;}
			if( command.cmd == CH_MOVE ){ // set move is valid move, else wont reach here
				if( chessGameSetMove(game, command.from,command.to, 1) == CH_CHESS_GAME_SUCCESS){
					return check_Checkmate_Check_Tie(game,1); 
				}
				continue;
			}
			if( command.cmd == CH_RESET){ return 3;}
			if( command.cmd == CH_UNDO ){ return 4; }
			if( command.cmd == CH_SAVE){ save_board(game, command.path); continue;}
		}
	}
	return 0 ;
}




/**
 * Function use minimax algorithem and set the recomended move on the board.
 * @param: ChessGame* game - the game to be updated.
 * 		   const char* enumArray -array of piece name strings, needed for printing.
 * @return
 *		-int true in case of a tie or checkmate - game ended.
 *		-else int 0
 */
bool computerTurn(ChessGame* game, const char* enumArray[], int print){

	historyCell move = creatHistoryCell( game->gameBoard[0][0], game->gameBoard[0][0]);
	if( chMinimaxSuggestMove(game, &move, game->currentPlayer ) != mini_max_SUCCESS ) printf("\n\n we have a problem with minimax function !\n\n");
	int from_x = move.fromCell.x, from_y = move.fromCell.y;
	int to_x = move.toCell.x , to_y = move.toCell.y;

	OrderedPair from = setOrderedPair(from_x, from_y), to = setOrderedPair(to_x, to_y);
	BoardPiece piece = move.fromCell.piece;

	chessGameSetMove(game, from, to, 0); // 0 mean that there is no need to print
	if(print) printf("Computer: move %s at <%d,%c> to <%d,%c>\n", enumArray[piece], from_x+1, from_y +'A',  to_x+1, to_y +'A' );

	return  check_Checkmate_Check_Tie(game,1);
}










/**
 * Function execute user vs computer chess game .
 * @param: ChessGame* game - the game to be updated.
 * 		   const char* enumArray -  piece name string array which will be forward to computerTurn function.
 * @return
 *		-int 0 - game ended, quit, tie or checkmate.
 *		-int 1 - game ended, user wish to update settings
 */
int user_VS_computer(ChessGame* game, const char* enumArray[]){
	if(game->user_color == 1){
		return white_User_VS_black_Computer( game, enumArray);
	}
	return black_User_VS_white_Computer( game, enumArray);
}


/**
 * Function execute user vs computer chess game .
 * @param: ChessGame* game - the game to be updated.
 * 		   const char* enumArray -  piece name string array which will be forward to computerTurn function.
 * @return
 *		-int 0 - game ended, quit, tie or checkmate.
 *		-int 1 - game ended, user wish to update settings
 */
int white_User_VS_black_Computer(ChessGame* game, const char* enumArray[]){
	int checkmate_check_tie = 0, playerMove, user_start = (game->user_color == game->currentPlayer) ;
	while (1){
		if(user_start){
			if( checkmate_check_tie){ return 0;}
			chessGamePrintBoard2(&game->gameBoard[0][0]);
			playerMove = playerTurn(game);

			if( playerMove ){ // playerMove == 0 only if we will make a valid move any other command will reach here
				if(playerMove ==  1 || playerMove ==  2){ return 0;}
				if(playerMove ==  3){ return 1;} // new from scratch
				if(playerMove ==  4){ undo_Two_Move(game,1); continue;}
			}
		}
		user_start = 1;
		checkmate_check_tie = computerTurn(game, enumArray, 1);
	}
	return 0;
}


/**
 * Function execute user vs computer chess game .
 * @param: ChessGame* game - the game to be updated.
 * 		   const char* enumArray -  piece name string array which will be forward to computerTurn function.
 * @return
 *		-int 0 - game ended, quit, tie or checkmate.
 *		-int 1 - game ended, user wish to update settings
 */
int black_User_VS_white_Computer(ChessGame* game, const char* enumArray[]){

	int checkmate_check_tie = 0, playerMove, player_start = (game->user_color == game->currentPlayer) ;

	while (1){
		if(!player_start){
			checkmate_check_tie = computerTurn(game, enumArray, 1);
			if( checkmate_check_tie) return 0;
		}

		chessGamePrintBoard2(&game->gameBoard[0][0]);
		playerMove = playerTurn(game);
		player_start= 0;
		if( playerMove ){ // playerMove == 0 only if we will make a valid move any other command will reach here
			if(playerMove ==  1 || playerMove ==  2)  return 0;
			if(playerMove ==  3)  return 1;
			if(playerMove ==  4){ player_start = 1; undo_Two_Move(game,1); continue;}
		}
	}
	return 0;
}




/**
 * Function execute user vs user chess game .
 * @param: ChessGame* game - the game to be updated.
 * @return
 *		-int 0 - game ended, one of the user command was quit.
 *		-int 1 - game ended,one of the user wish to change settings.
 */
int user_VS_user(ChessGame* game){

	int first_playerMove, second_playerMove;
	while (1){
		chessGamePrintBoard2(&game->gameBoard[0][0]);
		first_playerMove = playerTurn(game);

		if( first_playerMove ){ // playerMove == 0 only if we will make a valid move any other command will reach here
			if(first_playerMove ==  1|| first_playerMove == 2) return 0;
			if(first_playerMove ==  3) return 1; // new from scratch
		}

		chessGamePrintBoard2(&game->gameBoard[0][0]);
		second_playerMove = playerTurn(game);
		if( second_playerMove ){ // playerMove == 0 only if we will make a valid move any other command will reach here
			if(second_playerMove ==  1|| second_playerMove == 2) return 0;
			if(second_playerMove ==  3)  return 1; // new from scratch
		}
	}
	return 0;
}








