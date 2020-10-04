#include "CON_struct__Address_Que.h"
#define MAX_INFO_LENGTH 50



/**
 * Creates two five size data structure, integers array,
 * which operates queue of used address and the available ones.
 * @return:
 *  	-addressQue* in case of success.
 *   	-NULL, if an allocation error occurred.
 */
addressQue* init_addressQue(){

	addressQue *new_Que;
	new_Que = (addressQue*) malloc( sizeof( addressQue )); //alocated memory
	if (new_Que==NULL){ return NULL;}

	new_Que->used_size = 0;
	new_Que->available_size = 5;

	strncpy( new_Que->address[0], "saved_game/1.xml" ,LOCAL_ADDRESS_SIZE );
	strncpy( new_Que->address[1],"saved_game/2.xml", LOCAL_ADDRESS_SIZE );
	strncpy( new_Que->address[2], "saved_game/3.xml" ,LOCAL_ADDRESS_SIZE );
	strncpy( new_Que->address[3], "saved_game/4.xml" ,LOCAL_ADDRESS_SIZE );
	strncpy( new_Que->address[4], "saved_game/5.xml" ,LOCAL_ADDRESS_SIZE );
	int i;
	for( i= 0; i<5 ; i++){
		new_Que->available_array[i] = i+1;
		new_Que->used_array[i] = 0;
	}
	return new_Que;
}


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
addressQue_message que_save_at_start(ChessGame* game, addressQue* que){
	if (que == NULL || game==NULL ) return que_action_invalid_argument;

	int que_size = que->used_size, address_num;

	if(que_size == 5){
		address_num = que->used_array[4];
	}
	else{
		address_num = que->available_array[0];
		shift_Left_avilable_Array(que);
		que->used_size++;
		que->available_size--;
	}

	shift_Right_Used_Array(que);
	que->used_array[0] = address_num;
	char *address = que->address[address_num-1];
	if(save_board(game, address) != action_success) return que_action_faild;

	return que_action_success;
}

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
addressQue_message load_specific_game(ChessGame* game, addressQue* que, int index){

	if (que == NULL || game == NULL || index > 5 || index < 1) return que_action_invalid_argument;
	if(index > que->used_size) return que_action_invalid_argument;


	int address_Num = que->used_array[index-1];
	if(load_game(game,que->address[address_Num-1]) != action_success){
		return que_action_faild;
	}
	return que_action_success;
}


/**
 * Function shift right address represent in used array queue.
 * @param
 * 		-addressQue* que   - the saved game address queue.
 * @return addressQue_message:
 * 				que_action_invalid_argument -que param is NULL.
 * 				else que_action_success
 */
addressQue_message shift_Right_Used_Array(addressQue* que){
	if (que == NULL) return que_action_invalid_argument;
	int i;
	for(i= 4; i > 0 ; i--){
		que->used_array[i] = que->used_array[i-1];
	}
	que->used_array[0] = 0;
	return que_action_success;
}


/**
 * Function shift left address represent in available array queue.
 * @param
 * 		-addressQue* que   - the saved game address queue.
 * @return addressQue_message:
 * 				que_action_invalid_argument -que param is NULL.
 * 				else que_action_success
 */
addressQue_message shift_Left_avilable_Array(addressQue* que){
	if (que == NULL) return que_action_invalid_argument;

	if(que->available_size == 0 ) return que_action_success;

	int i = 0;
	for(   ;  i < 4 && que->available_array[i+1] != 0 ; i++){
		que->available_array[i] = que->available_array[i+1];
	}
	que->available_array[i] = 0;
	return que_action_success;
}








/**
 * Function frees all memory allocated to the given address queue.
 * in case que is NULL, function does nothing.
 * @param que
 *  */
void destroy_addressQue(addressQue* que){ //first free the elements and then free the struct
	if(que !=NULL){
		free(que);
	}
}



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
addressQue_message clear_Last_Used_Address(addressQue* que){
	if (que == NULL) return que_action_invalid_argument;

	int used_size = que->used_size, avail_size = 5-used_size;

	if(used_size==0) return que_action_invalid_argument;

	int last_idx = que->used_array[used_size-1];
	char *address = que->address[last_idx-1];

	int delete_file_status = remove(address);
	if(delete_file_status!=0){
		printf("File can not be deleted!\n");
		return que_action_faild;
	}

	que->used_array[used_size-1] = 0;
	que->used_size--;

	que->available_array[avail_size] = last_idx;
	que->available_size++;

	return que_action_success;
}


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
addressQue_message clear_addressQue(addressQue* que){
	if (que == NULL) return que_action_invalid_argument;

	int queSize = que->used_size , del_status = 0;
	if( queSize == 0) return que_action_success;
	int i;
	for( i= 0; i<queSize ; i++){
		del_status = remove(que->address[que->used_array[i]-1]);
		if(del_status!=0){
			printf("File can not be deleted!\nFile does not exist in current directory\n");
			return que_action_faild;
		}
	}

	for(i= 0; i<5 ; i++){
		que->available_array[i] = i+1;
		que->used_array[i] = 0;
	}

	que->used_size = 0;
	que->available_size = 5;
	return que_action_success;
}


/**
 * Returns true if there is five saved game.
 * @param que - saved game address queue.
 * @return
 * 		false if either src == NULL or the number of saved games smaller than five.
 * 		Otherwise, true is returned.
 */
bool queIsFull(addressQue* que){
	if (que ==NULL|| que->used_size==5 )	return 0;
	return 1; // the list if full
}

/**
 * Returns true if there is zero saved game
 * @param que - saved game address queue.
 * @return
 * 		false if either src == NULL or the number of saved games bigger than zero.
 * 		Otherwise, true is returned.
 */
bool queIsEmpty(addressQue* que){
	if (que ==NULL|| que->used_size==0)	return 0;
	return 1;
}


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
addressQue_message save_Que_Info(addressQue* que){
	if(que == NULL) return que_action_invalid_argument ;
	FILE *ofp;
	ofp = fopen("saved_game/QUE_INFO.xml", "w");
	if (ofp == NULL){ print_saveError(); return que_action_faild ;}
	int i;
	fprintf(ofp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(ofp, "<Que_Info>\n");
	fprintf(ofp, "<used_size>%d</used_size>\n",que->used_size);
	fprintf(ofp, "<used_address> ");
	for(  i = 0 ; i < 5 ; i++){
		fprintf(ofp, "%d ",que->used_array[i]);
	}
	fprintf(ofp,"</used_address>\n");
	fprintf(ofp,"<available_size>%d</available_size>\n",que->available_size);
	fprintf(ofp,"<available_address> ");
	for(  i = 0 ; i < 5 ; i++){
		fprintf(ofp, "%d ",que->available_array[i]);
	}
	fprintf(ofp, "</available_address>\n");
	fprintf(ofp, "</Que_Info>\n");

	if (fclose(ofp) == EOF){ print_saveError();  return que_action_faild;}
	return que_action_success;
}






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
addressQue_message load_Que_Info( addressQue* que){

	if( que == NULL) return que_action_invalid_argument;

	FILE *ifp;
	ifp = fopen("saved_game/QUE_INFO.xml", "r");
	if(ifp==NULL){
		print_loadError();
		return que_action_faild;
	}

	addressQue* temp_que = init_addressQue();
	char line[MAX_INFO_LENGTH];
	int flag = 0, len, arg;

	while ( fgets(line, MAX_INFO_LENGTH, ifp) != NULL){// every cycle we take a word and compare the begging, if the begging equal, so the next is the requeired.
		if (flag == 0){
			len = strlen("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
			if( strncmp(line,  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n", len)!= 0) break;
			flag = 1;
			continue;
		}

		if (flag == 1){
			if( strncmp(line,"<Que_Info>\n",  strlen("<Que_Info>\n"))!= 0) break;
			flag = 2;
			continue;
		}
		if (flag == 2){
			len = strlen("<used_size>");
			if( strncmp(line, "<used_size>", len )!= 0) break;
			arg = line[len] -'0';
			if (arg > 5 || arg < 0) break;
			temp_que->used_size =  arg;
			flag = 3;
			continue;
		}



		if (flag == 3){//equals to 1
			len = strlen("<used_address>");
			int* arr_pointer = &temp_que->used_array[0];
			if( strncmp(line, "<used_address>", len )!= 0)  break;
			if( sscanf( line+len ," %d %d %d %d %d ", arr_pointer, arr_pointer+1, arr_pointer+2,
					arr_pointer+3, arr_pointer+4 )  != 5 ) break;
			flag = 4;
			continue;
		}

		if (flag == 4){
			len = strlen("<available_size>");
			if( strncmp(line, "<available_size>", len )!= 0) break;
			arg = line[len] -'0';
			if (arg > 5 || arg < 0) break;
			temp_que->available_size =  arg;
			flag = 5;
			continue;
		}

		if (flag == 5){
			len = strlen("<available_address>");
			int* arr_pointer = &temp_que->available_array[0];
			if( strncmp(line, "<available_address>", len )!= 0)  break;
			if( sscanf( line+len ," %d %d %d %d %d ",arr_pointer, arr_pointer+1, arr_pointer+2, arr_pointer+3,arr_pointer+4 )  != 5 ) break;

			fclose(ifp);
			update_Que_Info(que,temp_que);
			destroy_addressQue(temp_que);
			return que_action_success;
		}
	}
	print_loadError();
	fclose(ifp);
	destroy_addressQue(temp_que);
	return que_action_faild;
}



/**
 * Function get  two addressQue references and
 * update one queue according to other details and order.
 *
 */
void update_Que_Info(addressQue* toQue, addressQue* fromQue){
	toQue->available_size = fromQue->available_size;
	toQue->used_size = fromQue->used_size;
	int i;
	for( i= 0; i<5 ; i++){
		toQue->available_array[i] = fromQue->available_array[i];
		toQue->used_array[i] = fromQue->used_array[i];
	}
}



