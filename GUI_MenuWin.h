/*
 * mainMenuWin.h
 *
 *  Created on: Sep 15, 2017
 *      Author: ranam
 */

#ifndef GUI_MENUWIN_H_
#define GUI_MENUWIN_H_

#include <SDL.h>
//the traget of the enum is to represent a situation, event, at the main_menu.
typedef enum {
	MAIN_EXIT, MAIN_NEW_GAME,MAIN_LOAD_GAME, MAIN_INVALID_ARGUMENT,MAIN_NONE
} MAIN_MENU_EVENT;

//the traget is to hold a main_menu.
typedef struct {
	//SDL_Window* window;
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	SDL_Texture* background_texture;
	SDL_Texture* newGame_texture;
	SDL_Texture* load_texture;
	SDL_Texture* quit_texture;
} MainWin;

/*the traget of the function is to creat a window for the main menu of the game.
 * the function return a struct MainWin, that includes all the relevant parametes for the main menu.
 */
MainWin* mainWindowCreate();

/* the traget of the function is to free the memory of the struct and it components.
 * it get refernce for MainWin and destroy all the fields in the struct.
*/
void mainWindowDestroy(MainWin* src);


/*the traget of the function is to draw the main menu on the board.
 * the function get refernce of MainWin and draw it on the window.
 */
void mainWindowDraw(MainWin* current) ;


/* represent click on the new game button.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnNewGame(int x, int y);


/* represent click on the load game button.
 *  * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnLoadGame(int x, int y);


/* represent click on the quit button.
 *  * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnQuit(int x, int y);


//the traget is to hide a window.
void mainWindowHide(MainWin* src);


//the traget is to show a window.
void mainWindowShow(MainWin* src);


/* the trgaet of the function is handle an event.
 * the function get refreces for MainWin and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
MAIN_MENU_EVENT mainMenuWindowHandleEvent( SDL_Event* event);


/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int main_menu_upload_textures_1 (SDL_Surface* loading_surface,MainWin * current );

#endif /* GUI_MENUWIN_H_ */
