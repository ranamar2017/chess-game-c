#ifndef CON_STRUCT__ORDEREDPAIR_H_
#define CON_STRUCT__ORDEREDPAIR_H_

//a type used to represent x,y coordinates pair.
typedef struct ordered_pair_t {
	int x;
	int y;
}OrderedPair;

/**
 * Function set new ordered pair. the function get two integers: x and y.
 * then function put the numbers in this manner: (x,y). x in the left and y in the right.
 *
 * @return
 *   the function returned Ordered pair that consist the two values (x,y).
 */
OrderedPair setOrderedPair(int x, int y);

#endif /* CON_STRUCT__ORDEREDPAIR_H_ */
