/*
 * game.c
 *
 *  Created on: Sep 16, 2017
 *      Author: ranam
 */

#include "GUI_GameWin.h"

#include <stdio.h>
#include "CON_struct__OrderedPair.h"

/*the traget of the function is to creat a window for the board game  of the game.
  * the function return a struct GameWin, that includes all the relevant parametes for the main menu.
 */
GameWin* gameWindowCreate(int playerAmount,int diffLevel,int playerColor,int currentPlayerColor){
	SDL_Surface* loading_surface = NULL;
	int success_upload_1, success_upload_2, success_upload_3,success_upload_4,success_upload_5,success_upload_6 ;
	GameWin * current = NULL ;
	current = (GameWin*) calloc(sizeof(GameWin), sizeof(char));
	if (current == NULL ) {
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
		gameWindowDestroy(current);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	current->move_relevant.x_current = 0;
	current->move_relevant.y_current = 0;
	current->move_relevant.x_mouse_down = 0;
	current->move_relevant.y_mouse_down= 0;
	current->move_relevant.x_mouse_up = 0;
	current->move_relevant.y_mouse_up = 0;
	current->move_relevant.mouse_down = 0;
	current->move_relevant.mouse_up = 0;
	current->move_relevant.mouse_motion = 0;

	current->the_game = initChessGame(playerAmount,6, diffLevel,playerColor,currentPlayerColor);
	if (current->the_game == NULL){
		gameWindowDestroy(current);
		return NULL ;
	}

	current->the_game->mode = 0 ;
	if (playerAmount == 1){
		if (playerColor == 0){
			current->the_game->currentPlayer = 1;
			const char *enumArray[] = {"pawn","bishop","rook","knight","queen","king"};
			computerTurn(current->the_game,enumArray,0);
		}
	}
	current->mainRenderer = SDL_CreateRenderer(current->mainWindow, -1, SDL_RENDERER_ACCELERATED);
	if (current->mainRenderer == NULL ) {
		// In the case that the window could not be made...
		gameWindowDestroy(current);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	success_upload_1 = game_Upload_Textures_1  (loading_surface,current);
	if (success_upload_1 == 0)
		return NULL;
	success_upload_2 = game_Upload_Textures_2  (loading_surface,current);
	if (success_upload_2 == 0)
		return NULL;
	success_upload_3 = game_Upload_Textures_3  (loading_surface,current);
	if (success_upload_3 == 0)
		return NULL;
	success_upload_4 = game_Upload_Textures_4  (loading_surface,current);
	if (success_upload_4 == 0)
		return NULL;
	success_upload_5 = game_Upload_Textures_5  (loading_surface,current);
	if (success_upload_5 == 0)
		return NULL;
	success_upload_6 = game_Upload_Textures_6  (loading_surface,current);
	if (success_upload_6 == 0)
		return NULL;
	return current;
}

/* the traget of the function is to free the memory of the struct and it components.
 *  it get refernce for GameWin and destroy all the fields in the struct.
 */
void gameWindowDestroy(GameWin* src){
	if (!src) {
		return;
	}

	chessGameDestroy (src->the_game); //destroy the game

	if (src->restart_choose_texture != NULL ) {
		SDL_DestroyTexture(src->restart_choose_texture);
	}
	if (src->save_choose_texture!= NULL ) {
		SDL_DestroyTexture(src->save_choose_texture);
	}
	if (src->load_choose_texture != NULL ) {
		SDL_DestroyTexture(src->load_choose_texture);
	}
	if (src->undo_not_choose_texture!= NULL ) {
		SDL_DestroyTexture(src->undo_not_choose_texture);
	}
	if (src->undo_choose_texture!= NULL ) {
		SDL_DestroyTexture(src->undo_choose_texture);
	}
	if (src->mainMenu_choose_texture!= NULL ) {
		SDL_DestroyTexture(src->mainMenu_choose_texture);
	}
	if (src->quit_choose_texture != NULL ) {
		SDL_DestroyTexture(src->quit_choose_texture);
	}
	if (src->white_pawn_texture!= NULL ) {
		SDL_DestroyTexture(src->white_pawn_texture);
	}
	if (src->white_bishop_texture != NULL ) {
		SDL_DestroyTexture(src->white_bishop_texture);
	}
	if (src->white_rook_texture!= NULL ) {
		SDL_DestroyTexture(src->white_rook_texture);
	}
	if (src->white_knight_texture!= NULL ) {
		SDL_DestroyTexture(src->white_knight_texture);
	}
	if (src->white_queen_texture!= NULL ) {
		SDL_DestroyTexture(src->white_queen_texture);
	}
	if (src->white_king_texture!= NULL ) {
		SDL_DestroyTexture(src->white_king_texture);
	}
	if (src->black_pawn_texture != NULL ) {
		SDL_DestroyTexture(src->black_pawn_texture);
	}
	if (src->black_bishop_texture!= NULL ) {
		SDL_DestroyTexture(src->black_bishop_texture);
	}
	if (src->black_rook_texture != NULL ) {
		SDL_DestroyTexture(src->black_rook_texture);
	}
	if (src->black_knight_texture!= NULL ) {
		SDL_DestroyTexture(src->black_knight_texture);
	}
	if (src->black_king_texture!= NULL ) {
		SDL_DestroyTexture(src->black_king_texture);
	}
	if (src->black_queen_texture!= NULL ) {
		SDL_DestroyTexture(src->black_queen_texture);
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

/*the traget of the function is to draw the game window on the board.
 * the function get refernce of GameWin and draw it on the window.
 */
void gameWindowDraw(GameWin* current){
	SDL_Rect RestartButton = {800,50,150,50};
	SDL_Rect SaveButton = {800,125,150,50};
	SDL_Rect LoadButton = {800,200,150,50};
	SDL_Rect UndoVButton = {800,275,150,50};
	SDL_Rect UndoNVButton = {800,275,150,50};
	SDL_Rect MainMenuButton = {800,500,150,50};
	SDL_Rect QuitButton = {800,575,150,50};
	SDL_RenderClear(current->mainRenderer);
	SDL_RenderCopy(current->mainRenderer, current->background_texture, NULL, NULL);
	SDL_RenderCopy(current->mainRenderer, current->restart_choose_texture, NULL, &RestartButton);
	SDL_RenderCopy(current->mainRenderer, current->save_choose_texture, NULL, &SaveButton);
	SDL_RenderCopy(current->mainRenderer, current->load_choose_texture, NULL, &LoadButton);
	if ( current->the_game->playerAmount == 1 && current->the_game->history_queue->actualSize > 1 ){
		SDL_RenderCopy(current->mainRenderer, current->undo_choose_texture, NULL, &UndoVButton);
	}
	else
		SDL_RenderCopy(current->mainRenderer, current->undo_not_choose_texture, NULL, &UndoNVButton);
	SDL_RenderCopy(current->mainRenderer, current->mainMenu_choose_texture, NULL, &MainMenuButton);
	SDL_RenderCopy(current->mainRenderer, current->quit_choose_texture, NULL, &QuitButton);
	OrderedPair from =  place_in_board (current->move_relevant.x_mouse_down, current->move_relevant.y_mouse_down);
	OrderedPair to =  place_in_board (current->move_relevant.x_mouse_up, current->move_relevant.y_mouse_up);
	if (current->move_relevant.mouse_down == 0 && current->move_relevant.mouse_motion == 0 && current->move_relevant.mouse_up == 1 ){
		from.x = (7 - from.x)  ;
		to.x = (7 - to.x) ;
	}

	for( int colom = 0 ; 7>= colom; colom++){
		for( int row = 0 ; row <= 7; row++ ){
			SDL_Rect Position_pieces = {33+colom*88,25+(7-(row))*77,65,65};
			if (current->move_relevant.mouse_down == 1 && from.x == (7-row) && from.y == colom) // will not draw the piece that we touch
				continue;
			int color_piece = current->the_game->gameBoard[row][colom].color_cell;
			BoardPiece piece = current->the_game->gameBoard[row][colom].piece;

			gameWindowDrawPieces(current,Position_pieces,color_piece,piece);
		}
		if (current->move_relevant.mouse_down == 1 && current->move_relevant.mouse_motion == 1 && current->move_relevant.mouse_up == 0 ){
			int color_piece = current->the_game->gameBoard[7-from.x][from.y].color_cell;
			BoardPiece piece = current->the_game->gameBoard[7-from.x][from.y].piece;

			SDL_Rect Position_Move = {current->move_relevant.x_current,  current->move_relevant.y_current,65,65};
			gameWindowDrawPieces(current,Position_Move,color_piece,piece);
		}
	}
	SDL_RenderPresent(current->mainRenderer);
}

/*the function get a specific describe of a piece and draw it on the board.
 * it get refernce of GameWin , SDL_Rect and info on the piece and draw it.
 */

void gameWindowDrawPieces(GameWin* current,SDL_Rect Position_pieces,int color_piece,BoardPiece piece){
	switch (piece){
	case Pawn:
		if(color_piece == 1){ SDL_RenderCopy(current->mainRenderer, current->white_pawn_texture, NULL, &Position_pieces); break;}
		SDL_RenderCopy(current->mainRenderer, current->black_pawn_texture, NULL, &Position_pieces); break;

	case Bishop:
		if(color_piece == 1){ SDL_RenderCopy(current->mainRenderer, current->white_bishop_texture, NULL, &Position_pieces); break;}
		SDL_RenderCopy(current->mainRenderer, current->black_bishop_texture, NULL, &Position_pieces); break;

	case Rook:
		if(color_piece == 1){ SDL_RenderCopy(current->mainRenderer, current->white_rook_texture, NULL, &Position_pieces) ; break;}
		SDL_RenderCopy(current->mainRenderer, current->black_rook_texture, NULL, &Position_pieces); break;

	case Knight:
		if(color_piece == 1){ SDL_RenderCopy(current->mainRenderer, current->white_knight_texture, NULL, &Position_pieces); break;}
		SDL_RenderCopy(current->mainRenderer, current->black_knight_texture, NULL, &Position_pieces); break;

	case Queen:
		if(color_piece == 1){ SDL_RenderCopy(current->mainRenderer, current->white_queen_texture, NULL, &Position_pieces) ; break;}
		SDL_RenderCopy(current->mainRenderer, current->black_queen_texture, NULL, &Position_pieces); break;
	case King:
		if(color_piece == 1){ SDL_RenderCopy(current->mainRenderer, current->white_king_texture, NULL, &Position_pieces) ; break;}
		SDL_RenderCopy(current->mainRenderer, current->black_king_texture, NULL, &Position_pieces); break;

	case Blank:
		break;

	}
}

/* the trgaet of the function is transalte a place on the board to  an order pair in the game,
 * that represnt a location such as: <2,a>
*/
//33+i*88,25+j*77,65,65
OrderedPair place_in_board(int x, int y){
	OrderedPair pair1;
	pair1.y = ((x - 20) / 88)  ;// -33
	pair1.x = ((y - 20) / 77)  ;
	return pair1;

}

/* represent click on restart.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnGameRestart(int x, int y) {
	if ((x >= 800 && x <= 950) && (y >= 50 && y <= 100)) {
		return 1;
	}
	return 0;
}

/* represent click on save.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnGameSave(int x, int y) {
	if ((x >= 800 && x <= 950) && (y >= 125 && y <= 175)) {
		return 1;
	}
	return 0;
}

/* represent click on load.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnGameLoad(int x, int y) {
	if ((x >= 800 && x <= 950) && (y >= 200 && y <= 250)) {
		return 1;
	}
	return 0;
}

/* represent click on undo.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnGameUndo(int x, int y) {
	if ((x >= 800 && x <= 950) && (y >= 275 && y <= 325)) {
		return 1;
	}
	return 0;
}


/* represent click on main menu.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnGameMainMenu(int x, int y) {
	if ((x >= 800 && x <= 950) && (y >= 500 && y <= 550)) {
		return 1;
	}
	return 0;
}

/* represent click on quit.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
 */
int isClickOnGameMainQuit(int x, int y) {
	if ((x >= 800 && x <= 950) && (y >= 575 && y <= 625)) {
		return 1;
	}
	return 0;
}

/* represent click on the board in order to move a piece.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
*/
int isClickOnSource(int x, int y) {
	//	if ((x >= 25 && x <= 90) && (y >= 20 && y <= 85)) {
	if ((x >= 25 && x <= 870) && (y >= 20 && y <= 650)) {
		return 1;
	}
	return 0;
}

/* represent click on the board in order to put a piece.
 * it get int of x and y. and return 1 if the x and y in the range, 0 otherwise.
*/
int isClickOnDes(int x, int y){
	if ((x >= 25 && x <= 870) && (y >= 20 && y <= 650)){
		return 1;
	}
	return 0;
}



/* the trgaet of the function is handle an event.
 * the function get refreces for GameWin and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
GAME_EVENT gameWindowHandleEvent(GameWin* src, SDL_Event* event) {
	if (event == NULL || src == NULL ) {
		return GAME_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (isClickOnGameRestart(event->button.x, event->button.y)) {
			return GAME_RESTART;
		}
		else if (isClickOnGameSave(event->button.x, event->button.y)){
			return GAME_SAVE;
		}
		else if (isClickOnGameLoad(event->button.x, event->button.y)){
			return GAME_LOAD;
		}
		else if (isClickOnGameUndo(event->button.x, event->button.y)){
			if (src->the_game->playerAmount == 1)
				undo_Two_Move (src->the_game,0);
			return GAME_UNDO;
		}
		else if (isClickOnGameMainMenu(event->button.x, event->button.y)){
			return GAME_MAIN_MENU;
		}
		else if (isClickOnGameMainQuit(event->button.x, event->button.y)){
			return MAIN_GAME_EXIT;
		}
		else if (isClickOnDes(event->button.x, event->button.y)){
			src->move_relevant.mouse_up = 1;
			src->move_relevant.mouse_down = 0;
			src->move_relevant.mouse_motion = 0;
			src->move_relevant.x_mouse_up = event->button.x;
			src->move_relevant.y_mouse_up = event->button.y;
		    gameWindowHandlePlayEvent(src);////the function that does the playing.
		}
		break;

	case SDL_MOUSEBUTTONDOWN:
		if (isClickOnSource(event->button.x, event->button.y) ){
			src->move_relevant.mouse_down = 1;
			src->move_relevant.mouse_up = 0;
			src->move_relevant.mouse_motion = 0;
			src->move_relevant.x_mouse_down = event->button.x;
			src->move_relevant.y_mouse_down = event->button.y;
			return PIECE_MOVE; //  handleMove(src,event->button.x, event->button.y);
		}
		break;
	case SDL_MOUSEMOTION:
		src->move_relevant.mouse_motion = 1;
		src->move_relevant.x_current = event->motion.x;
		src->move_relevant.y_current = event->motion.y;

		return GAME_NONE;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return MAIN_GAME_EXIT;
		}
		break;
	default:
		return GAME_NONE;
	}
	return GAME_NONE;

}


/* the trgaet of the function is handle an event- simulate a turn in the game.
 * the function get refreces for GameWin and event and analyze the event, it returns
 * a specific message that describe what to do according the event.
 */
GAME_EVENT gameWindowHandlePlayEvent(GameWin* src) {

	if (src->the_game->playerAmount == 2 || (src->the_game->playerAmount == 1 && src->the_game->currentPlayer == src->the_game->user_color)){
		OrderedPair from =  place_in_board (src->move_relevant.x_mouse_down, src->move_relevant.y_mouse_down);
		OrderedPair to =  place_in_board (src->move_relevant.x_mouse_up, src->move_relevant.y_mouse_up);
		if (src->move_relevant.mouse_down == 0 && src->move_relevant.mouse_motion == 0 && src->move_relevant.mouse_up == 1 ){
			from.x = (7 - from.x)  ;
			to.x = (7 - to.x)      ;
		}
		/*Chess_GAME_MESSAGE add =*/ chessGameSetMove (src->the_game,from,to,0);
		if(check(src->the_game)){
			if( checkmate(src->the_game)){
				if (src->the_game->currentPlayer == 1 && src->the_game->playerAmount == 2)
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "Check Mate for black! black is the winner",NULL );
				if (src->the_game->currentPlayer == 0 && src->the_game->playerAmount == 2)
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "Check Mate for white! white is the winner",NULL );
				if (src->the_game->playerAmount == 1 && src->the_game->currentPlayer == 1 && src->the_game->user_color == 0)
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "Check Mate for black! black is the winner - user is the winner",NULL );
				if(src->the_game->playerAmount == 1 && src->the_game->currentPlayer == 0 && src->the_game->user_color == 1)
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "Check Mate for white! white is the winner - user is the winner",NULL );

				return GAME_END;
			}
			else {
				if (src->the_game->currentPlayer == 1)
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Check", "Check On White!",NULL );
				if (src->the_game->currentPlayer == 0)
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Check", "Check On Black!",NULL );
			}
		}
		if (tie(src->the_game)){
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "The game end with tie!",NULL );
			return GAME_END;
		}

	}
	if (src->the_game->playerAmount == 1 && src->the_game->currentPlayer != src->the_game->user_color){
		const char *enumArray[] = {"pawn","bishop","rook","knight","queen","king"};
		computerTurn(src->the_game,enumArray,0);
		if( check(src->the_game) ){
			if( checkmate(src->the_game)){
				if (src->the_game->currentPlayer == 1 && src->the_game->user_color == 1)
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "Check Mate for black! black is the winner - computer is the winner",NULL );
				if(src->the_game->currentPlayer == 0 && src->the_game->user_color == 0)
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "Check Mate for white! white is the winner - computer is the winner",NULL );
				return GAME_END;
			}
			else {
				if (src->the_game->currentPlayer == 1)
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Check", "Check On White!",NULL );
				if (src->the_game->currentPlayer == 0)
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Check", "Check On Black!",NULL );

			}
		}
		if (tie(src->the_game)){
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "The game end with tie!",NULL );
			return GAME_END;
		}

	}
	return MOUSE_DES;
}

//the traget is to hide a window.
void mainGameWindowHide(GameWin* src) {
	SDL_HideWindow(src->mainWindow);
}

//the traget is to show a window.
void mainGameWindowShow(GameWin* src) {
	SDL_ShowWindow(src->mainWindow);
}

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int game_Upload_Textures_1 (SDL_Surface* loading_surface,GameWin * current ){

	loading_surface = SDL_LoadBMP("./images/ChessBoard.bmp");
	if (loading_surface == NULL ) {
		gameWindowDestroy (current);
		printf("couldn't create ChessBoard.bmp surface\n");
		return 0 ;
	}
	current->background_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->background_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		gameWindowDestroy (current);
		printf("couldn't create ChessBoard.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);



	loading_surface = SDL_LoadBMP("./images/restartChose.bmp");
	if (loading_surface == NULL ) {
		gameWindowDestroy (current);
		printf("couldn't create restartChose.bmp surface\n");
		return 0 ;
	}
	current->restart_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer,loading_surface );
	if (current->restart_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		gameWindowDestroy (current);
		printf("couldn't create restartChose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/saveChose.bmp");
	if (loading_surface == NULL ) {
		gameWindowDestroy (current);
		printf("couldn't create saveChose.bmp surface\n");
		return 0 ;
	}
	current->save_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer,loading_surface );
	if (current->save_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		gameWindowDestroy (current);
		printf("couldn't create saveChose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);



	loading_surface = SDL_LoadBMP("./images/LoadChose.bmp");
	if (loading_surface == NULL ) {
		gameWindowDestroy (current);
		printf("couldn't create LoadChose.bmp surface\n");
		return 0 ;
	}
	current->load_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->load_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		gameWindowDestroy (current);
		printf("couldn't create LoadChose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	return 1;

}

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int game_Upload_Textures_2 (SDL_Surface* loading_surface,GameWin * current ){

	loading_surface = SDL_LoadBMP("./images/UndoNot.bmp");
	if (loading_surface == NULL ) {
		gameWindowDestroy (current);
		printf("couldn't create UndoNot.bmp surface\n");
		return 0 ;
	}
	current->undo_not_choose_texture= SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->undo_not_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		gameWindowDestroy (current);
		printf("couldn't create  UndoNot.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/UndoChose.bmp");
	if (loading_surface == NULL ) {
		gameWindowDestroy (current);
		printf("couldn't create UndoChose.bmp surface\n");
		return 0 ;
	}
	current->undo_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->undo_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		gameWindowDestroy (current);
		printf("couldn't create  UndoChose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/MainMenuChose.bmp");
	if (loading_surface == NULL ) {
		gameWindowDestroy (current);
		printf("couldn't create MainMenuChose.bmp surface\n");
		return 0 ;
	}
	current->mainMenu_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->mainMenu_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		gameWindowDestroy (current);
		printf("couldn't create  MainMenuChose.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/quit.bmp");
	if (loading_surface == NULL ) {
		gameWindowDestroy (current);
		printf("couldn't create quit.bmp surface\n");
		return 0 ;
	}
	current->quit_choose_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->quit_choose_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		gameWindowDestroy (current);
		printf("couldn't create  quit.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	return 1;

}

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int game_Upload_Textures_3 (SDL_Surface* loading_surface,GameWin * current ){

	loading_surface = SDL_LoadBMP("./images/whiteBishop.bmp");
	if (loading_surface == NULL ) {
		gameWindowDestroy (current);
		printf("couldn't create whiteBishop.bmp surface\n");
		return 0 ;
	}
	SDL_SetColorKey(loading_surface, SDL_TRUE,
			SDL_MapRGB(loading_surface->format, 255, 255, 255));
	current->white_bishop_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->white_bishop_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		gameWindowDestroy (current);
		printf("couldn't create  whiteBishop.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/whitePawn.bmp");
	if (loading_surface == NULL ) {
		gameWindowDestroy (current);
		printf("couldn't create whitePawn.bmp surface\n");
		return 0 ;
	}
	SDL_SetColorKey(loading_surface, SDL_TRUE,
			SDL_MapRGB(loading_surface->format, 255, 255, 255));
	current->white_pawn_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->white_pawn_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		gameWindowDestroy (current);
		printf("couldn't create  whitePawn.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/whiteKnight.bmp");
	if (loading_surface == NULL ) {
		gameWindowDestroy (current);
		printf("couldn't create whiteKnight.bmp surface\n");
		return 0 ;
	}
	SDL_SetColorKey(loading_surface, SDL_TRUE,
			SDL_MapRGB(loading_surface->format, 255, 255, 255));
	current->white_knight_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->white_knight_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		gameWindowDestroy (current);
		printf("couldn't create  whiteKnight.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	return 1;

}

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int game_Upload_Textures_4 (SDL_Surface* loading_surface,GameWin * current ){

	loading_surface = SDL_LoadBMP("./images/whiteRook.bmp");
	if (loading_surface == NULL ) {
		gameWindowDestroy (current);
		printf("couldn't create whiteRook.bmp surface\n");
		return 0 ;
	}
	SDL_SetColorKey(loading_surface, SDL_TRUE,
			SDL_MapRGB(loading_surface->format, 255, 255, 255));
	current->white_rook_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->white_rook_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		gameWindowDestroy (current);
		printf("couldn't create  whiteRook.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/whiteQueen.bmp");
	if (loading_surface == NULL ) {
		gameWindowDestroy (current);
		printf("couldn't create whiteQueen.bmp surface\n");
		return 0 ;
	}
	SDL_SetColorKey(loading_surface, SDL_TRUE,
			SDL_MapRGB(loading_surface->format, 255, 255, 255));
	current->white_queen_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->white_queen_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		gameWindowDestroy (current);
		printf("couldn't create  whiteQueen.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/whiteKing.bmp");
	if (loading_surface == NULL ) {
		gameWindowDestroy (current);
		printf("couldn't create whiteKing.bmp surface\n");
		return 0 ;
	}
	SDL_SetColorKey(loading_surface, SDL_TRUE,
			SDL_MapRGB(loading_surface->format, 255, 255, 255));
	current->white_king_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->white_king_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		gameWindowDestroy (current);
		printf("couldn't create  whiteKing.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	return 1;

}

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int game_Upload_Textures_5 (SDL_Surface* loading_surface,GameWin * current ){

	loading_surface = SDL_LoadBMP("./images/blackPawn.bmp");
	if (loading_surface == NULL ) {
		gameWindowDestroy (current);
		printf("couldn't create blackPawn.bmp surface\n");
		return 0 ;
	}
	SDL_SetColorKey(loading_surface, SDL_TRUE,
			SDL_MapRGB(loading_surface->format, 255, 255, 255));
	current->black_pawn_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->black_pawn_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		gameWindowDestroy (current);
		printf("couldn't create  blackPawn.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/blackBishop.bmp");
	if (loading_surface == NULL ) {
		gameWindowDestroy (current);
		printf("couldn't create blackBishop.bmp surface\n");
		return 0 ;
	}
	SDL_SetColorKey(loading_surface, SDL_TRUE,
			SDL_MapRGB(loading_surface->format, 255, 255, 255));
	current->black_bishop_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->black_bishop_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		gameWindowDestroy (current);
		printf("couldn't create  blackBishop.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/blackKnight.bmp");
	if (loading_surface == NULL ) {
		gameWindowDestroy (current);
		printf("couldn't create blackKnight.bmp surface\n");
		return 0 ;
	}
	SDL_SetColorKey(loading_surface, SDL_TRUE,
			SDL_MapRGB(loading_surface->format, 255, 255, 255));
	current->black_knight_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->black_knight_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		gameWindowDestroy (current);
		printf("couldn't create blackKnight.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	return 1;

}

/*the traget of the function is to up load photos to the textures.
 * it return 1 if all the uploads of the photos success, 0 if it failed.
 */
int game_Upload_Textures_6 (SDL_Surface* loading_surface,GameWin * current ){

	loading_surface = SDL_LoadBMP("./images/blackRook.bmp");
	if (loading_surface == NULL ) {
		gameWindowDestroy (current);
		printf("couldn't create blackRook.bmp surface\n");
		return 0 ;
	}
	SDL_SetColorKey(loading_surface, SDL_TRUE,
			SDL_MapRGB(loading_surface->format, 255, 255, 255));
	current->black_rook_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->black_rook_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		gameWindowDestroy (current);
		printf("couldn't create  blackRook.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/blackQueen.bmp");
	if (loading_surface == NULL ) {
		gameWindowDestroy (current);
		printf("couldn't create blackQueen.bmp surface\n");
		return 0 ;
	}
	SDL_SetColorKey(loading_surface, SDL_TRUE,
			SDL_MapRGB(loading_surface->format, 255, 255, 255));
	current->black_queen_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->black_queen_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		gameWindowDestroy (current);
		printf("couldn't create  blackQueen.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);

	loading_surface = SDL_LoadBMP("./images/blackKing.bmp");
	if (loading_surface == NULL ) {
		gameWindowDestroy (current);
		printf("couldn't create blackKing.bmp surface\n");
		return 0 ;
	}
	SDL_SetColorKey(loading_surface, SDL_TRUE,
			SDL_MapRGB(loading_surface->format, 255, 255, 255));
	current->black_king_texture = SDL_CreateTextureFromSurface(current->mainRenderer, loading_surface );
	if (current->black_king_texture == NULL ) {
		SDL_FreeSurface(loading_surface);
		gameWindowDestroy (current);
		printf("couldn't create  blackKing.bmp texture\n");
		return 0 ;
	}
	SDL_FreeSurface(loading_surface);
	return 1;

}

