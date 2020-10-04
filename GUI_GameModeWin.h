/*
 * mainGameMode.h
 *
 *  Created on: Sep 15, 2017
 *      Author: ranam
 */

#ifndef GUI_GAMEMODEWIN_H_
#define GUI_GAMEMODEWIN_H_

#include <SDL.h>
#include <stdbool.h>

//the traget of the enum is to represent a situation, event, at the game_mode menu.
typedef enum {
	MAIN_GAME_MODE_EXIT, MAIN_GAME_MODE_BACK,MAIN_GAME_MODE_START,MAIN_GAME_MODE_NEXT, MAIN_GAME_MODE_INVALID_ARGUMENT,
	MAIN_GAME_MODE_NONE,ONE_PLAYER,TWO_PLAYERS
} MAIN_GAME_MODE_EVENT;


//the traget is to hold a game_mode.
typedef struct {
	//SDL_Window* window;
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	SDL_Texture* background_texture;
	SDL_Texture* one_choose_texture;
	SDL_Texture* one_not_choose_texture;
	SDL_Texture* two_choose_texture;
	SDL_Texture* two_not_choose_texture;
	SDL_Texture* start_texture;
	SDL_Texture* next_texture;
	SDL_Texture* back_texture;
	bool two_players ; // one player: 0, two players:1
	bool next_button ; // next: 1, start: 0;
} MainGameMode;


/*the traget of the function is to creat a window for the game mode window.
 * the function return a struct MainGameMode, that includes all the relevant parametes for the main menu.
 */
MainGameMode* mainGameModeWindowCreate();

/* the traget of the function is to free the memory of the struct and it components.
 * it get refernce for MainGameMode and destroy all the fields in the struct.
*/
void mainGameModeWindowDestroy(MainGameMode* src);

/*the traget of the function is to draw the game mode  on the board.
 * the function get refernce of MainGameMode and draw it on the window.
 */
void mainGameModeWindowDraw(MainGameMode* current);


//the traget is to hide a window.
void mainGameModeWindowHide(MainGameMode* src);


//the traget is to show a window.
void mainGameModeWindowShow(MainGameMode* src);


/* the trgaet of the function is handle an event.
 * the function get refreces for MainGameMode and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
MAIN_GAME_MODE_EVENT mainGameModeWindowHandleEvent(MainGameMode* src, SDL_Event* event);


/* represent click on the start button.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnStart(int x, int y);

/* represent click on the next button.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnNext(int x, int y) ;

/* represent click on the one player button.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnOnePlayer(int x, int y) ;

/* represent click on the two player button.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnTwoPlayer(int x, int y);

/* represent click on the back button.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnTwoBack(int x, int y);

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int game_Mode_Upload_Textures_2 (SDL_Surface* loading_surface,MainGameMode * current );

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int game_Mode_Upload_Textures_1 (SDL_Surface* loading_surface,MainGameMode * current );

#endif /* GUI_GAMEMODEWIN_H_ */
