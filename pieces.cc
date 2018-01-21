#include "pieces.h"
#include <iostream>
#include <memory>
#include "info.h"
#include "cell.h"
#include "board.h"
using namespace std;

Pieces::Pieces(Board* boardPtr): boardPtr{boardPtr} {
	++(boardPtr->blockNum);
	if(boardPtr->level == 0) {
		boardPtr->blockDic[boardPtr->blockNum] = Difficulty::Level0;
	}
	else if(boardPtr->level == 1) {
		boardPtr->blockDic[boardPtr->blockNum] = Difficulty::Level1;
	}
	else if(boardPtr->level == 2) {
		boardPtr->blockDic[boardPtr->blockNum] = Difficulty::Level2;
	}
	else if(boardPtr->level == 3) {
		boardPtr->blockDic[boardPtr->blockNum] = Difficulty::Level3;
	}
	else {
		boardPtr->blockDic[boardPtr->blockNum] = Difficulty::Level4;
	}

	for(int i = 0; i < rowSize; ++i) {
		//initializing a new empty 5 by 5 vector of Cells 
		vector<Cell> row;
		for(int c = 0; c < colSize; ++c) {
			// see if this works, initialize it to i + 1
			row.emplace_back(Cell{i + 1, c});
		}
		piece.emplace_back(row);
	}
	boardPtr->notify(*this);
}

Block Pieces::getBlockType() {
	return block;
}

void Pieces::shift(int x, int y) {
	// Shift by x horizontally, and y vertically
	// Create a new vector of our current piece to perform the shift on.
	// Then check if that shift is valid.
	vector<vector<Cell>> copyPiece;
	copyPiece = piece;

	for (vector<Cell> &row: copyPiece) {
		for (Cell &cell: row) {
			cell.c += x;
			cell.r += y;
		}
	}
	// If the shift is valid, swap current pieces with the vector of Cells.
	if(checkValidMove(boardPtr, copyPiece)) {
		piece.swap(copyPiece);
		boardPtr->notify(*this);
	}
	// Shift is invalid. Do nothing.
	else {
		return;
	}
}

void Pieces::matrixRotation(int x00, int x01, int x10, int x11){
	// Take the center as the pivot
	Cell pivot = piece[xPivot][yPivot];
	vector<vector<Cell>> newPiece;
	// Create a new vector of our current piece to perform the rotation on.
	// Then check if that rotation is valid.
	for(int i = 0; i < rowSize; ++i) {
		//initializing a new empty 5 by 5 vector of Cells 
		// change pivot values here 
		vector<Cell> row;
		for(int c = 0; c < colSize; ++c) {
			row.emplace_back(Cell{i, c});
			row[c].setState({Block::None, true, false, boardPtr->curDiff, boardPtr->blockNum});
		}
		newPiece.emplace_back(row);
	}

	for(int row = 0; row < rowSize; ++row) {
		for(int col = 0; col < colSize; ++col) {
			if(piece[row][col].getInfo().block != Block::None) {
				//Step 1: Transform within the matrix
				int mRow = row - xPivot;
				int mCol = col - yPivot;
				int newMRow = (x00 * mRow) + (x01 * mCol);
				int newMCol = (x10 * mRow) + (x11 * mCol);
				int finalMRow = newMRow + xPivot;
				int finalMCol = newMCol + yPivot;

				//Step 2: Transform within the Board
				// find the current X and Y position on the Board
				int initialX = piece[row][col].getInfo().row;
				int initialY = piece[row][col].getInfo().column;
				// find the rotation matrix for the cell to be rotated
				int rotationX = initialX - pivot.getInfo().row;
				int rotationY = initialY - pivot.getInfo().column;
				//dot product operation with rotation matrix with a -90degree matrix
				int newX = (x00 * rotationX) + (x01 * rotationY);
				int newY = (x10 * rotationX) + (x11 * rotationY);
				// add the new relative vector to the pivot coordinates
				int finalX = newX + pivot.getInfo().row;
				int finalY = newY + pivot.getInfo().column;
				// set the piece
				newPiece[finalMRow][finalMCol].setPiece(block, true, false, boardPtr->curDiff, boardPtr->blockNum);
				newPiece[finalMRow][finalMCol].r = finalX;
				newPiece[finalMRow][finalMCol].c = finalY;
			}
		}
	}
	//updates the pivot cell row and column values
	newPiece[xPivot][yPivot].r = pivot.getInfo().row;
	newPiece[xPivot][yPivot].c = pivot.getInfo().column;
	// Check to see if our new representation is valid. If it is, swap with 
	// current pieces and notify board.
	if(checkValidMove(boardPtr, newPiece)) {
		piece.swap(newPiece);
		boardPtr->notify(*this);
	}
	// The rotation is invalid. Do nothing.
	else {
		return;
	}
}


void Pieces::rotate(Direction direction) {
	// Check if we want to rotate it clockwise
	if(block == Block::OBlock) {
		return;
	}
	if (direction == Direction::Clockwise) {
		// Rotation matrix for pi/2
		matrixRotation(0, 1, -1, 0);
	}
	else if (direction == Direction::CounterClockwise) {
		// Rotation matrix for -pi/2			
		matrixRotation(0, -1, 1, 0);
	}
	else
		return;
}

void Pieces::movePiece(Direction direction) {
	if(direction == Direction::Left) {
		// Shift one unit to the left in x axis
		shift(-1, 0);
	}
	else if (direction == Direction::Right) {
		// Shift one unit to the right in the x axis
		shift(1, 0);
	}
	else if (direction == Direction::Down) {
		// Shift one unit down in the y axis
		shift(0, 1);
	}
	else if (direction == Direction::Clockwise) {
		// Rotate by pi/2
		rotate(Direction::Clockwise);
	}
	else if (direction == Direction::CounterClockwise) {
		// Rotate by -pi/2
		rotate(Direction::CounterClockwise);
	}
	else if (direction == Direction::Drop) {
		for(int i = 0; i < 18; ++i) {
			shift(0, 1);
		}
		//Change the state of all blocks to true for isDropped
		for(vector<Cell> &row: piece) {
			for(Cell &cell: row) {
				if(cell.getInfo().block != Block::None) {
					cell.setState({cell.getInfo().block, true, true, cell.getInfo().level, cell.getInfo().id});
				}
			}
		}
		//Increase the number of Pieces played
		++(boardPtr->starCounter);
		// Set curPiece to be nextPiece (maybe move)

		boardPtr->curPiece.swap(boardPtr->nextPiece);
		// Create a new instance of nextPiece
		// Now let's assign the next newPiece
		unique_ptr<Pieces> newPieceTemp = boardPtr->createPiece();
		boardPtr->nextPiece.swap(newPieceTemp);
		boardPtr->notify(*this);
		boardPtr->setCurrentPiece(boardPtr->curPiece);
		
	}
	else 
		return;
}

bool Pieces::checkValidMove(Board* boardPtr, vector<vector<Cell>> copyPiece) {
	// Get the amount of rows, and columns in the board.
	int boardRow = boardPtr->row - 1;
	int boardCol = boardPtr->col - 1;
	for (vector<Cell> row: copyPiece) {
		for (Cell cell: row) {
			// Case 1: See if it's out of bounds, and occupied
			if (((cell.r > boardRow || cell.r < 0) || (cell.c > boardCol || cell.c < 0)) && (cell.getInfo().block != Block::None)) {
				return false;
			}
			// Case 2: If it's occupied, see if Board is occupied as well
			else if ((cell.getInfo().block != Block::None) 
				// Check if this indexing is right
				&& ((boardPtr->theBoard[cell.r][cell.c].getInfo().block != Block::None)) && (boardPtr->theBoard[cell.r][cell.c].getInfo().isActive == false)) {
				return false;
			}
				
		}
	}
	return true;

}
