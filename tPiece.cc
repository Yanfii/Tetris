#include "tPiece.h"
#include "cell.h"
#include "board.h"
#include <vector>
using namespace std;


TPiece::TPiece(Board* boardPtr): Pieces{boardPtr} {
	block = Block::TBlock;
	xPivot = 2;
	yPivot = 1;
	for(int row = 0; row < 5; ++row) {
		for(int col = 0; col < 5; ++col) {
			if((row == 2 && col == 0) || (row == 2 && col == 1) || 
				(row == 2 && col == 2) || (row == 3 && col == 1)) {
				//assign the JBlock cell to the following coordinates
				piece[row][col].setPiece(Block::TBlock, true, false, boardPtr->curDiff, boardPtr->blockNum);
			}
			else {
				piece[row][col].setPiece(Block::None, true, false, boardPtr->curDiff, boardPtr->blockNum);
			}
		}
	}
};

