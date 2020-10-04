/*
 * guiMangaer.h
 *
 *  Created on: Sep 16, 2017
 *      Author: ranam
 */

#ifndef GUI__MANAGER_H_
#define GUI__MANAGER_H_


#include <SDL.h>
#include "CON_struct__Address_Que.h"
#include "GUI_ColorWin.h"
#include "GUI_DifficultyWin.h"
#include "GUI_GameModeWin.h"
#include "GUI_GameWin.h"
#include "GUI_LoadWin.h"
#include "GUI_MenuWin.h"
// #include "loadWin.h"

// the traget of the enum is to mention if we need to quit the program or to continue regular.
typedef enum{
	MANAGER_QUIT,
	MANAGER_NONE,
}MANAGER_EVENET;

// the traget of the enum is to save in which window we are during the run of the program.
typedef enum{
	Main_Menu,
	Main_Game_Mode,
	Game,
	Difficulty_Win,
	Color_Win,
	Load_Win
}ACTIVE_WINDOW;

//the traget is to hold a manager.
typedef struct{
	MainWin* mainMenu;
	MainGameMode* mainGameMode;
	GameWin* gameWin;
	DifficultyWin* difficultyWin;
	ColorWin* colorWin;
	LoadWin* loadWin;
	ACTIVE_WINDOW activeWin;
	int playerAmount;
	int diffLevel;
	int playerColor;
	int currentPlayerColor;
	int loadGame;
	int during_game;
	int save_game ;
	addressQue* temp_que ;
} GuiManager;

/*the traget of the function is to creat the manager of the run of  the program.
 * the function return a struct GuiManager, that includes all the relevant parametes for the manager.
 */
GuiManager* managerCreate();

/* the traget of the function is to free the memory of the struct and it components.
 * it get refernce for GuiManager and destroy all the fields in the struct.
*/
void managerDestroy(GuiManager* manager);

/*the traget of the function is to draw the window that we are in right now,
 * the function get refernce of GuiManager and draw the relevant window  on the screen.
 */
void managerDraw(GuiManager* manager);

/* the trgaet of the function is handle an event of main menu.
 * the function get refreces for GuiManager and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
MANAGER_EVENET handleManagerDueToMainMenuEvent(GuiManager* src,MAIN_MENU_EVENT event);

/* the trgaet of the function is handle an event of game mode.
 * the function get refreces for GuiManager and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
MANAGER_EVENET handleManagerDueToGameModeEvent(GuiManager* src,MAIN_GAME_MODE_EVENT event);

/* the trgaet of the function is handle an event of difficulty window.
 * the function get refreces for GuiManager and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
MANAGER_EVENET handleManagerDueToDifficultyEvent(GuiManager* src,DIFFICULTY_EVENT event);

/* the trgaet of the function is handle an event of color window.
 * the function get refreces for GuiManager and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
MANAGER_EVENET handleManagerDueToColorEvent(GuiManager* src,COLOR_EVENT event);

/* the trgaet of the function is handle an event of game, during the run of the chess game.
 * the function get refreces for GuiManager and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
MANAGER_EVENET handleManagerDueToGameEvent(GuiManager* src,GAME_EVENT event) ;

/* the trgaet of the function is handle an event of load menu.
 * the function get refreces for GuiManager and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
MANAGER_EVENET handleManagerDueToLoadEvent (GuiManager* src,LOAD_EVENT event);

/* the traget od this function is to manage all the events that happened during a running of game,
 * the function get refreces for GuiManager and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
MANAGER_EVENET managerHandleEvent(GuiManager* manager, SDL_Event* event);


/* the trgaet of the function is handle an event of game, during the run of the chess game.
 * the function get refreces for GuiManager and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
MANAGER_EVENET handleManagerDueToGameEventMainMenu(GuiManager* src);

/*the traget of the function is to ask the user if he want to save the
 * current game, if he didn't save until now. the message return 0 if the answer is cancel- return the game,
 * it return 1 if the answer is yes: save the game, it return 2: if the answer is 2, exit without saving.
 * if the game was saved until now, it wouldn't present the message and return -1.
 */
int ask_for_save(int save_game);

#endif /* GUI_FUNC_GUIMANAGERWIN_H_ */
