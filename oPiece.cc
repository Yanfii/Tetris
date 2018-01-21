#include "oPiece.h"
#include "cell.h"
#include "board.h"
#include <vector>
using namespace std;


OPiece::OPiece(Board* boardPtr): Pieces{boardPtr} {
	block = Block::OBlock;
	xPivot = 3;
	yPivot = 1;
	for(int row = 0; row < 5; ++row) {
		for(int col = 0; col < 5; ++col) {
			if((row == 2 && col == 0) || (row == 3 && col == 0) || 
				(row == 2 && col == 1) || (row == 3 && col == 1)) {
				//assign the JBlock cell to the following coordinates
				piece[row][col].setPiece(Block::OBlock, true, false, boardPtr->curDiff, boardPtr->blockNum);
			}
			else {
				piece[row][col].setPiece(Block::None, true, false, boardPtr->curDiff, boardPtr->blockNum);
			}
		}
	}
}

void OPiece::rotate(Direction direction) {
	return;
}

