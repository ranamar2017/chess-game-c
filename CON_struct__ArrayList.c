#include "CON_struct__ArrayList.h"


/**
 *  Creates an empty array list with the specified maximum capacity.
 *  @param maxSize - the maximum capacity of the target array list.
 *  @return
 *  NULL, if an allocation error occurred or maxSize  <= 0.
 *  An instant of an array list otherwise.
 */
CHArrayList* chArrayListCreate(int maxSize){

	if (maxSize<=0){return NULL;}

	CHArrayList *new_list;
	new_list= (CHArrayList*) malloc( sizeof( CHArrayList )); //alocated memory
	if (new_list==NULL){ return NULL;}

	new_list->actualSize = 0;
	new_list->maxSize = maxSize;

	new_list->elements = (historyCell*)malloc(maxSize*sizeof(historyCell));
	if (new_list->elements==NULL){
		free(new_list);
		return NULL;
	}

	return new_list;
}

/**
 *	Copy all src array list elements to destination array list
 *	in the same order as they appeared in the source list.
 *	@param from - the source array list, to - destination array list
 *	@return
 *	CH_ARRAY_LIST_INVALID_ARGUMENT if either an allocation error occurs or src == NULL.
 *	CH_ARRAY_LIST_SUCCESS otherwise.
 */
CH_ARRAY_LIST_MESSAGE chArrayListCopy(CHArrayList* from, CHArrayList* to){

	if (from == NULL|| from->elements==NULL || to == NULL) return CH_ARRAY_LIST_INVALID_ARGUMENT;

	int size = from->actualSize, idx;
	for (idx = 0 ;  idx < size  ;  ++idx){    //copy the content of every cell
		*((to->elements)+idx) = *((from->elements)+idx);
	}

	to->actualSize = from->actualSize;
	return CH_ARRAY_LIST_SUCCESS;
}

/**
 * Frees all memory resources associated with the source array list. If the
 * source array is NULL, then the function does nothing.
 * @param src - the source array list
 */
void chArrayListDestroy(CHArrayList* src){ //first free the elements and then free the struct
	if(src !=NULL){
		free(src->elements);
		free(src);
	}
}

/**
 * Invalidate all elements of the source array list. After invoking this function,
 * the size of the source list will be reduced to zero and maximum capacity is
 * not affected.
 * @param src - the source array list
 * @return
 * CH_ARRAY_LIST_INVALID_ARGUMENT if src == NULL
 * CH_ARRAY_LIST_SUCCESS otherwise
 */
CH_ARRAY_LIST_MESSAGE chArrayListClear(CHArrayList* src){

	if (src==NULL || src->elements==NULL) return	CH_ARRAY_LIST_INVALID_ARGUMENT;
	if(src->actualSize == 0) return CH_ARRAY_LIST_SUCCESS;
	int i;
	int actSize = src->actualSize;
	for(i=0;  i<actSize;  i++) // all the elements became zero.
		src->elements[i].valid = 0;

	src->actualSize=0; //the struct know that he has 0 elements.
	return CH_ARRAY_LIST_SUCCESS;
}


/**
 * Inserts element at a specified index. The elements residing at and after the
 * specified index will be shifted to make place for the new element. If the
 * array list reached its maximum capacity and error message is returned and
 * the source list is not affected
 * @param src   - the source array list
 * @param elem  - the new element to be inserted
 * @param index - the index where the new element will be placed. The index is
 *                0-based.
 * @return
 * CH_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * CH_ARRAY_LIST_FULL - if the source array list reached its maximum capacity
 * CH_ARRAY_LIST_SUCCESS - otherwise
 */
CH_ARRAY_LIST_MESSAGE chArrayListAddAt(CHArrayList* src, historyCell elem, int index){
	if (src==NULL || src->actualSize<index || src-> maxSize<=index || index<0) return CH_ARRAY_LIST_INVALID_ARGUMENT;

	if (src->actualSize==src->maxSize) return CH_ARRAY_LIST_FULL;

	if (src->actualSize==0){//put the first element.
		*(src->elements)=elem;
		src->actualSize++; //increasing the array.
	}

	else{
		int counter;
		for (counter=src->actualSize-1; counter>index-1; --counter){//change the state of every cell to right.
			*((src->elements)+(counter+1))=*((src->elements)+counter);//copy the content according to that idea.
		}
		*((src->elements)+index)=elem;//put the final element
		src->actualSize++;//increasing the array.
	}
	return CH_ARRAY_LIST_SUCCESS;
}


/**
 * Inserts element at a the beginning of the source element. The elements
 * will be shifted to make place for the new element. If the
 * array list reached its maximum capacity and error message is returned and
 * the source list is not affected
 * @param src   - the source array list
 * @param elem  - the new element to be inserted
 * @return
 * CH_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * CH_ARRAY_LIST_FULL - if the source array list reached its maximum capacity
 * CH_ARRAY_LIST_SUCCESS - otherwise
 */
CH_ARRAY_LIST_MESSAGE chArrayListAddFirst(CHArrayList* src, historyCell elem){
	return chArrayListAddAt(src,elem,0); //take advantage of same general method.
}

/**
 * Inserts element at a the end of the source element. If the array list
 * reached its maximum capacity and error message is returned and the source
 * list is not affected.
 * @param src   - the source array list
 * @param elem  - the new element to be inserted
 * @return
 * CH_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * CH_ARRAY_LIST_FULL - if the source array list reached its maximum capacity
 * CH_ARRAY_LIST_SUCCESS - otherwise
 */
CH_ARRAY_LIST_MESSAGE chArrayListAddLast(CHArrayList* src, historyCell elem){
	return chArrayListAddAt(src,elem,src->actualSize); //take advantage of same general method.
}

/**
 * Removes an element from a specified index. The elements residing after the
 * specified index will be shifted to make to keep the list continuous. If the
 * array list is empty then an error message is returned and the source list
 * is not affected
 * @param src   - The source array list
 * @param index - The index from where the new element will be removed.
 *                The index is 0-based.
 * @return
 * CH_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * CH_ARRAY_LIST_EMPTY - if the source array list is empty
 * CH_ARRAY_LIST_SUCCESS - otherwise
 */
CH_ARRAY_LIST_MESSAGE chArrayListRemoveAt(CHArrayList* src, int index){
	if (src==NULL|| src->elements==NULL ||index<0 ||  src->actualSize<=index || src-> maxSize<=index){
		if(src->actualSize==0){ //check in not null and bounds.
			return CH_ARRAY_LIST_EMPTY;
		}
		return CH_ARRAY_LIST_INVALID_ARGUMENT;
	}
	int counter;
	for (counter=index ; counter <= src->actualSize-1 ; ++counter){ // shift the cells one step in order to delete.
		if(src->actualSize-1 == counter &&  src->actualSize == src->maxSize){
			src->elements[src->actualSize-1].valid =0;
		}
		else{
			*(src->elements+counter)=*(src->elements+counter+1);
		}
	}
	src->actualSize--;
	return CH_ARRAY_LIST_SUCCESS;

}

/**
 * Removes an element from a the beginning of the list.
 * The elements will be shifted to make to keep the list continuous. If the
 * array list is empty then an error message is returned and the source list
 * is not affected
 * @param src   - The source array list
 * @param elem  - The new element to be inserted
 * @return
 * CH_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL
 * CH_ARRAY_LIST_EMPTY - if the source array list is empty
 * CH_ARRAY_LIST_SUCCESS - otherwise
 */
CH_ARRAY_LIST_MESSAGE chArrayListRemoveFirst(CHArrayList* src){//take advantage of same general method.
	return chArrayListRemoveAt(src,0);
}

/**
 * Removes an element from a the end of the list.
 * The elements will be shifted to make to keep the list continuous. If the
 * array list is empty then an error message is returned and the source list
 * is not affected
 * @param src   - The source array list
 * @param elem  - The new element to be inserted
 * @return
 * CH_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL
 * CH_ARRAY_LIST_EMPTY - if the source array list is empty
 * CH_ARRAY_LIST_SUCCESS - otherwise.
 */
CH_ARRAY_LIST_MESSAGE chArrayListRemoveLast(CHArrayList* src){//take advantage of same general method.
	return chArrayListRemoveAt(src,src->actualSize-1);
}

/**
 * Returns the element at the specified index. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @param index - the specified index, the index is 0-based.
 * @return
 * Undefined value if either src == NULL or index out of bound.
 * Otherwise, the element at the specified index is returned.
 */
historyCell chArrayListGetAt(CHArrayList* src, int index){
	if (src==NULL|| src->elements==NULL || index<0 || index>src->actualSize-1)
		return invalidHistoryCell();
	return src->elements[index];//return the relevant item.
}

/**
 * Returns the element at the beginning of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL or the list is empty
 * Otherwise, the element at the beginning of the list is returned.
 */
historyCell chArrayListGetFirst(CHArrayList* src){
	return chArrayListGetAt(src,0);//take advantage of same general method.
}

/**
 * Returns the element at the end of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL or the list is empty
 * Otherwise, the element at the end of the list is returned.
 */
historyCell chArrayListGetLast(CHArrayList* src){
	return  chArrayListGetAt(src,src->actualSize-1);//take advantage of same general method.
}

/**
 * Returns the maximum capacity of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL
 * Otherwise, the maximum capacity of the list is returned.
 */
int chArrayListMaxCapacity(CHArrayList* src){
	if (src==NULL|| src->elements==NULL)
		return -1;
	return src->maxSize;//return the max ability storage of that array.
}


/**
 * Returns the number of elements in the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL
 * Otherwise, the number of the elements in the list is returned.
 */
int chArrayListSize(CHArrayList* src){
	if (src==NULL|| src->elements==NULL)
		return -1;
	return src->actualSize;//return the actual ability of that storage
}

/**
 * Returns true if the list is full, that is the number of elements in the list
 * equals its maximum capacity.
 * @param src - the source array list
 * @return
 * false if either src == NULL or the number of elements in the list is less
 * than its maximum capacity.
 * Otherwise, true is returned.
 */
bool chArrayListIsFull(CHArrayList* src){
	if (src==NULL|| src->elements==NULL || src->maxSize!=src->actualSize)
		return 0;
	return 1; // the list if full
}

/**
 * Returns true if the list is empty, that is the number of elements in the list
 * equals to zero.
 * @param src - the source array list
 * @return
 * false if either src == NULL or the number of elements in the list is not zero.
 * Otherwise, true is returned.
 */
bool chArrayListIsEmpty(CHArrayList* src){
	if (src==NULL|| src->elements==NULL || src->actualSize!=0)
		return 0;
	return 1; //the list is empty.
}





