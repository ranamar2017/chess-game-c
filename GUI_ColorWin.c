/*
 * colorWin.c
 *
 *  Created on: Sep 16, 2017
 *      Author: ranam
 */


#include <stdio.h>
#include "GUI_ColorWin.h"

/*the traget of the function is to creat a window for the color menu of the game.
 *  the function return a struct ColorWin, that includes all the relevant parametes for the color menu.
 */
ColorWin* colorWindowCreate(){
	SDL_Surface* loading_surface = NULL;
	int success_upload_1, success_upload_2;

	ColorWin * current = NULL ;
	current = (ColorWin*) calloc(sizeof(ColorWin), sizeof(char));
	if (current == NULL ) {
		return NULL ;
	}
	SDL_Init(SDL_INIT_VIDEO);
	current->mainWindow = SDL_CreateWindow(
			"Chess",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			1000,
			650,
			SDL_WINDOW_SHOWN
	);

	current->color = 1;

	if (current->mainWindow == NULL ) {
		colorWindowDestroy (current);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}

	current->mainRenderer = SDL_CreateRenderer(current->mainWindow, -1, SDL_RENDERER_ACCELERATED);
	if (current->mainRenderer == NULL ) {
		// In the case that the window could not be made...
		colorWindowDestroy (current);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}

	success_upload_1 = color_Upload_Textures_1  (loading_surface,current);
	if (success_upload_1 == 0)
		return NULL;
	success_upload_2 = color_Upload_Textures_2  (loading_surface,current);
	if (success_upload_2 == 0)
		return NULL;
	return current;

}

/* the traget of the function is to free the memory of the struct and it components.
 * it get refernce for ColorWin and destroy all the fields in the struct.
*/
void colorWindowDestroy(ColorWin* src){
	if (!src) {
		return;
	}
	if (src->black_choose_texture != NULL ) {
		SDL_DestroyTexture(src->black_choose_texture);
	}
	if (src->black_not_choose_texture != NULL ) {
		SDL_DestroyTexture(src->black_not_choose_texture);
	}
	if (src->white_choose_texture != NULL ) {
		SDL_DestroyTexture(src->white_choose_texture);
	}
	if (src->white_not_choose_texture!= NULL ) {
		SDL_DestroyTexture(src->white_not_choose_texture);
	}
	if (src->start_texture!= NULL ) {
		SDL_DestroyTexture(src->start_texture);
	}
	if (src->back_texture!= NULL ) {
		SDL_DestroyTexture(src->back_texture);
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

/*the traget of the function is to draw the color menu on the board.
 * the function get refernce of ColorWin and draw it on the window.
 */
void colorWindowDraw(ColorWin* current){


	SDL_Rect BackButton = {425,425,150,50};
	SDL_Rect StartButton  = {425,275,150,50};
	SDL_Rect black_choose_texture = {265,140,150,50};
	SDL_Rect black_not_choose_texture = {265,140,150,50};
	SDL_Rect white_choose_texture = {585,140,150,50};
	SDL_Rect white_not_choose_texture = {585,140,150,50};

    SDL_RenderClear(current->mainRenderer);

    SDL_RenderCopy(current->mainRenderer, current->background_texture, NULL, NULL);
    if (current->color == 0){
    	SDL_RenderCopy(current->mainRenderer, current->black_choose_texture, NULL, &black_choose_texture);
    	SDL_RenderCopy(current->mainRenderer, current->white_not_choose_texture, NULL, &white_not_choose_texture);
    }
    else{
    	SDL_RenderCopy(current->mainRenderer, current->black_not_choose_texture, NULL, &black_not_choose_texture);
    	SDL_RenderCopy(current->mainRenderer, current->white_choose_texture, NULL, &white_choose_texture);
    }
    SDL_RenderCopy(current->mainRenderer, current->start_texture, NULL, &StartButton);
    SDL_RenderCopy(current->mainRenderer, current->back_texture, NULL, &BackButton);

    SDL_RenderPresent(current->mainRenderer);
}

//the traget is to hide a window.
void mainColorWindowHide(ColorWin* src) {
	SDL_HideWindow(src->mainWindow);
}

//the traget is to show a window.
void mainColorWindowShow(ColorWin* src) {
	SDL_ShowWindow(src->mainWindow);
}

/* represent click on back.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnColorBack(int x, int y) {
	if ((x >= 425 && x <= 575) && (y >= 425 && y <= 475)) {
		return 1;
	}
	return 0;
}

/* represent click on start.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnColorStart(int x, int y) {
	if ((x >= 425 && x <= 575) && (y >= 275 && y <= 325)) {
		return 1;
	}
	return 0;
}

/* represent click on black.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnBlack(int x, int y) {
	if ((x >= 265 && x <= 415) && (y >= 140 && y <= 190)) {
		return 1;
	}
	return 0;
}

/* represent click on white.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnWhite(int x, int y) {
	if ((x >= 585 && x <= 735) && (y >= 140 && y <= 190)) {
		return 1;
	}
	return 0;
}

/* the trgaet of the function is handle an event.
 * the function get refreces for ColorWin and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
COLOR_EVENT colorWindowHandleEvent(ColorWin* src, SDL_Event* event){
	if (!event) {
		return COLOR_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (isClickOnColorStart(event->button.x, event->button.y)) {
				return COLOR_START;
		}
		else if (isClickOnBlack(event->button.x, event->button.y)) {
			    src->color = 0;
				return COLOR_BLACK;
			}

		else if (isClickOnWhite(event->button.x, event->button.y)) {
				src->color = 1;
				return COLOR_WHITE;
			}
		else if (isClickOnColorBack(event->button.x, event->button.y))
			return COLOR_BACK;
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return MAIN_COLOR_EXIT;
		}
		break;
	default:
		return COLOR_NONE;
	}
	return COLOR_NONE;
 }

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int color_Upload_Textures_1 (SDL_Surface* loading_surface,ColorWin * current ){

	loading_surface = SDL_LoadBMP("./images/SelectYourColor.bmp");
	if (loading_surface == NULL ) {
		colorWindowDestroy (current);
		printf("couldn't create SelectYourColor.bmp surface\n");
		return 0 ;
	}
	current->background_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->background_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		colorWindowDestroy (current);
		printf("couldn't create SelectYourColor.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/BlackChose.bmp");
	if (loading_surface == NULL ) {
		colorWindowDestroy (current);
		printf("couldn't create BlackChose.bmp surface\n");
		return 0 ;
	}
	current->black_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer,loading_surface );
	if (current->black_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		colorWindowDestroy (current);
		printf("couldn't create BlackChose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/BlackNot.bmp");
	if (loading_surface == NULL ) {
		colorWindowDestroy (current);
		printf("couldn't create BlackNot.bmp surface\n");
		return 0 ;
	}
	current->black_not_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer,loading_surface );
	if (current->black_not_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		colorWindowDestroy (current);
		printf("couldn't create BlackNot.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/WhiteChose.bmp");
	if (loading_surface == NULL ) {
		colorWindowDestroy (current);
		printf("couldn't create WhiteChose.bmp surface\n");
		return 0 ;
	}
	current->white_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->white_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		colorWindowDestroy (current);
		printf("couldn't create WhiteChose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	return 1;

}

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int color_Upload_Textures_2 (SDL_Surface* loading_surface,ColorWin * current ){

	loading_surface = SDL_LoadBMP("./images/WhiteNot.bmp");
	if (loading_surface == NULL ) {
		colorWindowDestroy (current);
		printf("couldn't create WhiteNot.bmp surface\n");
		return 0 ;
	}
	current->white_not_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->white_not_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		colorWindowDestroy (current);
		printf("couldn't create  WhiteNot.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/StartChose.bmp");
	if (loading_surface == NULL ) {
		colorWindowDestroy (current);
		printf("couldn't create StartChose.bmp surface\n");
		return 0 ;
	}
	current->start_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->start_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		colorWindowDestroy (current);
		printf("couldn't create  StartChose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/BackChose.bmp");
	if (loading_surface == NULL ) {
		colorWindowDestroy (current);
		printf("couldn't create BackChose.bmp surface\n");
		return 0 ;
	}
	current->back_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->back_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		colorWindowDestroy (current);
		printf("couldn't create  BackChose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	return 1;
}
