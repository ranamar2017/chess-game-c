/*
 * difficulty.h
 *
 *  Created on: Sep 15, 2017
 *      Author: ranam
 */

#ifndef GUI_DIFFICULTYWIN_H_
#define GUI_DIFFICULTYWIN_H_

#include <SDL.h>

//the traget of the enum is to represent a situation, event, at the difficulty menu.
 typedef enum {
	MAIN_DIFFICULTY_EXIT, DIFFICULTY_NEXT,DIFFICULTY_BACK,DIFFICULTY_NOOB,DIFFICULTY_EASY,
	DIFFICULTY_MOODERATE,DIFFICULTY_HARD,DIFFICULTY_EXPERT, DIFFICULTY_INVALID_ARGUMENT,DIFFICULTY_NONE
} DIFFICULTY_EVENT;

//the traget is to hold a color.
typedef struct {
	//SDL_Window* window;
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	SDL_Texture* background_texture;
	SDL_Texture* noob_choose_texture;
	SDL_Texture* noob_not_choose_texture;
	SDL_Texture* easy_choose_texture;
	SDL_Texture* easy_not_choose_texture;
	SDL_Texture* moderate_choose_texture;
	SDL_Texture* moderate_not_choose_texture;
	SDL_Texture* hard_choose_texture;
	SDL_Texture* hard_not_choose_texture;
	SDL_Texture* expert_not_choose_texture;
	SDL_Texture* next_texture;
	SDL_Texture* back_texture;
	int diffi ;
} DifficultyWin;

/*the traget of the function is to creat a window for the difficulty menu of the game.
 * the function return a struct DifficultyWin, that includes all the relevant parametes for the difficulty.
 */
DifficultyWin* difficultyWindowCreate();

/* the traget of the function is to free the memory of the struct and it components.
 *  * it get refernce for DifficultyWin and destroy all the fields in the struct.
 */
void difficultyWindowDestroy(DifficultyWin* src);

/*the traget of the function is to draw the difficulty window on the board.
 *   the function get refernce of DifficultyWin and draw it on the window.
 */
void difficultyWindowDraw(DifficultyWin* current);

/* the trgaet of the function is handle an event.
 * the function get refreces for DifficultyWin and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
DIFFICULTY_EVENT difficultyWindowHandleEvent(DifficultyWin* src, SDL_Event* event);

/* represent click on noob.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnNoob(int x, int y);
/* represent click on easy.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnEasy(int x, int y);
/* represent click on moderate.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnModerate(int x, int y);
/* represent click on hard.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnHard(int x, int y);
/* represent click on back.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnDifficultyBack(int x, int y);
/* represent click on next.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnDifficultyNext(int x, int y);

//the traget is to hide a window.
void mainDifficultyWindowHide(DifficultyWin* src);

//the traget is to show a window.
void mainDifficultyWindowShow(DifficultyWin* src);

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int difficulty_Upload_Textures_1 (SDL_Surface* loading_surface,DifficultyWin * current );
/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int difficulty_Upload_Textures_2 (SDL_Surface* loading_surface,DifficultyWin * current );
/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int difficulty_Upload_Textures_3 (SDL_Surface* loading_surface,DifficultyWin * current );
/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int difficulty_Upload_Textures_4 (SDL_Surface* loading_surface,DifficultyWin * current );


#endif /* GUI_DIFFICULTYWIN_H_ */
