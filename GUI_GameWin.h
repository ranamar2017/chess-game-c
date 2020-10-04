/*
 * gameWin.h
 *
 *  Created on: Sep 16, 2017
 *      Author: ranam
 */

#ifndef GUI_GAMEWIN_H_
#define GUI_GAMEWIN_H_



#include <SDL.h>
#include <stdbool.h>
//#include "CON_func__game.h"
#include "CON_func__mainAux.h"
//#include "CON_func__miniMax.h"


//the traget of the enum is to represent a situation, event, at the game window.
 typedef enum {
	MAIN_GAME_EXIT,BLACK_WON,WHITE_WON,CHECK_ON_WHITE,CHECK_ON_BLACK,
	TIE, GAME_RESTART,GAME_SAVE,GAME_LOAD,GAME_UNDO,GAME_MAIN_MENU,GAME_END,
	GAME_INVALID_ARGUMENT,GAME_NONE,PIECE_MOVE,MOUSE_MOVE,MOUSE_DES
} GAME_EVENT;

//the traget is to hold a mouse position.
typedef struct {
	int x_mouse_down;
	int y_mouse_down;
	int x_current;
	int y_current;
	int x_mouse_up;
	int y_mouse_up;
	bool mouse_down;
	bool mouse_motion;
	bool mouse_up;
}MOVE;

//the traget is to hold a game.
typedef struct {
	//SDL_Window* window;
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	SDL_Texture* background_texture;
	SDL_Texture* restart_choose_texture;
	SDL_Texture* save_choose_texture;
	SDL_Texture* load_choose_texture;
	SDL_Texture* undo_not_choose_texture;
	SDL_Texture* undo_choose_texture;
	SDL_Texture* mainMenu_choose_texture;
	SDL_Texture* quit_choose_texture;
	SDL_Texture* white_pawn_texture;
	SDL_Texture* white_bishop_texture;
	SDL_Texture* white_rook_texture;
	SDL_Texture* white_knight_texture;
	SDL_Texture* white_queen_texture;
	SDL_Texture* white_king_texture;
	SDL_Texture* black_pawn_texture;
	SDL_Texture* black_bishop_texture;
	SDL_Texture* black_rook_texture;
	SDL_Texture* black_knight_texture;
	SDL_Texture* black_queen_texture;
	SDL_Texture* black_king_texture;
	MOVE  move_relevant;
	ChessGame* the_game;
} GameWin;

/*the traget of the function is to creat a window for the board game  of the game.
  * the function return a struct GameWin, that includes all the relevant parametes for the main menu.
 */
GameWin* gameWindowCreate(int playerAmount,int diffLevel,int playerColor,int currentPlayerColor);


/* the traget of the function is to free the memory of the struct and it components.
 *  it get refernce for GameWin and destroy all the fields in the struct.
 */
void gameWindowDestroy(GameWin* src);

/*the traget of the function is to draw the game window on the board.
 * the function get refernce of GameWin and draw it on the window.
 */
void gameWindowDraw(GameWin* current);

/* represent click on restart.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnGameRestart(int x, int y);

/* represent click on save.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnGameSave(int x, int y);

/* represent click on load.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnGameLoad(int x, int y);

/* represent click on undo.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnGameUndo(int x, int y);

/* represent click on main menu.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnGameMainMenu(int x, int y);

/* represent click on quit.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnGameMainQuit(int x, int y);

/* represent click on the board in order to put a piece.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
*/
int isClickOnDes(int x, int y);

/* represent click on the board in order to move a piece.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
*/
int isClickOnSource(int x, int y);

/* the trgaet of the function is handle an event.
 * the function get refreces for GameWin and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
GAME_EVENT gameWindowHandleEvent(GameWin* src, SDL_Event* event);

/* the trgaet of the function is transalte a place on the board to  an order pair in the game,
 * that represnt a location such as: <2,a>
*/
OrderedPair place_in_board(int x, int y);


/*the traget of the function is to draw the game window on the board.
 * the function get refernce of GameWin and draw it on the window.
 */
void gameBoardDraw(GameWin* current,char pie,SDL_Rect * Position_pieces);

//the traget is to hide a window.
void mainGameWindowHide(GameWin* src);

//the traget is to show a window.
void mainGameWindowShow(GameWin* src);

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int game_Upload_Textures_1 (SDL_Surface* loading_surface,GameWin * current );

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int game_Upload_Textures_2 (SDL_Surface* loading_surface,GameWin * current );

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int game_Upload_Textures_3 (SDL_Surface* loading_surface,GameWin * current );

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int game_Upload_Textures_4 (SDL_Surface* loading_surface,GameWin * current );

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int game_Upload_Textures_5 (SDL_Surface* loading_surface,GameWin * current );

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int game_Upload_Textures_6 (SDL_Surface* loading_surface,GameWin * current );

/* the trgaet of the function is handle an event- simulate a turn in the game.
 * the function get refreces for GameWin and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
GAME_EVENT gameWindowHandlePlayEvent(GameWin* src);

/*the function get a specific describe of a piece and draw it on the board.
 * it get refernce of GameWin , SDL_Rect and info on the piece and draw it.
 */
void gameWindowDrawPieces(GameWin* current,SDL_Rect Position_pieces,int color_piece,BoardPiece piece);

#endif /* GUI_GAMEWIN_H_ */
