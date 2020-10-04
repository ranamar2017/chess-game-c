
#include "GUI_LoadWin.h"

#include "CON_struct__Address_Que.h"

#include <stdio.h>

/*the traget of the function is to creat a window for the load of the game.
 * the function return a struct LoadWin, that includes all the relevant parametes for the Load window.
 */
LoadWin* loadWindowCreate(addressQue* temp_que){
	int success_upload_1, success_upload_2, success_upload_3,success_upload_4 ;
	SDL_Surface* loading_surface = NULL;
	LoadWin * current = NULL ;
		current = (LoadWin*) calloc(sizeof(LoadWin), sizeof(char));
		if (current == NULL ){
			return NULL ;
		}



		current->slot_active = 0;
		current->slot_available = temp_que->used_size;

		current->mainWindow = SDL_CreateWindow(
		    "Chess",
		    SDL_WINDOWPOS_CENTERED,
		    SDL_WINDOWPOS_CENTERED,
		    1000,
		    650,
		    SDL_WINDOW_SHOWN
		);

		if (current->mainWindow == NULL ) {
			loadWindowDestroy(current);
			printf("Could not create window: %s\n", SDL_GetError());
			return NULL ;
		}

		current->mainRenderer = SDL_CreateRenderer(current->mainWindow, -1, SDL_RENDERER_ACCELERATED);
		if (current->mainRenderer == NULL ) {
			// In the case that the window could not be made.
			loadWindowDestroy(current);
			printf("Could not create window: %s\n", SDL_GetError());
			return NULL ;
		}
		success_upload_1 = load_Upload_Textures_1  (loading_surface,current);
		if (success_upload_1 == 0)
			return NULL;
		success_upload_2 = load_Upload_Textures_2  (loading_surface,current);
		if (success_upload_2 == 0)
			return NULL;
		success_upload_3 = load_Upload_Textures_3  (loading_surface,current);
		if (success_upload_3 == 0)
			return NULL;
		success_upload_4 = load_Upload_Textures_4  (loading_surface,current);
		if (success_upload_4== 0)
			return NULL;

		return current;
}








/* the traget of the function is to free the memory of the struct and it components.
 * it get refernce for LoadWin and destroy all the fields in the struct.
*/
void loadWindowDestroy(LoadWin* src){
	if (!src) {
		return;
	}
	if (src->game_slot_1_not_choose_texture != NULL ) {
		SDL_DestroyTexture(src->game_slot_1_not_choose_texture);
	}
	if (src->game_slot_1_not_choose_texture!= NULL ) {
		SDL_DestroyTexture(src->game_slot_1_not_choose_texture);
	}
	if (src->game_slot_2_choose_texture != NULL ) {
		SDL_DestroyTexture(src->game_slot_2_choose_texture);
	}
	if (src->game_slot_2_not_choose_texture!= NULL ) {
		SDL_DestroyTexture(src->game_slot_2_not_choose_texture);
	}
	if (src->game_slot_3_choose_texture!= NULL ) {
		SDL_DestroyTexture(src->game_slot_3_choose_texture);
	}
	if (src->game_slot_3_not_choose_texture != NULL ) {
		SDL_DestroyTexture(src->game_slot_3_not_choose_texture);
	}
	if (src->game_slot_4_choose_texture!= NULL ) {
		SDL_DestroyTexture(src->game_slot_4_choose_texture);
	}
	if (src->game_slot_4_not_choose_texture!= NULL ) {
		SDL_DestroyTexture(src->game_slot_4_not_choose_texture);
	}
	if (src->game_slot_5_not_choose_texture!= NULL ) {
		SDL_DestroyTexture(src->game_slot_5_not_choose_texture);
	}
	if (src->game_slot_5_choose_texture!= NULL ) {
		SDL_DestroyTexture(src->game_slot_5_choose_texture);
	}
	if (src->load_texture!= NULL ) {
		SDL_DestroyTexture(src->load_texture);
	}
	if (src->load_Not_texture!= NULL ) {
		SDL_DestroyTexture(src->load_Not_texture);
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

/*the traget of the function is to draw the load window on the board.
 * the function get refernce of LoadWin and draw it on the window.
 */
void loadWindowDraw(LoadWin* current){

	SDL_Rect BackButton = {265,140,150,50};
	SDL_Rect Slot1VButton = {425,200,150,40};
	SDL_Rect Slot1NVButton = {425,200,150,40};
	SDL_Rect Slot2VButton = {425,275,150,40};
	SDL_Rect Slot2NVButton = {425,275,150,40};
	SDL_Rect Slot3VButton = {425,350,150,40};
	SDL_Rect Slot3NVButton = {425,350,150,40};
	SDL_Rect Slot4VButton = {425,425,150,40};
	SDL_Rect Slot4VNButton = {425,425,150,40};
	SDL_Rect Slot5VButton = {425,500,150,40};
	SDL_Rect Slot5NVButton = {425,500,150,40};
	SDL_Rect LoadButton  = {585,140,150,50};

    SDL_RenderClear(current->mainRenderer);
    SDL_RenderCopy(current->mainRenderer, current->background_texture, NULL, NULL);
    switch (current->slot_available){
    case 1:
    	SDL_RenderCopy(current->mainRenderer, current->game_slot_1_not_choose_texture, NULL, &Slot1NVButton); break;
    case 2:
    	SDL_RenderCopy(current->mainRenderer, current->game_slot_1_not_choose_texture, NULL, &Slot1NVButton);
    	SDL_RenderCopy(current->mainRenderer, current->game_slot_2_not_choose_texture, NULL, &Slot2NVButton); break;
    case 3:
    	SDL_RenderCopy(current->mainRenderer, current->game_slot_1_not_choose_texture, NULL, &Slot1NVButton);
    	SDL_RenderCopy(current->mainRenderer, current->game_slot_2_not_choose_texture, NULL, &Slot2NVButton);
    	SDL_RenderCopy(current->mainRenderer, current->game_slot_3_not_choose_texture, NULL, &Slot3NVButton); break;
    case 4:
    	SDL_RenderCopy(current->mainRenderer, current->game_slot_1_not_choose_texture, NULL, &Slot1NVButton);
        SDL_RenderCopy(current->mainRenderer, current->game_slot_2_not_choose_texture, NULL, &Slot2NVButton);
        SDL_RenderCopy(current->mainRenderer, current->game_slot_3_not_choose_texture, NULL, &Slot3NVButton);
        SDL_RenderCopy(current->mainRenderer, current->game_slot_4_not_choose_texture, NULL, &Slot4VNButton);break;
    case 5:
    	SDL_RenderCopy(current->mainRenderer, current->game_slot_1_not_choose_texture, NULL, &Slot1NVButton);
    	SDL_RenderCopy(current->mainRenderer, current->game_slot_2_not_choose_texture, NULL, &Slot2NVButton);
    	SDL_RenderCopy(current->mainRenderer, current->game_slot_3_not_choose_texture, NULL, &Slot3NVButton);
        SDL_RenderCopy(current->mainRenderer, current->game_slot_4_not_choose_texture, NULL, &Slot4VNButton);
    	SDL_RenderCopy(current->mainRenderer, current->game_slot_5_not_choose_texture, NULL, &Slot5NVButton);break;
    }

    switch (current->slot_active){
        case 1:
        	SDL_RenderCopy(current->mainRenderer, current->game_slot_1_choose_texture, NULL, &Slot1VButton); break;
        case 2:
        	SDL_RenderCopy(current->mainRenderer, current->game_slot_2_choose_texture, NULL, &Slot2VButton); break;
        case 3:
        	SDL_RenderCopy(current->mainRenderer, current->game_slot_3_choose_texture, NULL, &Slot3VButton); break;
        case 4:
            SDL_RenderCopy(current->mainRenderer, current->game_slot_4_choose_texture, NULL, &Slot4VButton);break;
        case 5:
            SDL_RenderCopy(current->mainRenderer, current->game_slot_5_choose_texture, NULL, &Slot5VButton );break;
        }

    if (current->slot_active == 0)
    	SDL_RenderCopy(current->mainRenderer, current->load_Not_texture, NULL, &LoadButton);
    else
    	SDL_RenderCopy(current->mainRenderer, current->load_texture, NULL, &LoadButton);

    SDL_RenderCopy(current->mainRenderer, current->back_texture, NULL, &BackButton);
    SDL_RenderPresent(current->mainRenderer);
}




//the traget is to hide a window.
void mainLoadWindowHide(LoadWin* src) {
	SDL_HideWindow(src->mainWindow);
}

//the traget is to show a window.
void mainLoadWindowShow(LoadWin* src) {
	SDL_ShowWindow(src->mainWindow);
}



/* represent click on slot 1.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnSlot1(int x, int y) {
	if ((x >= 425 && x <= 575) && (y >= 200 && y <= 240)) {
		return 1;
	}
	return 0;
}

/* represent click on slot 2.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnSlot2(int x, int y) {
	if ((x >= 425 && x <= 575) && (y >= 275 && y <= 315)) {
		return 1;
	}
	return 0;
}

/* represent click on slot 3.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnSlot3(int x, int y) {
	if ((x >= 425 && x <= 575) && (y >= 350 && y <= 390)) {
		return 1;
	}
	return 0;
}

/* represent click on slot 4.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnSlot4(int x, int y) {
	if ((x >= 425 && x <= 575) && (y >= 425 && y <= 465)) {
		return 1;
	}
	return 0;
}

/* represent click on slot 5.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnSlot5(int x, int y) {
	if ((x >= 425 && x <= 575) && (y >= 500 && y <= 540)) {
		return 1;
	}
	return 0;
}

/* represent click on back.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnLoadBack(int x, int y) {
	if ((x >= 265 && x <= 415) && (y >= 140 && y <= 190)) {
		return 1;
	}
	return 0;
}

/* represent click on load.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnLoadLoad(int x, int y) {
	if ((x >= 585 && x <= 735) && (y >= 140 && y <= 190)) {
		return 1;
	}
	return 0;
}

/* the trgaet of the function is handle an event.
 * the function get refreces for LoadWin and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
LOAD_EVENT loadWindowHandleEvent(LoadWin* src, SDL_Event* event){
	if (!event) {
		return lOAD_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (isClickOnLoadLoad(event->button.x, event->button.y)) {
				return lOAD_LOAD;
		}
		else if (isClickOnSlot1(event->button.x, event->button.y)) {
			if (src->slot_available > 0){
			    src->slot_active = 1;
				return LOAD_GAME_SLOT_1;}
			}

		else if (isClickOnSlot2(event->button.x, event->button.y)) {
			if (src->slot_available > 1){
				src->slot_active = 2;
				return LOAD_GAME_SLOT_2;}
			}
		else if (isClickOnSlot3(event->button.x, event->button.y)) {
			if (src->slot_available > 2){
			    src->slot_active = 3;
				return LOAD_GAME_SLOT_3;}
			}

		else if (isClickOnSlot4(event->button.x, event->button.y)) {
			if (src->slot_available > 3){
				src->slot_active = 4;
				return LOAD_GAME_SLOT_4;}
			}
		else if (isClickOnSlot5(event->button.x, event->button.y)) {
			if (src->slot_available > 4){
				src->slot_active = 5;
				return LOAD_GAME_SLOT_5;}
			}
		else if (isClickOnLoadBack(event->button.x, event->button.y))
			return LOAD_BACK;
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return MAIN_LOAD_EXIT;
		}
		break;
	default:
		return LOAD_NONE;
	}
	return LOAD_NONE;
 }

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int load_Upload_Textures_1 (SDL_Surface* loading_surface,LoadWin * current ){
	loading_surface = SDL_LoadBMP("./images/LoadMenu.bmp");
	if (loading_surface == NULL ) {
		loadWindowDestroy(current);
		printf("couldn't create LoadMenu.bmp surface\n");
		return 0 ;
	}
	current->background_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->background_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		loadWindowDestroy(current);
		printf("couldn't create LoadMenu.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	loading_surface = SDL_LoadBMP("./images/GameSlot1Chose.bmp");
	if (loading_surface == NULL ) {
		loadWindowDestroy(current);
		printf("couldn't create GameSlot1Chose.bmp surface\n");
		return 0 ;
	}
	current->game_slot_1_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer,loading_surface );
	if (current->game_slot_1_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		loadWindowDestroy(current);
		printf("couldn't create GameSlot1Chose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	loading_surface = SDL_LoadBMP("./images/GameSlot1Not.bmp");
	if (loading_surface == NULL ) {
		loadWindowDestroy(current);
		printf("couldn't create GameSlot1Not.bmp surface\n");
		return 0 ;
	}
	current->game_slot_1_not_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer,loading_surface );
	if (current->game_slot_1_not_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		loadWindowDestroy(current);
		printf("couldn't create GameSlot1Not.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	loading_surface = SDL_LoadBMP("./images/GameSlot2Chose.bmp");
	if (loading_surface == NULL ) {
		loadWindowDestroy(current);
		printf("couldn't create GameSlot2Chose.bmp surface\n");
		return 0 ;
	}
	current->game_slot_2_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->game_slot_2_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		loadWindowDestroy(current);
		printf("couldn't create GameSlot2Chose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	return 1;
}

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int load_Upload_Textures_2 (SDL_Surface* loading_surface,LoadWin * current ){
	loading_surface = SDL_LoadBMP("./images/GameSlot2Not.bmp");
	if (loading_surface == NULL ) {
		loadWindowDestroy(current);
		printf("couldn't createGameSlot2Not.bmp surface\n");
		return 0 ;
	}
	current->game_slot_2_not_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->game_slot_2_not_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		loadWindowDestroy(current);
		printf("couldn't create  GameSlot2Not.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	loading_surface = SDL_LoadBMP("./images/GameSlot3Chose.bmp");
	if (loading_surface == NULL ) {
		loadWindowDestroy(current);
		printf("couldn't create GameSlot3Chose.bmp surface\n");
		return 0 ;
	}
	current->game_slot_3_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->game_slot_3_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		loadWindowDestroy(current);
		printf("couldn't create  GameSlot3Chose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	loading_surface = SDL_LoadBMP("./images/GameSlot3Not.bmp");
	if (loading_surface == NULL ) {
		loadWindowDestroy(current);
		printf("couldn't create GameSlot3Not.bmp surface\n");
		return 0 ;
	}
	current->game_slot_3_not_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->game_slot_3_not_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		loadWindowDestroy(current);
		printf("couldn't create  GameSlot3Not.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	loading_surface = SDL_LoadBMP("./images/GameSlot4Chose.bmp");
	if (loading_surface == NULL ) {
		loadWindowDestroy(current);
		printf("couldn't create GameSlot4Chose.bmp surface\n");
		return 0 ;
	}
	current->game_slot_4_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->game_slot_4_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		loadWindowDestroy(current);
		printf("couldn't create  GameSlot4Chose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	return 1;

}

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int load_Upload_Textures_3 (SDL_Surface* loading_surface,LoadWin * current ){
	loading_surface = SDL_LoadBMP("./images/GameSlot4Not.bmp");
	if (loading_surface == NULL ) {
		loadWindowDestroy(current);
		printf("couldn't create GameSlot4Not.bmp surface\n");
		return 0 ;
	}
	current->game_slot_4_not_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->game_slot_4_not_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		loadWindowDestroy(current);
		printf("couldn't create  GameSlot4Not.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	loading_surface = SDL_LoadBMP("./images/GameSlot5Chose.bmp");
	if (loading_surface == NULL ) {
		loadWindowDestroy(current);
		printf("couldn't create GameSlot5Chose.bmp surface\n");
		return 0 ;
	}
	current->game_slot_5_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->game_slot_5_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		loadWindowDestroy(current);
		printf("couldn't create  GameSlot5Chose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	loading_surface = SDL_LoadBMP("./images/GameSlot5Not.bmp");
	if (loading_surface == NULL ) {
		loadWindowDestroy(current);
		printf("couldn't create GameSlot5Not.bmp surface\n");
		return 0 ;
	}
	current->game_slot_5_not_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->game_slot_5_not_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		loadWindowDestroy(current);
		printf("couldn't create  GameSlot5Not.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	loading_surface = SDL_LoadBMP("./images/LoadChose.bmp");
	if (loading_surface == NULL ) {
		loadWindowDestroy(current);
		printf("couldn't create LoadChose.bmp surface\n");
		return 0 ;
	}
	current->load_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->load_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		loadWindowDestroy(current);
		printf("couldn't create  LoadChose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	return 1;
}

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int load_Upload_Textures_4 (SDL_Surface* loading_surface,LoadWin * current ){
	loading_surface = SDL_LoadBMP("./images/LoadChoseNot.bmp");
	if (loading_surface == NULL ) {
		loadWindowDestroy(current);
		printf("couldn't create LoadChoseNot.bmp surface\n");
		return 0 ;
	}
	current->load_Not_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->load_Not_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		loadWindowDestroy(current);
		printf("couldn't create  LoadChoseNot.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/BackChose.bmp");
	if (loading_surface == NULL ) {
		loadWindowDestroy(current);
		printf("couldn't create BackChose.bmp surface\n");
		return 0 ;
	}
	current->back_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->back_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		loadWindowDestroy(current);
		printf("couldn't create  BackChose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	return 1;
}
