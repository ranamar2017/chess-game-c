/*
 * mainMenuWin.c
 *
 *  Created on: Sep 15, 2017
 *      Author: ranam
 */

#include <stdio.h>
#include "GUI_MenuWin.h"


/*the traget of the function is to creat a window for the main menu of the game.
 * the function return a struct MainWin, that includes all the relevant parametes for the main menu.
 */
MainWin* mainWindowCreate(){
	SDL_Surface* loading_surface = NULL;
	int success_upload ;

	MainWin * current = NULL ;
		current = (MainWin*) calloc(sizeof(MainWin), sizeof(char));
		if (current == NULL ){
		return NULL ;
		}

//	SDL_Init(SDL_INIT_VIDEO);
	current->mainWindow = SDL_CreateWindow(
	    "Chess",
	    SDL_WINDOWPOS_CENTERED,
	    SDL_WINDOWPOS_CENTERED,
	    1000,
	    650,
	    SDL_WINDOW_SHOWN
	);

	if (current->mainWindow == NULL ) {
		mainWindowDestroy(current);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}

	current->mainRenderer = SDL_CreateRenderer(current->mainWindow, -1, SDL_RENDERER_ACCELERATED);
	if (current->mainRenderer  == NULL ) {
		// In the case that the window could not be made.
		mainWindowDestroy(current);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}

	success_upload = main_menu_upload_textures_1 (loading_surface,current); // upload the textures.
	if (success_upload == 0)
		return NULL;
	return current;
}

/* the traget of the function is to free the memory of the struct and it components.
 * it get refernce for MainWin and destroy all the fields in the struct.
*/
void mainWindowDestroy(MainWin* src){
if (!src) {
	return;
}
if (src->quit_texture != NULL ) {
	SDL_DestroyTexture(src->quit_texture);
}
if (src->load_texture != NULL ) {
	SDL_DestroyTexture(src->load_texture);
}
if (src->newGame_texture != NULL ) {
	SDL_DestroyTexture(src->newGame_texture);
}
if (src->background_texture != NULL ) {
	SDL_DestroyTexture(src->background_texture);
}
if (src->mainRenderer != NULL ) {
	SDL_DestroyRenderer(src->mainRenderer);
}
if (src->mainWindow != NULL ) {
	SDL_DestroyWindow(src->mainWindow);
}
free(src);
}

/*the traget of the function is to draw the main menu on the board.
 * the function get refernce of MainWin and draw it on the window.
 */
void mainWindowDraw(MainWin* current) {
	if(current==NULL){
		return;
	}
	SDL_Rect newGameButton = {425,300,150,50};
	SDL_Rect loadGameButton = {425,375,150,50};
	SDL_Rect quitGameButton = {425,450,150,50};

    SDL_RenderClear(current->mainRenderer);
    SDL_RenderCopy(current->mainRenderer, current->background_texture, NULL, NULL);
    SDL_RenderCopy(current->mainRenderer, current->newGame_texture, NULL, &newGameButton);
    SDL_RenderCopy(current->mainRenderer, current->load_texture, NULL, &loadGameButton);
    SDL_RenderCopy(current->mainRenderer, current->quit_texture, NULL, &quitGameButton);
    SDL_RenderPresent(current->mainRenderer);
}

/* represent click on the new game button.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnNewGame(int x, int y) {
	if ((x >= 425 && x <= 575) && (y >= 300 && y <= 350)) {
		return 1;
	}
	return 0;
}

/* represent click on the load game button.
 *  * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnLoadGame(int x, int y) {
	if ((x >= 425 && x <= 575) && (y >= 375 && y <= 425)) {
		return 1;
	}
	return 0;
}

/* represent click on the quit button.
 *  * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnQuit(int x, int y) {
	if ((x >= 425 && x <= 575) && (y >= 450 && y <= 500)) {
		return 1;
	}
	return 0;
}

//the traget is to hide a window.
void mainWindowHide(MainWin* src) {
	SDL_HideWindow(src->mainWindow);
}

//the traget is to show a window.
void mainWindowShow(MainWin* src){
	SDL_ShowWindow(src->mainWindow);
}

/* the trgaet of the function is handle an event.
 * the function get refreces for MainWin and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
MAIN_MENU_EVENT mainMenuWindowHandleEvent( SDL_Event* event){
	if (!event) {
		return MAIN_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (isClickOnNewGame(event->button.x, event->button.y)) {
			return MAIN_NEW_GAME;
		}
		else if (isClickOnLoadGame(event->button.x, event->button.y)) {
			return MAIN_LOAD_GAME;
		}
		else if (isClickOnQuit(event->button.x, event->button.y))
			return MAIN_EXIT;
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return MAIN_EXIT;
		}
		break;
	default:
		return MAIN_NONE;
	}
	return MAIN_NONE;
}


/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */

int main_menu_upload_textures_1 (SDL_Surface* loading_surface,MainWin * current ){
	loading_surface = SDL_LoadBMP("./images/openBackGround.bmp");
	if (loading_surface == NULL ) {
		mainWindowDestroy(current);
		printf("couldn't create openBackGround.bmp surface\n");
		return 0;
	}
	current->background_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->background_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		mainWindowDestroy(current);
		printf("couldn't create openBackGround.bmp texture\n");
		return 0;
	}
	SDL_FreeSurface(loading_surface);
	loading_surface = SDL_LoadBMP("./images/StartChose.bmp");
	if (loading_surface == NULL ) {
		mainWindowDestroy(current);
		printf("couldn't create StartChose.bmp surface\n");
		return 0;
	}
	current->newGame_texture = SDL_CreateTextureFromSurface(current->mainRenderer,loading_surface );
	if (current->newGame_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		mainWindowDestroy(current);
		printf("couldn't create StartChose.bmp texture\n");
		return 0;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/LoadChose.bmp");
	if (loading_surface == NULL ) {
		mainWindowDestroy(current);
		printf("couldn't create LoadChose.bmp surface\n");
		return 0;
	}
	current->load_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->load_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		mainWindowDestroy(current);
		printf("couldn't create LoadChose.bmp texture\n");
		return 0;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/quit.bmp");
	if (loading_surface == NULL ) {
		mainWindowDestroy(current);
		printf("couldn't create quit.bmp surface\n");
		return 0;
	}
	current->quit_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->quit_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		mainWindowDestroy(current);
		printf("couldn't create quit.bmp texture\n");
		return 0;
	}
	SDL_FreeSurface(loading_surface);
    return 1;

}
