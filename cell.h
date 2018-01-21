#ifndef CELL_H
#define CELL_H
#include <iostream>
#include "subject.h"
#include "state.h"

struct Info;

class Cell: public Subject{ // cell in this question is not a observer
	int r, c;

public:
	Cell(int r, int c);

	void setPiece(Block block, bool isActive, bool isDropped,Difficulty level, int id); // set current cell to designated piece
	void movePiece(std::string cmd);
	Info getInfo() const override; // get position of current cell and the block it belongs to
	friend class Pieces;
};

#endif

