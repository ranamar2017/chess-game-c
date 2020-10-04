#include <SDL.h>
#include <SDL_video.h>
#include <stdio.h>

#include "GUI__Manager.h"
#include "CON_func__mainAux.h"


int main(int argc, char *argv[]){
	/// GUI MAIN
	if(argc == 2 && strcmp(argv[1],"-g") == 0 ){

		if (SDL_Init(SDL_INIT_VIDEO) < 0) { //SDL2 INIT
			printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
			return 1;
		}
		GuiManager* manager = managerCreate();
		if (manager == NULL ) {
			SDL_Quit();
			return 0;
		}
		SDL_Event event;
		while (1) {
			SDL_WaitEvent(&event);
			if (managerHandleEvent(manager, &event) == MANAGER_QUIT) {
				break;
			}
			managerDraw(manager);
		}
		managerDestroy(manager);
		SDL_Quit();
		return 0;
	}
	else if ( argc == 1 || (argc == 2 && strcmp(argv[1],"-c") == 0 ) ){
		/// COMSOL MAIN
		setvbuf (stdout, NULL, _IONBF, BUFSIZ);
		const char *enumArray[] = {"pawn","bishop","rook","knight","queen","king"};

		int  curGame;
		start_Quit_Settings choice = gameSettings;
		ChessGame *game;

		while (1){

			game = initDefaultChessGame();
			if(game == NULL){return 1;}

			if(choice == gameSettings){
				printf("Specify game setting or type 'start' to begin a game with the current setting:\n" );
				choice = setGameSettings(&game);
				if(choice == quitGame){ chessGameDestroy(game); return 0;}
			}

			if(game->playerAmount == 1){
				curGame = user_VS_computer(game,enumArray);
				if(curGame == 0){ chessGameDestroy(game); return 0;}
				if(curGame == 1){ choice = gameSettings;}
			}

			else if(game->playerAmount == 2){
				curGame = user_VS_user(game);
				if(curGame == 0){ chessGameDestroy(game); return 0;}
				if(curGame == 1){ choice = gameSettings;}
			}

			chessGameDestroy(game);
		}
		return 0;
	}
	//wont reach here
	return 0;
}
