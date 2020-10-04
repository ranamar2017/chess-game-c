#include "CON_struct__HistoryCell.h"

/**
 * the traget of the function is to creat a new History cell. the function get the BoardCell: from,to.
 * create new history cell and put the relavnt fields with those BoardCells. in addition it change the valid filed to be 1 - it means true.
 *
 * @return
 *   a new historyCell with the relevant values.
 */
historyCell creatHistoryCell(BoardCell from, BoardCell to){

	historyCell new_HisCell;
	new_HisCell.fromCell = from;
	new_HisCell.toCell = to;
	new_HisCell.valid = 1;

	return new_HisCell;
}


/**
 * Function creat new invalid History cell, function mainly used in other function that must return HistoryCell.
 * create new history cell and put Blank board piece with 0,0 x and y coordinates.
 *
 * @return
 *   a new historyCell with the valid = 0.
 **/
historyCell invalidHistoryCell(){
	historyCell new_HisCell;
	new_HisCell.fromCell = makeBlank(0,0);
	new_HisCell.toCell = makeBlank(0,0);
	new_HisCell.valid = 0;

	return new_HisCell;

}

