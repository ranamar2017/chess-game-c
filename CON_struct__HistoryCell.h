#ifndef CON_STRUCT__HISTORYCELL_H_
#define CON_STRUCT__HISTORYCELL_H_

#include "CON_struct__GameBoard.h"


/*
* struct used to represent an history cell, which contain board move information.
* history cell contain:
* 1) fromCell: indicated where the piece was before.
* 2) toCell  : indicated where the cell is after move action.
*  in addtion there is a valid indication.
*/
typedef struct historyCell{
	BoardCell fromCell;
	BoardCell toCell;
	int valid;
}historyCell;


/**
 * the traget of the function is to creat a new History cell. the function get the BoardCell: from,to.
 * create new history cell and put the relavnt fields with those BoardCells. in addition it change the valid filed to be 1 - it means true.
 *
 * @return
 *   a new historyCell with the relevant values.
 */
historyCell creatHistoryCell(BoardCell from, BoardCell to);


/**
 * Function creat new invalid History cell, function mainly used in other function that must return HistoryCell.
 * create new history cell and put Blank board piece with 0,0 x and y coordinates.
 *
 * @return
 *   a new historyCell with the valid = 0.
 **/
historyCell invalidHistoryCell();




#endif /* CON_STRUCT__HISTORYCELL_H_ */

