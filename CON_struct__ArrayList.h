#ifndef CON_STRUCT__ARRAYLIST_H_
#define CON_STRUCT__ARRAYLIST_H_

#include <stdbool.h>

#include "CON_struct__HistoryCell.h"


// a struct that his traget is to represent an array list that include history cells. in addiation, there is fields for actuaal size and max size.
typedef struct ch_array_list {
	historyCell* elements;
	int actualSize;
	int maxSize;
} CHArrayList;


// enum to describe possible modifying results of array_list struct..
typedef enum ch_array_list_message {
	CH_ARRAY_LIST_SUCCESS,
	CH_ARRAY_LIST_INVALID_ARGUMENT,
	CH_ARRAY_LIST_FULL,
	CH_ARRAY_LIST_EMPTY
} CH_ARRAY_LIST_MESSAGE;



/**
 *  Creates an empty array list with the specified maximum capacity.
 *  @param maxSize - the maximum capacity of the target array list.
 *  @return
 *  NULL, if an allocation error occurred or maxSize  <= 0.
 *  An instant of an array list otherwise.
 */
CHArrayList* chArrayListCreate(int maxSize);

/**
 *	Copy all src array list elements to destination array list
 *	in the same order as they appeared in the source list.
 *	@param from - the source array list, to - destination array list
 *	@return
 *	CH_ARRAY_LIST_INVALID_ARGUMENT if either an allocation error occurs or src == NULL.
 *	CH_ARRAY_LIST_SUCCESS otherwise.
 */
CH_ARRAY_LIST_MESSAGE chArrayListCopy(CHArrayList* from, CHArrayList* to);

/**
 * Frees all memory resources associated with the source array list. If the
 * source array is NULL, then the function does nothing.
 * @param src - the source array list
 */
void chArrayListDestroy(CHArrayList* src);

/**
 * Invalidate all elements of the source array list. After invoking this function,
 * the size of the source list will be reduced to zero and maximum capacity is
 * not affected.
 * @param src - the source array list
 * @return
 * CH_ARRAY_LIST_INVALID_ARGUMENT if src == NULL
 * CH_ARRAY_LIST_SUCCESS otherwise
 */
CH_ARRAY_LIST_MESSAGE chArrayListClear(CHArrayList* src);


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
CH_ARRAY_LIST_MESSAGE chArrayListAddAt(CHArrayList* src, historyCell elem, int index);

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
CH_ARRAY_LIST_MESSAGE chArrayListAddFirst(CHArrayList* src, historyCell elem);

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
CH_ARRAY_LIST_MESSAGE chArrayListAddLast(CHArrayList* src, historyCell elem);


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
CH_ARRAY_LIST_MESSAGE chArrayListRemoveAt(CHArrayList* src, int index);

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
CH_ARRAY_LIST_MESSAGE chArrayListRemoveFirst(CHArrayList* src);

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
CH_ARRAY_LIST_MESSAGE chArrayListRemoveLast(CHArrayList* src);

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
historyCell chArrayListGetAt(CHArrayList* src, int index);


/**
 * Returns the element at the beginning of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL or the list is empty
 * Otherwise, the element at the beginning of the list is returned.
 */
historyCell chArrayListGetFirst(CHArrayList* src);

/**
 * Returns the element at the end of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL or the list is empty
 * Otherwise, the element at the end of the list is returned.
 */
historyCell chArrayListGetLast(CHArrayList* src);

/**
 * Returns the maximum capacity of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL
 * Otherwise, the maximum capacity of the list is returned.
 */
int chArrayListMaxCapacity(CHArrayList* src);

/**
 * Returns the number of elements in the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL
 * Otherwise, the number of the elements in the list is returned.
 */
int chArrayListSize(CHArrayList* src);

/**
 * Returns true if the list is full, that is the number of elements in the list
 * equals its maximum capacity.
 * @param src - the source array list
 * @return
 * false if either src == NULL or the number of elements in the list is less
 * than its maximum capacity.
 * Otherwise, true is returned.
 */
bool chArrayListIsFull(CHArrayList* src);

/**
 * Returns true if the list is empty, that is the number of elements in the list
 * equals to zero.
 * @param src - the source array list
 * @return
 * false if either src == NULL or the number of elements in the list is not zero.
 * Otherwise, true is returned.
 */
bool chArrayListIsEmpty(CHArrayList* src);


#endif
