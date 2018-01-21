#ifndef PIECES_H
#define PIECES_H
#include <vector>
#include <memory>
#include "state.h"

class Board;
class Cell;

class Pieces{
	int rowSize = 5;
	int colSize = 5;
protected:
	 Board* boardPtr;
	 std::vector<std::vector<Cell>> piece;
	 Block block;
	 int xPivot = 2;
	 int yPivot = 2;
public:
	Pieces(Board* boardPtr);
	void shift(int x, int y);
	void matrixRotation(int x00, int x01, int x10, int x11);
	virtual void rotate(Direction direction);
	void movePiece(Direction direction);
	bool isValidMove();
	bool checkValidMove(Board* boardPtr, std::vector<std::vector<Cell>>);
	Block getBlockType();
	friend class Board;

};

#endif

