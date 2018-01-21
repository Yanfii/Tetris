#include <string>
#include "cell.h"
#include "info.h"


Cell::Cell(int r, int c):r{r}, c{c} {}

void Cell::setPiece(Block block, bool isActive, bool isDropped, Difficulty level, int id) {
	State theState{block, isActive, isDropped, level, id};
	this->setState(theState);
	notifyObservers();
}


Info Cell::getInfo() const{
	Block newB = getState().block;
	bool status = getState().isActive;
	bool drop = getState().isDropped;
	Difficulty diffLevel = getState().level;
	int idNum = getState().id;
	Info ret{r, c, newB, status, drop, diffLevel, idNum};
	return ret;
}

