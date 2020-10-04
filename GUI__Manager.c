/*
 * guiManager.c
 *
 *  Created on: Sep 16, 2017
 *      Author: ranam
 */

#include "GUI__Manager.h"

#include "CON_struct__Address_Que.h"
#include <stdio.h>
#include <stdlib.h>

/*the traget of the function is to creat the manager of the run of  the program.
 * the function return a struct GuiManager, that includes all the relevant parametes for the manager.
 */
GuiManager* managerCreate(){
	GuiManager* manager = (GuiManager*) malloc(sizeof(GuiManager));
	if (manager == NULL ) {
		return NULL ;
	}
	manager->mainMenu = mainWindowCreate();
	if (manager->mainMenu == NULL ) {
		free(manager);
		return NULL ;
	}
	manager->mainGameMode = NULL;
	manager->gameWin = NULL;
	manager->difficultyWin = NULL;
	manager->colorWin = NULL;
	manager->loadWin = NULL;
	manager->activeWin = Main_Menu;
	manager->playerAmount = 1;
	manager->diffLevel = 2;
	manager->playerColor = 1;
	manager->currentPlayerColor = 1;
	manager->loadWin = 0 ;
	manager->during_game = 0 ;
	manager->save_game = 0;
	manager->temp_que = init_addressQue() ;
	if (manager->temp_que == NULL){
		managerDestroy(manager);
		return NULL ;
	}
	load_Que_Info (manager->temp_que);
	return manager;
}

/* the traget of the function is to free the memory of the struct and it components.
 * it get refernce for GuiManager and destroy all the fields in the struct.
*/
void managerDestroy(GuiManager* manager){
	if (!manager){
		return;
	}
	if (manager->activeWin == Main_Menu)
		mainWindowDestroy(manager->mainMenu);
	if (manager->activeWin == Main_Game_Mode)
		mainGameModeWindowDestroy(manager->mainGameMode);
	if (manager->activeWin == Difficulty_Win)
			difficultyWindowDestroy(manager->difficultyWin);
	if (manager->activeWin == Color_Win)
			colorWindowDraw(manager->colorWin);
	if (manager->activeWin == Game)
		gameWindowDestroy(manager->gameWin);
	if (manager->activeWin == Load_Win)
		loadWindowDestroy(manager->loadWin);
	save_Que_Info (manager->temp_que);
	destroy_addressQue(manager->temp_que);

	free(manager);
}

/*the traget of the function is to draw the window that we are in right now,
 * the function get refernce of GuiManager and draw the relevant window  on the screen.
 */
void managerDraw(GuiManager* manager) {
	if (!manager) {
		return;
	}

	if (manager->activeWin == Main_Menu)
		mainWindowDraw(manager->mainMenu);
	if (manager->activeWin == Main_Game_Mode)
		mainGameModeWindowDraw(manager->mainGameMode);
	if (manager->activeWin == Game)
		gameWindowDraw(manager->gameWin);
	if (manager->activeWin == Difficulty_Win)
		difficultyWindowDraw(manager->difficultyWin);
	if (manager->activeWin == Color_Win)
		colorWindowDraw(manager->colorWin);
	if (manager->activeWin == Load_Win)
		loadWindowDraw(manager->loadWin);

}

/* the trgaet of the function is handle an event of main menu.
 * the function get refreces for GuiManager and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
MANAGER_EVENET handleManagerDueToMainMenuEvent(GuiManager* src,MAIN_MENU_EVENT event) {
	if (src == NULL ) {
		return MANAGER_NONE;
	}
	if (event == MAIN_NEW_GAME) {
		mainWindowDestroy(src->mainMenu);
		(src->mainGameMode) = mainGameModeWindowCreate();
		if (src->mainGameMode == NULL ) {
			printf("Couldn't create Game Mode window\n");
			return MANAGER_QUIT;
		}
		src->activeWin = Main_Game_Mode;
	}
	if (event == MAIN_LOAD_GAME){
		mainWindowDestroy(src->mainMenu);
		src->loadWin = loadWindowCreate(src->temp_que);
		if (src->loadWin == NULL ) {
			printf("Couldn't create load window\n");
			return MANAGER_QUIT;
		}
		src->activeWin = Load_Win;
	}
	if (event == MAIN_EXIT){
		return MANAGER_QUIT;
	}
	return MANAGER_NONE;
}

/* the trgaet of the function is handle an event of game mode.
 * the function get refreces for GuiManager and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
MANAGER_EVENET handleManagerDueToGameModeEvent(GuiManager* src,MAIN_GAME_MODE_EVENT event) {
	if (src == NULL ) {
		return MANAGER_NONE;
	}
	if (event == MAIN_GAME_MODE_START) {
		mainGameModeWindowDestroy(src->mainGameMode);
		src->gameWin = gameWindowCreate(src->playerAmount,src->diffLevel,src->playerColor,src->currentPlayerColor);
		if (src->gameWin == NULL ) {
			printf("Couldn't create Game window\n");
			return MANAGER_QUIT;
		}
		src->activeWin = Game;
		src->during_game = 1;
	}
	if (event == MAIN_GAME_MODE_NEXT){
		mainGameModeWindowDestroy(src->mainGameMode);
		src->difficultyWin = difficultyWindowCreate();
		if (src->difficultyWin == NULL){
			printf("Couldn't create Difficulty window\n");
			return MANAGER_QUIT;
		}
		src->activeWin = Difficulty_Win;
	}

	if (event == MAIN_GAME_MODE_BACK){
		src->playerAmount = 1;
		mainGameModeWindowDestroy(src->mainGameMode);
		src->mainMenu = mainWindowCreate();
			if (src->mainMenu == NULL ) {
				printf("Couldn't create Main_Menu window\n");
				return MANAGER_QUIT;
			}
		src->activeWin = Main_Menu;
		src->playerAmount = 1;
		src->diffLevel = 2;
		src->playerColor = 1;
		src->currentPlayerColor = 1;
		src->loadWin = 0 ;
		src->during_game = 0;
		src->save_game = 0;
		mainWindowShow (src->mainMenu);
		return MANAGER_NONE;
	}

	if (event == ONE_PLAYER){
		src->playerAmount = 1;
		return MANAGER_NONE;
	}

	if (event == TWO_PLAYERS){
		src->playerAmount = 2;
		return MANAGER_NONE;
	}

	if (event == MAIN_GAME_MODE_EXIT){
		return MANAGER_QUIT;
	}
	return MANAGER_NONE;
}

/* the trgaet of the function is handle an event of difficulty window.
 * the function get refreces for GuiManager and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
MANAGER_EVENET handleManagerDueToDifficultyEvent(GuiManager* src,DIFFICULTY_EVENT event) {
	if (src == NULL ) {
		return MANAGER_NONE;
	}
	if (event == DIFFICULTY_NEXT) {
		difficultyWindowDestroy(src->difficultyWin);
		src->colorWin = colorWindowCreate();
		if (src->colorWin == NULL ) {
			printf("Couldn't create color window\n");
			return MANAGER_QUIT;
		}
		src->activeWin = Color_Win;
	}

	if (event == DIFFICULTY_NOOB){
		src->diffLevel = 1;
		return MANAGER_NONE;
	}

	if (event == DIFFICULTY_EASY){
		src->diffLevel = 2;
		return MANAGER_NONE;
	}

	if (event == DIFFICULTY_MOODERATE){
		src->diffLevel = 3;
		return MANAGER_NONE;
	}

	if (event == DIFFICULTY_HARD){
		src->diffLevel = 4;
		return MANAGER_NONE;
	}

	if (event == DIFFICULTY_BACK){
		src->diffLevel = 1;

		difficultyWindowDestroy (src->difficultyWin);
		src->mainMenu = mainWindowCreate();
		if (src->mainMenu == NULL ) {
			printf("Couldn't create Difficulty window\n");
				    return MANAGER_QUIT;
		}
		src->activeWin = Main_Menu;
		src->playerAmount = 1;
		src->diffLevel = 2;
		src->playerColor = 1;
		src->currentPlayerColor = 1;
		src->loadWin = 0 ;
		src->during_game = 0;
		src->save_game = 0;
		src->activeWin = Main_Menu;
		mainWindowShow (src->mainMenu);
		return MANAGER_NONE;
	}

	if (event == MAIN_DIFFICULTY_EXIT){
		return MANAGER_QUIT;
	}

	return MANAGER_NONE;
}

/* the trgaet of the function is handle an event of color window.
 * the function get refreces for GuiManager and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
MANAGER_EVENET handleManagerDueToColorEvent(GuiManager* src,COLOR_EVENT event) {
	if (src == NULL ) {
		return MANAGER_NONE;
	}
	if (event == COLOR_START) {
		colorWindowDestroy(src->colorWin);
		src->gameWin = gameWindowCreate(src->playerAmount,src->diffLevel,src->playerColor,src->currentPlayerColor);
		if (src->gameWin == NULL ) {
			printf("Couldn't create Game window\n");
			return MANAGER_QUIT;
		}
		src->activeWin = Game;
		src->during_game = 1;
	}
	if (event == COLOR_BACK){
		colorWindowDestroy (src->colorWin);
		src->mainMenu = mainWindowCreate();
		if (src->mainMenu == NULL ) {
			printf("Couldn't create Main_Menu window\n");
				return MANAGER_QUIT;
		}
		src->activeWin = Main_Menu;
		src->playerAmount = 1;
		src->diffLevel = 2;
		src->playerColor = 1;
		src->currentPlayerColor = 1;
		src->loadWin = 0 ;
		src->during_game = 0;
		src->save_game = 0;
		src->activeWin = Main_Menu;
		mainWindowShow (src->mainMenu);
		return MANAGER_NONE;
	}

	if (event == COLOR_WHITE){
		src->playerColor = 1;
		src->currentPlayerColor = 1;
		return MANAGER_NONE;
	}

	if (event == COLOR_BLACK){
		src->playerColor = 0;
		src->currentPlayerColor = 0;
		return MANAGER_NONE;
	}

	if (event == MAIN_COLOR_EXIT){
		return MANAGER_QUIT;
	}
	return MANAGER_NONE;
}

/* the trgaet of the function is handle an event of game, during the run of the chess game.
 * the function get refreces for GuiManager and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
MANAGER_EVENET handleManagerDueToGameEvent(GuiManager* src,GAME_EVENT event) {
	if (src == NULL ) {
		return MANAGER_NONE;
	}
	if (event == GAME_RESTART) {
		gameWindowDestroy(src->gameWin); ///////don't forget to remove a specific game.
		src->gameWin = gameWindowCreate(src->playerAmount,src->diffLevel,src->playerColor,src->currentPlayerColor);
		if (src->gameWin == NULL ) {
			printf("Couldn't create Game window\n");
			return MANAGER_QUIT;
		}
		src->activeWin = Game;
	}
	if (event == GAME_SAVE){
		que_save_at_start (src->gameWin->the_game,src->temp_que);
		src->save_game = 1;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Save", "The game was saved.",NULL );
	}
	if (event == GAME_LOAD){
		mainGameWindowHide(src->gameWin);
		src->loadWin = loadWindowCreate(src->temp_que);
		if (src->loadWin == NULL ) {
			printf("Couldn't create load window\n");
			return MANAGER_QUIT;
		}
		src->activeWin = Load_Win;
		src->save_game = 0;}
	if (event == GAME_UNDO){
		return MANAGER_NONE;}
	if (event == GAME_MAIN_MENU){
		int ans = ask_for_save(src->save_game);
			if (ans == 1 || ans == -1)
				return handleManagerDueToGameEventMainMenu(src);
			if (ans == 0)
				return MANAGER_NONE;
			if (ans == 2){
				que_save_at_start (src->gameWin->the_game,src->temp_que);
				src->save_game = 1;
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Save", "The game was saved.",NULL );
				return handleManagerDueToGameEventMainMenu(src);
			}
	}
	if (event == GAME_END){
		src->gameWin->the_game->mode = 1;
	}
	if (event == MAIN_GAME_EXIT){
		int ans = ask_for_save(src->save_game);
		if (ans == 1 || ans == -1)
			return MANAGER_QUIT;
		if (ans == 0)
			return MANAGER_NONE;
		if (ans == 2){
			que_save_at_start (src->gameWin->the_game,src->temp_que);
			src->save_game = 1;
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Save", "The game was saved.",NULL );
			return MANAGER_QUIT;
		}
	}
	return MANAGER_NONE;
}

/* the trgaet of the function is handle an event of game, during the run of the chess game.
 * the function get refreces for GuiManager and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
MANAGER_EVENET handleManagerDueToGameEventMainMenu(GuiManager* src){
	gameWindowDestroy(src->gameWin);
	src->mainMenu = mainWindowCreate();
	if (src->mainMenu == NULL ) {
		printf("Couldn't create Main_Menu window\n");
		return MANAGER_QUIT;
	}
	src->activeWin = Main_Menu;
	src->playerAmount = 1;
	src->diffLevel = 2;
	src->playerColor = 1;
	src->currentPlayerColor = 1;
	src->loadWin = 0 ;
	src->during_game = 0;
	src->save_game = 0;
	src->activeWin = Main_Menu;
	mainWindowShow (src->mainMenu);
	return MANAGER_NONE;
}

/*the traget of the function is to ask the user if he want to save the
 * current game, if he didn't save until now. the message return 0 if the answer is cancel- return the game,
 * it return 1 if the answer is yes: save the game, it return 2: if the answer is 2, exit without saving.
 * if the game was saved until now, it wouldn't present the message and return -1.
 */
int ask_for_save(int save_game){
	if (save_game == 0){
	    const SDL_MessageBoxButtonData buttons[] = {
	        { /* .flags, .buttonid, .text */        0, 0, "cancel" },
	        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "no" },
	        { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "yes" },
	    };
	    const SDL_MessageBoxColorScheme colorScheme = {
	        { /* .colors (.r, .g, .b) */
	            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
	            { 125,   125,   125 },
	            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
	            {   0, 255,   0 },
	            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
	            { 255, 255,   0 },
	            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
	            {   0,   0, 255 },
	            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
	            { 255,   0, 255 }
	        }
	    };
	    const SDL_MessageBoxData messageboxdata = {
	        SDL_MESSAGEBOX_INFORMATION, /* .flags */
	        NULL, /* .window */
	        "Do you want to save the game?", /* .title */
	        "select a button please", /* .message */
	        SDL_arraysize(buttons), /* .numbuttons */
	        buttons, /* .buttons */
	        &colorScheme /* .colorScheme */
	    };
	    int buttonid = -1;
	    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
	        SDL_Log("error displaying message box");
	     //   return  -1;
	    }
	    return buttonid;
	}
	return -1;
}

/* the trgaet of the function is handle an event of load menu.
 * the function get refreces for GuiManager and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
MANAGER_EVENET handleManagerDueToLoadEvent (GuiManager* src,LOAD_EVENT event) {
	if (src == NULL ) {
		return MANAGER_NONE;
	}
	if (event == lOAD_LOAD) {
		if (src->loadGame != 0){
		    if (src->during_game == 0){
				src->gameWin = gameWindowCreate(src->playerAmount,src->diffLevel,src->playerColor,src->currentPlayerColor);
				if (src->gameWin == NULL ) {
					printf("Couldn't create Game window\n");
					return MANAGER_QUIT;
				}
		    	load_specific_game (src->gameWin->the_game,src->temp_que,src->loadGame);
		    }
		    else{
		    	gameWindowDestroy(src->gameWin);
		    	src->gameWin = gameWindowCreate(src->playerAmount,src->diffLevel,src->playerColor,src->currentPlayerColor);
		    	if (src->gameWin == NULL ) {
		    		printf("Couldn't create Game window\n");
		    		return MANAGER_QUIT;
		    	}
		    	load_specific_game (src->gameWin->the_game,src->temp_que,src->loadGame);
		    }
		    src->activeWin = Game;
		    src->during_game = 1;
		    src->loadGame = 0;
		    src->gameWin->the_game->mode = 0 ;
		    loadWindowDestroy(src->loadWin);
		}
	}

	if (event == LOAD_GAME_SLOT_1){
		src->loadGame = 1;
		return MANAGER_NONE;
	}

	if (event == LOAD_GAME_SLOT_2){
		src->loadGame = 2;
		return MANAGER_NONE;
	}

	if (event == LOAD_GAME_SLOT_3){
		src->loadGame = 3;
		return MANAGER_NONE;
	}

	if (event == LOAD_GAME_SLOT_4){
		src->loadGame = 4;
		return MANAGER_NONE;
	}
	if (event == LOAD_GAME_SLOT_5){
		src->loadGame = 5;
		return MANAGER_NONE;
	}

	if (event == LOAD_BACK){
		src->loadGame = 0;
		loadWindowDestroy(src->loadWin);

    if (src->during_game == 1 ){
    	src->activeWin = Game;
    	mainGameWindowShow (src->gameWin);
    }
    else{
    	src->mainMenu = mainWindowCreate();
    	if (src->mainMenu == NULL ) {
    		printf("Couldn't create Main_Menu window\n");
    		return MANAGER_QUIT;
    	}
    	src->activeWin = Main_Menu;
    	src->playerAmount = 1;
    	src->diffLevel = 2;
    	src->playerColor = 1;
    	src->currentPlayerColor = 1;
    	src->loadWin = 0 ;
    	src->during_game = 0;
    	src->save_game = 0;
		src->activeWin = Main_Menu;
		mainWindowShow (src->mainMenu);
    }
		return MANAGER_NONE;
	}

	if (event == MAIN_LOAD_EXIT){
		return MANAGER_QUIT;
	}

	return MANAGER_NONE;
}

/* the traget od this function is to manage all the events that happened during a running of game,
 * the function get refreces for GuiManager and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */

MANAGER_EVENET managerHandleEvent(GuiManager* manager, SDL_Event* event) {
	if (manager == NULL || event == NULL ) {
		return MANAGER_NONE;
	}
	if (manager->activeWin == Main_Menu) {
		MAIN_MENU_EVENT mainEvent = mainMenuWindowHandleEvent( event);
		return handleManagerDueToMainMenuEvent(manager, mainEvent);
	}
	if (manager->activeWin == Main_Game_Mode){
		MAIN_GAME_MODE_EVENT mainGameModeEvent = mainGameModeWindowHandleEvent (manager->mainGameMode,event) ;
		return handleManagerDueToGameModeEvent(manager, mainGameModeEvent);
	}
	if (manager->activeWin == Game){
		GAME_EVENT gameEvent = gameWindowHandleEvent (manager->gameWin,event);
		managerDraw (manager);
		return handleManagerDueToGameEvent(manager, gameEvent);
	}
	if (manager->activeWin == Difficulty_Win){
		DIFFICULTY_EVENT difficultyEvent = difficultyWindowHandleEvent (manager->difficultyWin,event);
		return handleManagerDueToDifficultyEvent (manager,difficultyEvent);
	}
	if (manager->activeWin == Color_Win){
		COLOR_EVENT colorEvent = colorWindowHandleEvent (manager->colorWin,event);
		return handleManagerDueToColorEvent (manager,colorEvent);
    }
	if (manager->activeWin == Load_Win){
		LOAD_EVENT loadEvent = loadWindowHandleEvent (manager->loadWin,event);
		return handleManagerDueToLoadEvent (manager,loadEvent);
	}
	return MANAGER_NONE;
}

