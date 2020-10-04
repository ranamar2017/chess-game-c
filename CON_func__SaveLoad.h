#ifndef CON_FUNC__SAVELOAD_H_
#define CON_FUNC__SAVELOAD_H_

#include "CON_func__game.h"


typedef enum save_load_message {
	invalid_argument,
	action_faild,
	action_success,
}save_load_message;



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
save_load_message save_board(ChessGame* game, char* out_path);


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
save_load_message load_game( ChessGame* src, char* in_path);


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

int load_first_settings(ChessGame* game, FILE* ifp);
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
int load_board(ChessGame* game, FILE* ifp);



/**
 * Function get two chess game reference and update one game according to other game information.
  *	@param from
 *		- ChessGame* toGame   - the game to be update
 *		- ChessGame* fromGame - a game that contain the relevant info.
 *
 */
save_load_message updateGame_From_loaded_Game(ChessGame* toGame, ChessGame* fromGame);


/**
 * Function get  char that represent a chess game piece ant return the right BoardPiece.
 *
 *	@param from
 *		- char piece - represent BoardPiece
 * @return
 * 		represented BoardPiece
 *
 */
BoardPiece  get_board_piece(char piece);


/**
 * Function get  char that represent a chess game piece and color ant return the right piece color.
 *
 * @param from
 *		- char piece - represent BoardPiece
 * @return
 * 		BoardPiece color
 *
 */
int get_color_piece (char piece);

// Function print relevant save error message
void print_saveError();

// Function print relevant load error message
void print_loadError();

#endif
