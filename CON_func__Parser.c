#include "CON_func__Parser.h"

/**
 * the function build an default commnd in the struct of setting_command. it doesn't get nothing.
 * but the function put the dafualt values for every varibale.
 * @retrun
 * setting cammand with default values.
 */
Setting_Command initDefaultCommand(){
	Setting_Command command;
	command.cmd = CH_INVALID_LINE; //the default situation.
	command.arg = 0;
	command.validArg = 0;
	command.from = setOrderedPair(0,0);
	command.to = setOrderedPair(0,0);
	return command;
}

/**
 * Parses a specified line. If the line is a command which has an integer
 * argument then the argument is parsed and is saved in the field arg.
 * if the command is legal the validarg is set to true, else it set to false.
 *  the function updated the setting_command according to the command.
 *
 * @return
 * A parsed line (Setting_Command) such that:
 *   cmd - contains the command type, if the line is invalid then this field is
 *         set to INVALID_LINE
 *   validArg - is set to true if the command is legal and else set to false.
 *   arg      - the integer argument, the default is 0.
 *   from     - in relevant commands it represents an ordered pair.
 *   to       - in relevant commands it represents an ordered pair.
 */
Setting_Command chParseLine(const char* str, bool settingMode, bool gameMode){

	char str2[strlen(str)+1];
	char *first,*second,*third,*fourth;

	strcpy(str2,str); // copy str to str2
	Setting_Command command = initDefaultCommand();

	const char s[]=" \t\r\n"; // the delimiter that divided the line

	first=strtok(str2,s); //first dividing
	if(first == NULL ){	return command;	}

	second = strtok(NULL, s);	third = strtok(NULL, s);	fourth = strtok(NULL, s);

	if(strtok(NULL, s)!= NULL){return command;	} // there is no command with 5 part

	if(third == NULL){

		if(second == NULL){
			if( (strcmp("print_setting",first) == 0))//print the setting of the game
				return updateCommand( CH_PRINT_SETTING, 0,settingMode,gameMode);

			if( (strcmp("quit",first) == 0))//quit game
				return updateCommand( CH_QUIT, 0,settingMode,gameMode);

			if( (strcmp("start",first) == 0))//start the game
				return updateCommand( CH_START, 0,settingMode,gameMode);

			if( (strcmp("undo",first) == 0))//undo
				return updateCommand(CH_UNDO, 0,settingMode,gameMode);

			if( (strcmp("reset",first) == 0 ))//restart_game
				return updateCommand( CH_RESET, 0,settingMode,gameMode);

			if((strcmp("default",first) == 0))
				return updateCommand( CH_DEFAULT, 0,settingMode,gameMode);
		}

		if( (strcmp("game_mode",first) == 0) && chParserIsInt(second))//game mode
			return updateCommand(CH_GAME_MODE, atoi( second ),settingMode,gameMode);

		if(strcmp("difficulty",first) == 0){//difficulty
			if( chParserIsInt(second)) return updateCommand(CH_DIFFICULTY, atoi( second ),settingMode,gameMode);
			command.cmd = CH_DIFFICULTY;
			command.validArg = 0;
			return command;
		}

		if( (strcmp("user_color",first) == 0) && chParserIsInt(second))//user_color, only in one player mode.
			return updateCommand(CH_USER_COLOR, atoi( second ),settingMode,gameMode);


		if( (strcmp("load",first) == 0) && second != NULL){//load, we will take care of path null in the program
			command.cmd = CH_LOAD;
			command.validArg = 1;
			strcpy (command.path , second);
			return command;
		}

		if( (strcmp("save",first) == 0) && second != NULL ){//save, we will take care of path null in the program
			command.cmd = CH_SAVE;
			command.validArg = 1;
			strcpy (command.path , second);
			return command;
		}

	}
	/// third != NULL
	if ( (strcmp("move",first) == 0) && chParserIsCouple(second) == 1  && (strcmp("to",third) == 0) && chParserIsCouple(fourth) == 1){ // in addition it check legality.

		command.cmd = CH_MOVE;

		if ( strlen(second)!= 5  || strlen(fourth)!= 5){
			if(gameMode) print_invalidPos();
			return command;
		}

		if (  second[1] > '8' || second [1] < '1'  ||  second[3] > 'H' ||   second [3] < 'A'  ){
			if(gameMode) print_invalidPos();
			return command;
		}

		if ( fourth[1] > '8' ||  fourth [1] < '1' ||  fourth[3] > 'H'  ||  fourth [3] < 'A'  ){
			if(gameMode) print_invalidPos();
			return command;
		}
		command.from.x = second[1]-'1';
		command.from.y = second[3]- 'A';
		command.to.x = fourth[1]-'1';
		command.to.y = fourth[3]- 'A';
		command.validArg=1;
		return command;
	}

	return command; // shouldnt reach here/
}


/*
 * the command prints ""Invalid position on the board".
 * */
void print_invalidPos(){printf("Invalid position on the board\n");}


/*
 * the traget of the function is to update an specific command in the legal values of it, such as validard and arg.
 * the function get an setting_commnd, CH_SETTING_COMMAND - a specific command, and argument.
 * @return
 * 	an update Setting_command.
 */
Setting_Command updateCommand( CH_SETTING_COMMAND CH_command, int arg, bool settingMode, bool gameMode){

	Setting_Command command;
	command.cmd = CH_command;
	command.arg =  arg;

	command.validArg = 0;

	switch(CH_command){

	case CH_GAME_MODE:
		if(arg == 1 || arg ==2){
			if(arg == 1 && settingMode)printf("Game mode is set to %d player\n",command.arg);
			if(arg == 2 &&  settingMode)printf("Game mode is set to %d players\n",command.arg);
			command.validArg = 1;
			return command;
		}
		if(settingMode)printf("Wrong game mode\n");
		return command;


	case CH_DIFFICULTY:
		if(arg >= 1 && arg <=5){
			command.validArg = 1;
		}
		return command;


	case CH_USER_COLOR: // black: 0, white: 1.
		if(arg == 0 || arg == 1){
			command.validArg = 1;
			return command;
		}
		return command;


	case CH_RESET:
		if(gameMode)printf("Restarting...\n");
		command.validArg = 1;
		return command;


	case CH_QUIT: // black: 0, white: 1.
		printf("Exiting...\n");
		command.validArg = 1;
		return command;

	default :
		command.validArg = 1;
		return command;
	}
}



/**
 * Checks if a specified string represents a valid integer. It is recommended
 * to use this function prior to calling the standard library function atoi.
 *
 * @return
 * true if the string represents a valid integer, and false otherwise.
 */
bool chParserIsInt(const char* str){

	if ( str==NULL ){ return 0; } //check if str is null
	int len = strlen(str); // len=lentgh, get the lentgh

	if (len == 0){ return 0;}
	int i;
	for ( i = 0; i< len ; ++i){
		if( str[0] == 45 && i == 0) //45 == -
			continue;
		if (str[i] < 48 || str[i] > 57) //numbers between 0-9
			return 0;
	}
	return 1;
}


/**
 * Checks if a specified string represents a valid shape of ordered pair <x,y> of the index in the table.
 *
 * @return
 * true if the string represents a valid shape of ordered pair <x,y>, and false otherwise.
 */
bool chParserIsCouple( const char* str ){
	if (str == NULL) return 0;  //check if str is null
	int last_indx = strlen(str)-1, commaAmount = 0; // len=lentgh, get the lentgh

	if (str[0] != '<' || str[last_indx] != '>') return 0;
	int i;
	for( i = 1 ; i < last_indx ; i++){
		if(str[i] == ',') {
			//<,66> / <66,> / <,,4>
			if(  i == 1  || i == last_indx-1 )return 0;
			commaAmount++;
		}
	}
	if (commaAmount != 1) return 0;

	return 1;
}






