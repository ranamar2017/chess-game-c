#include "CON_struct__OrderedPair.h"

/**
 * Function set new ordered pair. the function get two integers: x and y.
 * then function put the numbers in this manner: (x,y). x in the left and y in the right.
 *
 * @return
 *   the function returned Ordered pair that consist the two values (x,y).
 */
OrderedPair setOrderedPair(int x, int y){
	OrderedPair pair;
	pair.x = x;
	pair.y = y;
	return pair;
}
