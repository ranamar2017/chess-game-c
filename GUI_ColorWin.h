/*
 * colorWin.h
 *
 *  Created on: Sep 16, 2017
 *      Author: ranam
 */

#ifndef GUI_COLORWIN_H_
#define GUI_COLORWIN_H_

#include <SDL.h>
#include <stdbool.h>

//the traget of the enum is to represent a situation, event, at the color menu.
 typedef enum {
	MAIN_COLOR_EXIT, COLOR_START,COLOR_BACK,
	COLOR_WHITE,COLOR_BLACK, COLOR_INVALID_ARGUMENT,COLOR_NONE
} COLOR_EVENT;

//the traget is to hold a color.
typedef struct {
	//SDL_Window* window;
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	SDL_Texture* background_texture;
	SDL_Texture* black_choose_texture;
	SDL_Texture* black_not_choose_texture;
	SDL_Texture* white_choose_texture;
	SDL_Texture* white_not_choose_texture;
	SDL_Texture* start_texture;
	SDL_Texture* back_texture;
	bool color ; //black: 0, white:1
} ColorWin;

/*the traget of the function is to creat a window for the color menu of the game.
 *  the function return a struct ColorWin, that includes all the relevant parametes for the color menu.
 */
ColorWin* colorWindowCreate();

/* the traget of the function is to free the memory of the struct and it components.
 * it get refernce for ColorWin and destroy all the fields in the struct.
*/
void colorWindowDestroy(ColorWin* src);

/*the traget of the function is to draw the color menu on the board.
 * the function get refernce of ColorWin and draw it on the window.
 */
void colorWindowDraw(ColorWin* current);


//the traget is to hide a window.
void mainColorWindowHide(ColorWin* src);

//the traget is to show a window.
void mainColorWindowShow(ColorWin* src);

/* represent click on back.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnColorBack(int x, int y);

/* represent click on start.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnColorStart(int x, int y);

/* represent click on black.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnBlack(int x, int y);

/* represent click on white.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnWhite(int x, int y);

/* the trgaet of the function is handle an event.
 * the function get refreces for ColorWin and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
COLOR_EVENT colorWindowHandleEvent(ColorWin* src, SDL_Event* event);

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int color_Upload_Textures_1 (SDL_Surface* loading_surface,ColorWin * current );

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int color_Upload_Textures_2 (SDL_Surface* loading_surface,ColorWin * current );

#endif /* GUI_COLORWIN_H_ */
