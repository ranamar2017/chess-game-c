#ifndef CON_FUNC__PARSER_H_
#define CON_FUNC__PARSER_H_


#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "CON_struct__OrderedPair.h"

//specify the maximum line length
#define CH_MAX_LINE_LENGTH 1024

//enum used to represent user command.
typedef enum CH_setting_command{
	CH_GAME_MODE,// one player -> human being against the computer. two players -> two people. 1 or 2.
	CH_UNDO,
	CH_DIFFICULTY, // there are four levels. 1-4
	CH_USER_COLOR, // black: 0. white: 1.
	CH_LOAD,
	CH_DEFAULT, //reset the game settings to the default values.
	CH_MOVE,
	CH_PRINT_SETTING,
	CH_QUIT,
	CH_START,
	CH_SAVE,
	CH_RESET,
	CH_INVALID_LINE,
}CH_SETTING_COMMAND;



// This struct used to store all relevant data from parsed line
// default val are 0;
typedef struct setting_command{
	CH_SETTING_COMMAND cmd;
	bool validArg; //is set to true if the line contains a valid argument
	int arg;
	OrderedPair from; // in some commands we have to save ordered pairs.
	OrderedPair to;
	char path [CH_MAX_LINE_LENGTH]; // in order the save/load command
} Setting_Command;


/**
 * the function build an default commnd in the struct of setting_command. it doesn't get nothing.
 * but the function put the dafualt values for every varibale.
 * @retrun
 * setting cammand with default values.
 */
Setting_Command initDefaultCommand();

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
Setting_Command chParseLine(const char* str, bool settingMode, bool gameMode);


/*
 * the traget of the function is to update an specific command in the legal values of it, such as validard and arg.
 * the function get an setting_commnd, CH_SETTING_COMMAND - a specific command, and argument.
 * @return
 * 	an update Setting_command.
 */
Setting_Command updateCommand( CH_SETTING_COMMAND CH_command, int arg, bool settingMode, bool gameMode);

/**
 * Checks if a specified string represents a valid integer. It is recommended
 * to use this function prior to calling the standard library function atoi.
 *
 * @return
 * true if the string represents a valid integer, and false otherwise.
 */
bool chParserIsInt(const char* str);

/**
 * Checks if a specified string represents a valid shape of ordered pair <x,y> of the index in the table.
 *
 * @return
 * true if the string represents a valid shape of ordered pair <x,y>, and false otherwise.
 */
bool chParserIsCouple( const char*str );

/*
 * the command prints ""Invalid position on the board".
 * */
void print_invalidPos();

#endif /* CON_FUNC__PARSER_H_ */
