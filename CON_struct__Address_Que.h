#ifndef CON_STRUCT__ADDRESS_QUE_H_
#define CON_STRUCT__ADDRESS_QUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CON_func__SaveLoad.h"

#define LOCAL_ADDRESS_SIZE 35

typedef struct addressQue{
	int used_size;
	int available_size;
	char address[5][LOCAL_ADDRESS_SIZE];
	int available_array[5];
	int used_array[5];
}addressQue;

typedef enum addressQue_message {
	que_action_invalid_argument,
	que_action_faild,
	que_action_success,
}addressQue_message;





/**
 * Creates two five size data structure, integers array,
 * which operates queue of used address and the available ones.
 * @return:
 *  	-addressQue* in case of success.
 *   	-NULL, if an allocation error occurred.
 */
addressQue* init_addressQue();


/**
 * Function save current game and update the first slot of the used array to this address number,
 * older used address will be shift one slot right in order to maintain LRU order.
 * IF used array size is smaller than 5, used array size will be increased and avilable size will be decrease at one.
 * @param
 * 		-ChessGame* game   - game to be save.
 * 		- addressQue* que - queue to save recent saved information.
 * @return addressQue_message:
 * 				que_action_invalid_argument - game or que are NULL.
 * 				else que_action_success
 */
addressQue_message que_save_at_start(ChessGame* game, addressQue* que);

/**
 * Function get index and load the game that is saved in the relevant index address slot
 * @param
 * 		-ChessGame* game   - game to be updated.
 * 		-addressQue* que   - queue that hold the access to the used address which contain game information.
 * 		-int index         - The desirable saved game index.
 * @return addressQue_message:
 * 				que_action_invalid_argument - game or que are NULL, or index is bigger than the queue size .
 * 				else que_action_success
 */
addressQue_message load_specific_game(ChessGame* game, addressQue* que, int index);


/**
 * Function shift right address represent in used array queue.
 * @param
 * 		-addressQue* que   - the saved game address queue.
 * @return addressQue_message:
 * 				que_action_invalid_argument -que param is NULL.
 * 				else que_action_success
 */
addressQue_message shift_Right_Used_Array(addressQue* que);


/**
 * Function shift left address represent in available array queue.
 * @param
 * 		-addressQue* que   - the saved game address queue.
 * @return addressQue_message:
 * 				que_action_invalid_argument -que param is NULL.
 * 				else que_action_success
 */
addressQue_message shift_Left_avilable_Array(addressQue* que);







/**
 * Function frees all memory allocated to the given address queue.
 * in case que is NULL, function does nothing.
 * @param que
 *  */
void destroy_addressQue(addressQue* que);



/**
 * Function delete oldest saved game file,
 * release its address and store it in the available address queue.
 * @param
 * 		-addressQue* que   -saved game address queue.
 * @return addressQue_message:
 * 				que_action_invalid_argument -que param is NULL, or que size is 0.
 * 				que_action_faild in case file does not exists in the given address.
 * 				else que_action_success
 */
addressQue_message clear_Last_Used_Address(addressQue* que);


/**
 * Function delete all saved games files from saved_game folder,
 * Function return the address queue to his initiation position.
 * @param
 * 		-addressQue* que   -saved game address queue.
 * @return addressQue_message:
 * 				que_action_invalid_argument -que param is NULL.
 * 				que_action_faild in case one of files does not exists in his designated address.
 * 				else que_action_success
 */
addressQue_message clear_addressQue(addressQue* que);

/**
 * Returns true if there is five saved game.
 * @param que - saved game address queue.
 * @return
 * 		false if either src == NULL or the number of saved games smaller than five.
 * 		Otherwise, true is returned.
 */
bool queIsFull(addressQue* que);
/**
 * Returns true if there is zero saved game
 * @param que - saved game address queue.
 * @return
 * 		false if either src == NULL or the number of saved games bigger than zero.
 * 		Otherwise, true is returned.
 */
bool queIsEmpty(addressQue* que);

/**
 * Function save current queue details in xml form in such order and manner
 * that allow future update any new queue to the right used address and right LRU order.
 *	@param from
 *		- ChessGame* game - game to be saved
 * @return addressQue_message:
 * 				que_action_invalid_argument -que param is NULL.
 * 				que_action_faild in case that the queue info file does not exists in his supposed address.
 * 				else que_action_success
 */
addressQue_message save_Que_Info(addressQue* que);




/**
 * Function load last used queue details from xml file.
 * in case load action was success, the queue holds the
 * right used address and right LRU order.
 * @param from
 *		- ChessGame* game - game to be saved
 * @return addressQue_message:
 * 				que_action_invalid_argument -que param is NULL.
 * 				que_action_faild in case that the queue info file does not exists in his supposed address.
 * 				else que_action_success
 */
addressQue_message load_Que_Info( addressQue* que);



/**
 * Function get  two addressQue references and
 * update one queue according to other details and order.
 *
 */
void update_Que_Info(addressQue* toQue, addressQue* fromQue);



#endif /* CON_STRUCT__ADDRESS_QUE_H_ */
