/*
 * loadWin.h
 *
 *  Created on: Sep 19, 2017
 *      Author: ranam
 */

#ifndef GUI_LOADWIN_H_
#define GUI_LOADWIN_H_

#include <SDL.h>
#include "CON_struct__Address_Que.h"

//the traget of the enum is to represent a situation, event, at the load.
 typedef enum {
	MAIN_LOAD_EXIT, lOAD_LOAD, LOAD_BACK,LOAD_GAME_SLOT_1,LOAD_GAME_SLOT_2,
	LOAD_GAME_SLOT_3,LOAD_GAME_SLOT_4,LOAD_GAME_SLOT_5, lOAD_INVALID_ARGUMENT,LOAD_NONE
} LOAD_EVENT;


//the traget is to hold a load.
typedef struct {
	//SDL_Window* window;
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	SDL_Texture* background_texture;
	SDL_Texture* game_slot_1_choose_texture;
	SDL_Texture* game_slot_1_not_choose_texture;
	SDL_Texture* game_slot_2_choose_texture;
	SDL_Texture* game_slot_2_not_choose_texture;
	SDL_Texture* game_slot_3_choose_texture;
	SDL_Texture* game_slot_3_not_choose_texture;
	SDL_Texture* game_slot_4_choose_texture;
	SDL_Texture* game_slot_4_not_choose_texture;
	SDL_Texture* game_slot_5_choose_texture;
	SDL_Texture* game_slot_5_not_choose_texture;
	SDL_Texture* load_texture;
	SDL_Texture* load_Not_texture;
	SDL_Texture* back_texture;
	int slot_active ;
	int slot_available;
} LoadWin;

/*the traget of the function is to creat a window for the load of the game.
 * the function return a struct LoadWin, that includes all the relevant parametes for the Load window.
 */
LoadWin* loadWindowCreate(addressQue* temp_que);

/* the traget of the function is to free the memory of the struct and it components.
 * it get refernce for LoadWin and destroy all the fields in the struct.
*/
void loadWindowDestroy(LoadWin* src);

/*the traget of the function is to draw the load window on the board.
 * the function get refernce of LoadWin and draw it on the window.
 */
void loadWindowDraw(LoadWin* current);

/* the trgaet of the function is handle an event.
 * the function get refreces for LoadWin and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
LOAD_EVENT loadWindowHandleEvent(LoadWin* src, SDL_Event* event);

/* represent click on slot 1.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnSlot1(int x, int y);


/* represent click on slot 2.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnSlot2(int x, int y);

/* represent click on slot 3.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnSlot3(int x, int y);

/* represent click on slot 4.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnSlot4(int x, int y);

/* represent click on slot 5.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnSlot5(int x, int y);

/* represent click on back.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnLoadBack(int x, int y);

/* represent click on load.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnLoadLoad(int x, int y);

//the traget is to hide a window.
void mainLoadWindowHide(LoadWin* src);

//the traget is to show a window.
void mainLoadWindowShow(LoadWin* src);

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int load_Upload_Textures_1 (SDL_Surface* loading_surface,LoadWin * current );

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int load_Upload_Textures_2 (SDL_Surface* loading_surface,LoadWin * current );

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int load_Upload_Textures_3 (SDL_Surface* loading_surface,LoadWin * current );

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int load_Upload_Textures_4 (SDL_Surface* loading_surface,LoadWin * current );


#endif /* GUI_LOADWIN_H_ */
