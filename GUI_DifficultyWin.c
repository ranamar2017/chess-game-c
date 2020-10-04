/*
 * difficulty.c
 *
 *  Created on: Sep 16, 2017
 *      Author: ranam
 */


#include <stdio.h>
#include "GUI_DifficultyWin.h"

/*the traget of the function is to creat a window for the difficulty menu of the game.
 * the function return a struct DifficultyWin, that includes all the relevant parametes for the difficulty.
 */
DifficultyWin* difficultyWindowCreate(){
	SDL_Surface* loading_surface = NULL;
	int success_upload_1, success_upload_2, success_upload_3,success_upload_4;

	DifficultyWin * current = NULL ;
	current = (DifficultyWin*) calloc(sizeof(DifficultyWin), sizeof(char));
	if (current == NULL ) {
		return NULL ;
	}


	//		SDL_Init(SDL_INIT_VIDEO);
	current->mainWindow = SDL_CreateWindow(
			"Chess",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			1000,
			650,
			SDL_WINDOW_SHOWN
	);

	current->diffi = 2;

	if (current->mainWindow == NULL ) {
		difficultyWindowDestroy (current);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}

	current->mainRenderer = SDL_CreateRenderer(current->mainWindow, -1, SDL_RENDERER_ACCELERATED);
	if (current->mainRenderer == NULL ) {
		// In the case that the window could not be made...
		difficultyWindowDestroy (current);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}

	success_upload_1 = difficulty_Upload_Textures_1  (loading_surface,current);
	if (success_upload_1 == 0)
		return NULL;
	success_upload_2 = difficulty_Upload_Textures_2  (loading_surface,current);
	if (success_upload_2 == 0)
		return NULL;
	success_upload_3 = difficulty_Upload_Textures_3  (loading_surface,current);
	if (success_upload_3 == 0)
		return NULL;
	success_upload_4 = difficulty_Upload_Textures_4  (loading_surface,current);
	if (success_upload_4 == 0)
		return NULL;
	return current;

}


/* the traget of the function is to free the memory of the struct and it components.
 *  * it get refernce for DifficultyWin and destroy all the fields in the struct.
 */
void difficultyWindowDestroy(DifficultyWin* src){
	if (!src) {
		return;
	}
	if (src->noob_choose_texture != NULL ) {
		SDL_DestroyTexture(src->noob_choose_texture);
	}
	if (src->noob_not_choose_texture != NULL ) {
		SDL_DestroyTexture(src->noob_not_choose_texture);
	}
	if (src->easy_choose_texture != NULL ) {
		SDL_DestroyTexture(src->easy_choose_texture);
	}
	if (src->easy_not_choose_texture!= NULL ) {
		SDL_DestroyTexture(src->easy_not_choose_texture);
	}
	if (src->moderate_choose_texture!= NULL ) {
		SDL_DestroyTexture(src->moderate_choose_texture);
	}
	if (src->moderate_not_choose_texture != NULL ) {
		SDL_DestroyTexture(src->moderate_not_choose_texture);
	}
	if (src->hard_choose_texture!= NULL ) {
		SDL_DestroyTexture(src->hard_choose_texture);
	}
	if (src->hard_not_choose_texture!= NULL ) {
		SDL_DestroyTexture(src->hard_not_choose_texture);
	}
	if (src->expert_not_choose_texture!= NULL ) {
		SDL_DestroyTexture(src->expert_not_choose_texture);
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




/*the traget of the function is to draw the difficulty window on the board.
 *   the function get refernce of DifficultyWin and draw it on the window.
 */
void difficultyWindowDraw(DifficultyWin* current){

	SDL_Rect BackButton = {265,140,150,50};
	SDL_Rect NoobVButton = {425,200,150,40};
	SDL_Rect NoobNVButton = {425,200,150,40};
	SDL_Rect EasyVButton = {425,275,150,40};
	SDL_Rect EasyNVButton = {425,275,150,40};
	SDL_Rect ModerateVButton = {425,350,150,40};
	SDL_Rect ModerateNVButton = {425,350,150,40};
	SDL_Rect HardVButton = {425,425,150,40};
	SDL_Rect HardNVButton = {425,425,150,40};
//	SDL_Rect ExpertNVButton = {425,500,150,40};
	SDL_Rect NextButton  = {585,140,150,50};

    SDL_RenderClear(current->mainRenderer);
    SDL_RenderCopy(current->mainRenderer, current->background_texture, NULL, NULL);
    if (current->diffi == 1){
    	SDL_RenderCopy(current->mainRenderer, current->noob_choose_texture, NULL, &NoobVButton);
    	SDL_RenderCopy(current->mainRenderer, current->easy_not_choose_texture, NULL, &EasyNVButton);
    	SDL_RenderCopy(current->mainRenderer, current->moderate_not_choose_texture, NULL, &ModerateNVButton);
    	 SDL_RenderCopy(current->mainRenderer, current->hard_not_choose_texture, NULL, &HardNVButton);
    }
    if (current->diffi == 2){
    	SDL_RenderCopy(current->mainRenderer, current->noob_not_choose_texture, NULL, &NoobNVButton);
    	SDL_RenderCopy(current->mainRenderer, current->easy_choose_texture, NULL, &EasyVButton);
    	SDL_RenderCopy(current->mainRenderer, current->moderate_not_choose_texture, NULL, &ModerateNVButton);
    	SDL_RenderCopy(current->mainRenderer, current->hard_not_choose_texture, NULL, &HardNVButton);
    }
    if (current->diffi == 3){
    	SDL_RenderCopy(current->mainRenderer, current->noob_not_choose_texture, NULL, &NoobNVButton);
    	SDL_RenderCopy(current->mainRenderer, current->easy_not_choose_texture, NULL, &EasyNVButton);
    	SDL_RenderCopy(current->mainRenderer, current->moderate_choose_texture, NULL, &ModerateVButton);
    	SDL_RenderCopy(current->mainRenderer, current->hard_not_choose_texture, NULL, &HardNVButton);
    }
    if (current->diffi == 4){
    	SDL_RenderCopy(current->mainRenderer, current->noob_not_choose_texture, NULL, &NoobNVButton);
    	SDL_RenderCopy(current->mainRenderer, current->easy_not_choose_texture, NULL, &EasyNVButton);
    	SDL_RenderCopy(current->mainRenderer, current->moderate_not_choose_texture, NULL, &ModerateNVButton);
    	SDL_RenderCopy(current->mainRenderer, current->hard_choose_texture, NULL, &HardVButton);
    }

    SDL_RenderCopy(current->mainRenderer, current->next_texture, NULL, &NextButton);
    SDL_RenderCopy(current->mainRenderer, current->back_texture, NULL, &BackButton);

    SDL_RenderPresent(current->mainRenderer);

}

//the traget is to hide a window.
void mainDifficultyWindowHide(DifficultyWin* src) {
	SDL_HideWindow(src->mainWindow);
}

//the traget is to show a window.
void mainDifficultyWindowShow(DifficultyWin* src) {
	SDL_ShowWindow(src->mainWindow);
}


/* represent click on noob.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnNoob(int x, int y) {
	if ((x >= 425 && x <= 575) && (y >= 200 && y <= 240)) {
		return 1;
	}
	return 0;
}

/* represent click on easy.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnEasy(int x, int y) {
	if ((x >= 425 && x <= 575) && (y >= 275 && y <= 315)) {
		return 1;
	}
	return 0;
}

/* represent click on moderate.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnModerate(int x, int y) {
	if ((x >= 425 && x <= 575) && (y >= 350 && y <= 390)) {
		return 1;
	}
	return 0;
}

/* represent click on hard.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnHard(int x, int y) {
	if ((x >= 425 && x <= 575) && (y >= 425 && y <= 465)) {
		return 1;
	}
	return 0;
}

/* represent click on back.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnDifficultyBack(int x, int y) {
	if ((x >= 265 && x <= 415) && (y >= 140 && y <= 190)) {
		return 1;
	}
	return 0;
}

/* represent click on next.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnDifficultyNext(int x, int y) {
	if ((x >= 585 && x <= 735) && (y >= 140 && y <= 190)) {
		return 1;
	}
	return 0;
}

/* the trgaet of the function is handle an event.
 * the function get refreces for DifficultyWin and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
DIFFICULTY_EVENT difficultyWindowHandleEvent(DifficultyWin* src, SDL_Event* event){
	if (!event) {
		return DIFFICULTY_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (isClickOnDifficultyNext(event->button.x, event->button.y)) {
				return DIFFICULTY_NEXT;
		}
		else if (isClickOnNoob(event->button.x, event->button.y)) {
			    src->diffi = 1;
				return DIFFICULTY_NOOB;
			}

		else if (isClickOnEasy(event->button.x, event->button.y)) {
				src->diffi = 2;
				return DIFFICULTY_EASY;
			}
		else if (isClickOnModerate(event->button.x, event->button.y)) {
			    src->diffi = 3;
				return DIFFICULTY_MOODERATE;
			}

		else if (isClickOnHard(event->button.x, event->button.y)) {
				src->diffi = 4;
				return DIFFICULTY_HARD;
			}


		else if (isClickOnDifficultyBack(event->button.x, event->button.y))
			return DIFFICULTY_BACK;
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return MAIN_DIFFICULTY_EXIT;
		}
		break;
	default:
		return DIFFICULTY_NONE;
	}
	return DIFFICULTY_NONE;
 }

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int difficulty_Upload_Textures_1 (SDL_Surface* loading_surface,DifficultyWin * current ){

	loading_surface = SDL_LoadBMP("./images/Difficulty.bmp");
	if (loading_surface == NULL ) {
		difficultyWindowDestroy (current);
		printf("couldn't create Difficulty.bmp surface\n");
		return 0 ;
	}
	current->background_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->background_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		difficultyWindowDestroy (current);
		printf("couldn't create Difficulty.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/NoobChose.bmp");
	if (loading_surface == NULL ) {
		difficultyWindowDestroy (current);
		printf("couldn't create NoobChose.bmp surface\n");
		return 0 ;
	}
	current->noob_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer,loading_surface );
	if (current->noob_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		difficultyWindowDestroy (current);
		printf("couldn't create NoobChose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/NoobNot.bmp");
	if (loading_surface == NULL ) {
		difficultyWindowDestroy (current);
		printf("couldn't create NoobNot.bmp surface\n");
		return 0 ;
	}
	current->noob_not_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer,loading_surface );
	if (current->noob_not_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		difficultyWindowDestroy (current);
		printf("couldn't create NoobNot.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/EasyChose.bmp");
	if (loading_surface == NULL ) {
		difficultyWindowDestroy (current);
		printf("couldn't create EasyChose.bmp surface\n");
		return 0 ;
	}
	current->easy_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->easy_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		difficultyWindowDestroy (current);
		printf("couldn't create EasyChose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	return 1;
}

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int difficulty_Upload_Textures_2 (SDL_Surface* loading_surface,DifficultyWin * current ){

	loading_surface = SDL_LoadBMP("./images/EasyNot.bmp");
	if (loading_surface == NULL ) {
		difficultyWindowDestroy (current);
		printf("couldn't create EasyNot.bmp surface\n");
		return 0 ;
	}
	current->easy_not_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->easy_not_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		difficultyWindowDestroy (current);
		printf("couldn't create  EasyNot.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/ModerateChose.bmp");
	if (loading_surface == NULL ) {
		difficultyWindowDestroy (current);
		printf("couldn't create ModerateChose.bmp surface\n");
		return 0 ;
	}
	current->moderate_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->moderate_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		difficultyWindowDestroy (current);
		printf("couldn't create  ModerateChose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/ModerateNot.bmp");
	if (loading_surface == NULL ) {
		difficultyWindowDestroy (current);
		printf("couldn't create ModerateNot.bmp surface\n");
		return 0 ;
	}
	current->moderate_not_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->moderate_not_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		difficultyWindowDestroy (current);
		printf("couldn't create  ModerateNot.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	return 1;

}

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int difficulty_Upload_Textures_3 (SDL_Surface* loading_surface,DifficultyWin * current ){

	loading_surface = SDL_LoadBMP("./images/HardChose.bmp");
	if (loading_surface == NULL ) {
		difficultyWindowDestroy (current);
		printf("couldn't create HardChose.bmp surface\n");
		return 0 ;
	}
	current->hard_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->hard_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		difficultyWindowDestroy (current);
		printf("couldn't create  HardChose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/HardNot.bmp");
	if (loading_surface == NULL ) {
		difficultyWindowDestroy (current);
		printf("couldn't create HardNot.bmp surface\n");
		return 0 ;
	}
	current->hard_not_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->hard_not_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		difficultyWindowDestroy (current);
		printf("couldn't create  HardNot.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/ExpertNot.bmp");
	if (loading_surface == NULL ) {
		difficultyWindowDestroy (current);
		printf("couldn't create Expert.bmp surface\n");
		return 0 ;
	}
	current->expert_not_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->expert_not_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		difficultyWindowDestroy (current);
		printf("couldn't create  Expert.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	return 1;

}

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int difficulty_Upload_Textures_4 (SDL_Surface* loading_surface,DifficultyWin * current ){

	loading_surface = SDL_LoadBMP("./images/NextChose.bmp");
	if (loading_surface == NULL ) {
		difficultyWindowDestroy (current);
		printf("couldn't create NextChose.bmp surface\n");
		return 0 ;
	}
	current->next_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->next_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		difficultyWindowDestroy (current);
		printf("couldn't create  NextChose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/BackChose.bmp");
	if (loading_surface == NULL ) {
		difficultyWindowDestroy (current);
		printf("couldn't create BackChose.bmp surface\n");
		return 0 ;
	}
	current->back_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->back_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		difficultyWindowDestroy (current);
		printf("couldn't create  BackChose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	return 1;

}


