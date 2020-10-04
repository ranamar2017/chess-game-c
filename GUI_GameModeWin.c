/*
 * mainGameMode.c
 *
 *  Created on: Sep 15, 2017
 *      Author: ranam
 */
#include <stdio.h>
#include "GUI_GameModeWin.h"

/*the traget of the function is to creat a window for the game mode window.
 * the function return a struct MainGameMode, that includes all the relevant parametes for the main menu.
 */
MainGameMode* mainGameModeWindowCreate(){
	SDL_Surface* loading_surface = NULL;
	int success_upload_1, success_upload_2 ;


	MainGameMode * current = NULL ;
	current = (MainGameMode*) calloc(sizeof(MainGameMode), sizeof(char));
	if (current == NULL ) {
		return NULL ;
	}

	current->two_players = 0;
	current->next_button = 1;

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
		mainGameModeWindowDestroy (current);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}

	current->mainRenderer = SDL_CreateRenderer(current->mainWindow, -1, SDL_RENDERER_ACCELERATED);
	if (current->mainRenderer == NULL ) {
		mainGameModeWindowDestroy (current);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	success_upload_1 = game_Mode_Upload_Textures_1 (loading_surface,current);
	if (success_upload_1 == 0)
		return NULL;
	success_upload_2 = game_Mode_Upload_Textures_2 (loading_surface,current);
	if (success_upload_2 == 0)
		return NULL;

	return current;
}

/* the traget of the function is to free the memory of the struct and it components.
 * it get refernce for MainGameMode and destroy all the fields in the struct.
*/
void mainGameModeWindowDestroy(MainGameMode* src){
	if (!src) {
		return;
	}
	if (src->one_choose_texture != NULL ) {
		SDL_DestroyTexture(src->one_choose_texture);
	}
	if (src->one_not_choose_texture != NULL ) {
		SDL_DestroyTexture(src->one_not_choose_texture);
	}
	if (src->two_choose_texture != NULL ) {
		SDL_DestroyTexture(src->two_choose_texture);
	}
	if (src->two_not_choose_texture!= NULL ) {
		SDL_DestroyTexture(src->two_not_choose_texture);
	}
	if (src->start_texture!= NULL ) {
		SDL_DestroyTexture(src->start_texture);
	}
	if (src->next_texture!= NULL ) {
		SDL_DestroyTexture(src->next_texture);
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

/*the traget of the function is to draw the game mode on the board.
 * the function get refernce of MainGameMode and draw it on the window.
 */
void mainGameModeWindowDraw(MainGameMode* current) {
	SDL_Rect OnePlayerVButton = {265,170,150,50};
	SDL_Rect OnePlayerNVButton = {265,170,150,50};
	SDL_Rect StartButton = {425,325,150,50};
	SDL_Rect NextButton  = {425,325,150,50};
	SDL_Rect TwoPlayerVButton = {585,170,150,50};
	SDL_Rect TwoPlayerNVButton = {585,170,150,50};
	SDL_Rect BackButton = {425,425,150,50};

    SDL_RenderClear(current->mainRenderer);
    SDL_RenderCopy(current->mainRenderer, current->background_texture, NULL, NULL);
    if (current->two_players == 0){
    	SDL_RenderCopy(current->mainRenderer, current->one_choose_texture, NULL, &OnePlayerVButton);
    	SDL_RenderCopy(current->mainRenderer, current->two_not_choose_texture, NULL, &TwoPlayerNVButton);
    }
    else{
    	SDL_RenderCopy(current->mainRenderer, current->two_choose_texture, NULL, &TwoPlayerVButton);
    	SDL_RenderCopy(current->mainRenderer, current->one_not_choose_texture, NULL, &OnePlayerNVButton);
    }
    if (current->next_button == 1){
    	SDL_RenderCopy(current->mainRenderer, current->next_texture, NULL, &NextButton);
    }
    else{
        SDL_RenderCopy(current->mainRenderer, current->start_texture, NULL, &StartButton);
    }
    SDL_RenderCopy(current->mainRenderer, current->back_texture, NULL, &BackButton);

    SDL_RenderPresent(current->mainRenderer);
}


//the traget is to hide a window.
void mainGameModeWindowHide(MainGameMode* src) {
	SDL_HideWindow(src->mainWindow);
}

//the traget is to show a window.
void mainGameModeWindowShow(MainGameMode* src) {
	SDL_ShowWindow(src->mainWindow);
}

/* represent click on the start button.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnStart(int x, int y) {
	if ((x >= 425 && x <= 575) && (y >= 325 && y <= 375)) {
		return 1;
	}
	return 0;
}

/* represent click on the next button.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnNext(int x, int y) {
	if ((x >= 425 && x <= 575) && (y >= 325 && y <= 375)) {
		return 1;
	}
	return 0;
}

/* represent click on the one player button.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnOnePlayer(int x, int y) {
	if ((x >= 265 && x <= 415) && (y >= 170 && y <= 220)) {
		return 1;
	}
	return 0;
}

/* represent click on the two player button.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnTwoPlayer(int x, int y) {
	if ((x >= 585 && x <= 735) && (y >= 170 && y <= 220)) {
		return 1;
	}
	return 0;
}

/* represent click on the back button.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnBack(int x, int y) {
	if ((x >= 425 && x <= 575) && (y >= 425 && y <= 475)) {
		return 1;
	}
	return 0;
}

/* the trgaet of the function is handle an event.
 * the function get refreces for MainGameMode and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
MAIN_GAME_MODE_EVENT mainGameModeWindowHandleEvent(MainGameMode* src, SDL_Event* event){
	if (!event) {
		return MAIN_GAME_MODE_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (isClickOnStart(event->button.x, event->button.y)) {
			if (src->next_button == 0)
				return MAIN_GAME_MODE_START;
			else
				return MAIN_GAME_MODE_NEXT;
		}
		else if (isClickOnOnePlayer(event->button.x, event->button.y)) {
			    src->two_players = 0;
			    src->next_button = 1;
				return ONE_PLAYER;
			}

		else if (isClickOnTwoPlayer(event->button.x, event->button.y)) {
			    src->two_players = 1;
			    src->next_button = 0;
				return TWO_PLAYERS;
			}

		else if (isClickOnBack(event->button.x, event->button.y))
			return MAIN_GAME_MODE_BACK;
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return MAIN_GAME_MODE_EXIT;
		}
		break;
	default:
		return MAIN_GAME_MODE_NONE;
	}
	return MAIN_GAME_MODE_NONE;
 }

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int game_Mode_Upload_Textures_1 (SDL_Surface* loading_surface,MainGameMode * current ){
	loading_surface = SDL_LoadBMP("./images/GameMode.bmp");
	if (loading_surface == NULL ) {
		mainGameModeWindowDestroy (current);
		printf("couldn't create GameMode.bmp surface\n");
		return 0 ;
	}
	current->background_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->background_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		mainGameModeWindowDestroy (current);
		printf("couldn't create GameMode.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/OnePlayerChose.bmp");
	if (loading_surface == NULL ) {
		mainGameModeWindowDestroy (current);
		printf("couldn't create OnePlayerChose.bmp surface\n");
		return 0 ;
	}
	current->one_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer,loading_surface );
	if (current->one_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		mainGameModeWindowDestroy (current);
		printf("couldn't create OnePlayerChose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/OnePlayerNot.bmp");
	if (loading_surface == NULL ) {
		mainGameModeWindowDestroy (current);
		printf("couldn't create OnePlayerNot.bmp surface\n");
		return 0 ;
	}
	current->one_not_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer,loading_surface );
	if (current->one_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		mainGameModeWindowDestroy (current);
		printf("couldn't create OnePlayerNot.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	loading_surface = SDL_LoadBMP("./images/TwoPlayersChose.bmp");
	if (loading_surface == NULL ) {
		mainGameModeWindowDestroy (current);
		printf("couldn't create TwoPlayersChose.bmp surface\n");
		return 0 ;
	}
	current->two_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->two_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		mainGameModeWindowDestroy (current);
		printf("couldn't create TwoPlayersChose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	return 1;
}

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int game_Mode_Upload_Textures_2 (SDL_Surface* loading_surface,MainGameMode * current ){

	loading_surface = SDL_LoadBMP("./images/TwoPlayersNot.bmp");
	if (loading_surface == NULL ) {
		mainGameModeWindowDestroy (current);
		printf("couldn't create TwoPlayersNot.bmp surface\n");
		return 0 ;
	}
	current->two_not_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->two_not_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		mainGameModeWindowDestroy (current);
		printf("couldn't create  TwoPlayersNot.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/StartChose.bmp");
	if (loading_surface == NULL ) {
		mainGameModeWindowDestroy (current);
		printf("couldn't create StartChose.bmp surface\n");
		return 0 ;
	}
	current->start_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->start_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		mainGameModeWindowDestroy (current);
		printf("couldn't create  StartChose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/TwoPlayersNot.bmp");
	if (loading_surface == NULL ) {
		mainGameModeWindowDestroy (current);
		printf("couldn't create TwoPlayersNot.bmp surface\n");
		return 0 ;
	}
	current->two_not_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->two_not_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		mainGameModeWindowDestroy (current);
		printf("couldn't create  TwoPlayersNot.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/NextChose.bmp");
	if (loading_surface == NULL ) {
		mainGameModeWindowDestroy (current);
		printf("couldn't create NextChose.bmp surface\n");
		return 0 ;
	}
	current->next_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->next_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		mainGameModeWindowDestroy (current);
		printf("couldn't create  NextChose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/BackChose.bmp");
	if (loading_surface == NULL ) {
		mainGameModeWindowDestroy (current);
		printf("couldn't create BackChose.bmp surface\n");
		return 0 ;
	}
	current->back_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->back_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		mainGameModeWindowDestroy (current);
		printf("couldn't create  BackChose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	return 1;
}
