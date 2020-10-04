#ifndef CON_FUNC__MAINAUX_H_
#define CON_FUNC__MAINAUX_H_


#include "CON_func__Parser.h"
#include "CON_func__SaveLoad.h"
#include "CON_func__miniMax.h"


/*
 * Struct to representing the consol mode of the game: settings mode or game mode.
 * */
typedef enum stat_Quit_Settings{
	gameSettings,
	startGame,
	quitGame,
}start_Quit_Settings;


/**
 * Function update game according to the prefered user game settings.
 * Function keep updating settings until user presse 'start' or 'quit'.
 * @ChessGame** game - the game to be updated.
 * @return
 *		-startGame -user finished typing game settings and pressed start
 *		-quitGame  -user pressed quit
 */
start_Quit_Settings setGameSettings(ChessGame** game);

/**
 * Function get user command and filter relevant command according to the consol mode.
 * Function keep updating settings until user provide a valid command.
 * @ChessGame* game - the game to be updated.
 * @return
 *		-Setting_Command
 */
Setting_Command userCommand(ChessGame* game);


/**
 * Function use minimax algorithem and set the recomended move on the board.
 * @param: ChessGame* game - the game to be updated.
 * 		   const char* enumArray -array of piece name strings, needed for printing.
 * @return
 *		-int true in case of a tie or checkmate - game ended.
 *		-else int 0
 */
bool computerTurn(ChessGame* game, const char* enumArray[], int print);

/**
 * Function execute the user command.
 * @ChessGame* game - the game to be updated.
 * @return
 *		-int 1 - user command is quit.
 *		-int 2 - user command is RESET
 *		-int 3 - user command is undo
 */
int playerTurn(ChessGame* game);


/**
 * Function execute user vs computer chess game .
 * @param: ChessGame* game - the game to be updated.
 * 		   const char* enumArray -  piece name string array which will be forward to computerTurn function.
 * @return
 *		-int 0 - game ended, quit, tie or checkmate.
 *		-int 1 - game ended, user wish to update settings
 */
int user_VS_computer(ChessGame* game, const char* enumArray[]);

/**
 * Function execute user vs computer chess game .
 * @param: ChessGame* game - the game to be updated.
 * 		   const char* enumArray -  piece name string array which will be forward to computerTurn function.
 * @return
 *		-int 0 - game ended, quit, tie or checkmate.
 *		-int 1 - game ended, user wish to update settings
 */
int white_User_VS_black_Computer(ChessGame* game, const char* enumArray[]);


/**
 * Function execute user vs computer chess game .
 * @param: ChessGame* game - the game to be updated.
 * 		   const char* enumArray -  piece name string array which will be forward to computerTurn function.
 * @return
 *		-int 0 - game ended, quit, tie or checkmate.
 *		-int 1 - game ended, user wish to update settings
 */
int black_User_VS_white_Computer(ChessGame* game, const char* enumArray[]);

/**
 * Function execute user vs user chess game .
 * @param: ChessGame* game - the game to be updated.
 * @return
 *		-int 0 - game ended, one of the user command was quit.
 *		-int 1 - game ended,one of the user wish to change settings.
 */
int user_VS_user(ChessGame* game);








#endif /* CON_FUNC__MAINAUX_H_ */
