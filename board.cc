#include <cstdlib>
#include "board.h"
#include "textdisplay.h"
#include "cell.h"
#include "observer.h"
#include "graphicsdisplay.h"
#include "interpreter.h"
#include "iPiece.h"
#include "jPiece.h"
#include "lPiece.h"
#include "oPiece.h"
#include "sPiece.h"
#include "tPiece.h"
#include "zPiece.h"
using namespace std;
//blockDic
Board::Board(): highScore {0} {
	level = 0;
	curLevelZeroBlock = 1;
	curRandomBlock = 1;
	// Seed the random number generator
	srand(time(NULL));
	// Set the fileName
	fileName = "sequence.txt";

}

void Board::setStarPiece() {
	int column = 5;
	int currentRow = 3;

	while(currentRow + 1 < 18 && theBoard[currentRow + 1][column].getInfo().block == Block::None && theBoard[currentRow + 1][column].getInfo().isActive == false) {
		++currentRow;
	}
	theBoard[currentRow][column].setPiece(Block::starBlock, false, true, curDiff, blockNum);
	theBoard[currentRow][column].notifyObservers();
}

int Board::getStarCounter() {
	return starCounter;
}
void Board::setHintPiece() {
}

void Board::notify(Pieces &whoNotified) { // whoNotified here is a piece
	// Step 1: Remove all active cells
	for (int r = 0; r < 18; ++r) {
		for (int c = 0; c < 11; ++c) {
			if (theBoard[r][c].getInfo().isActive) {
				State newS {Block::None, false, false,theBoard[r][c].getInfo().level, theBoard[r][c].getInfo().id};
				theBoard[r][c].setState(newS); // if the cell is active then delete it(change the block to None)
				theBoard[r][c].notifyObservers(); //notify the display class
			}
		}
	}
	// Step 2: Fill out the grid with new active pieces
	bool callDropped = false;
	for (int r = 0; r < 5; ++r) {
		for (int c = 0; c < 5; ++c) {
			Cell singleCell = whoNotified.piece[r][c]; // get the cells from 5*5, if the block is not none ,update the board
			if (singleCell.getInfo().block != Block::None) { 
				int rowNum = singleCell.getInfo().row;
				int colNum = singleCell.getInfo().column;
				State newS {singleCell.getInfo().block, true, 
					singleCell.getInfo().isDropped, singleCell.getInfo().level, singleCell.getInfo().id};
				theBoard[rowNum][colNum].setState(newS);
				theBoard[rowNum][colNum].notifyObservers(); //notify the display class
			}
			// once we found something with the drop command we set callDropped to true
			if (singleCell.getInfo().isDropped) callDropped = true;
		}
	}
	// Step 3: Remove rows, only if the command is dropped
	if (callDropped) {
		for(int r = 0; r < 18; ++r) {
			for (int c = 0; c < 11; ++c) {
				if (theBoard[r][c].getInfo().isActive){
					State newS = {theBoard[r][c].getInfo().block, false, 
						theBoard[r][c].getInfo().isDropped, theBoard[r][c].getInfo().level,
						 theBoard[r][c].getInfo().id};
					theBoard[r][c].setState(newS);
					theBoard[r][c].notifyObservers();
				}
			}
		}
		// have to set everything inactive once call dropped(incomplete)
		checkRow();
	}

}


void Board::setObserver(shared_ptr<GraphicsDisplay> ob) {
	this->ob = ob;
	for (int r = 0; r < 18; ++r) {
		for (int c = 0; c < 11; ++c){
			theBoard[r][c].attach(ob); // attach this observer to every cell on the board
		}
	}
}

void Board::setCurrentPiece(unique_ptr<Pieces> &p) {
	p->shift(0, 0);
}

void Board::init() {
	td = make_shared<TextDisplay>(18,11);
	vector<vector<Cell>> newBoard;
	for (int r = 0; r < 18; ++r) { //fill in the board with empty cells
		vector<Cell> cellArr;
		for (int c = 0; c < 11; ++c) {
			Cell toPush{r, c};
			toPush.attach(td);
			cellArr.emplace_back(toPush);
		}
		newBoard.emplace_back(cellArr);
	}
	// Set theBoard to equal newBoard, reset the Level and Score. 
	// Highscore remains the same
	theBoard = newBoard;
	level = 0;
	score = 0;
	curRandomBlock = 1;
	isRandom = true;
	curLevelZeroBlock = 1;
	// Create the current, and next piece
	curPiece = createPiece();
	nextPiece = createPiece();
	setCurrentPiece(curPiece);
	if (isGraphic) {
	 ob = make_shared<GraphicsDisplay>(this); // let ob point to the board if we turn off textOnly
	 setObserver(ob);
	}
	setCurrentPiece(curPiece);
}

int Board::getLevel() { return level; }
void Board::graphSwitch(bool displayGraph) {
	if (displayGraph) isGraphic = true;
	if (!displayGraph) isGraphic = false;
}

int Board::getBlockNum() {
	return blockNum;
}

void Board::setLevel(int lev) {
	level = lev;
	if (lev <= 0) {
		level = 0;
		curDiff = Difficulty::Level0;
	}
	if (lev == 1) curDiff = Difficulty::Level1;
	if (lev == 2) curDiff = Difficulty::Level2;
	if (lev == 3) curDiff = Difficulty::Level3;
	if (lev >= 4) {
		level = 4;
		curDiff = Difficulty::Level4;
	}
	if (isGraphic) ob->changeScore(*this);
}

void Board::setFileName(string file) { fileName = file; }

void Board::seedRNG(int seed) { srand(seed); }

void Board::randomize() { isRandom = true; }

void Board::unRandomize() { isRandom = false; }

void Board::setNoRandomFileName(string fileName) { noRandomFileName = fileName; }

// This helper will return the desired block given a Command
Pieces Board::getPiece (Command c) {
	if (c == Command::I) {
		return IPiece(this);
	} else if (c == Command::J) {
		return JPiece(this);
	} else if (c == Command::L) {
		return LPiece(this);
	} else if (c == Command::O) {
		return OPiece(this);
	} else if (c == Command::S) {
		return SPiece(this);
	} else if (c == Command::Z) {
		return ZPiece(this);
	} else if (c == Command::T) {
		return TPiece(this);
	} else {
		return IPiece(this);
	}
}

// This will return a pointer to a block
unique_ptr<Pieces> Board::createPiece() {
	Interpreter i = Interpreter();
	// Do the ++idCounter or some shit here, if we choose to do it
	switch (level) {
		// We'll want to check what level we're on, as the behaviour is contingent on it
		case 0: {
			// Here, we just read from a file
			ifstream infile;
			infile.open(fileName);
			string block;
			for (int i = 0; i < curLevelZeroBlock; ++i) {
				// We want to loop until we get the desired block
				infile >> block;
				// Maybe do some more error checking?
				if (infile.eof()) {
					// Set the counter back to 1
					curLevelZeroBlock = 1;
				}
			}
			// Indicate that we retrieved a block
			++curLevelZeroBlock;
			Command c = i.getCommand(block).second;
			return make_unique<Pieces>(getPiece(c));
		}	
		case 1: {
			// Choose a number between 0 and 11
			int num = rand() % 12;
			switch (num) {
				// Skewed to be 1/12 Probability
				case 0:
					// Return an S piece
					return make_unique<Pieces>(SPiece(this));
				// Also skewed to be 1/12 Probability
				case 1:
					// Return a Z piece
					return make_unique<Pieces>(ZPiece(this));
				// Everything else here is 1/6 probability
				case 2: case 3:
					return make_unique<Pieces>(IPiece(this));
				case 4: case 5:
					return make_unique<Pieces>(JPiece(this));
				case 6: case 7:
					return make_unique<Pieces>(LPiece(this));
				case 8: case 9:
					return make_unique<Pieces>(OPiece(this));
				case 10: case 11:
					return make_unique<Pieces>(TPiece(this));
			}
		}
		case 2: {
			// Here, all blocks are selected w/ equal Probability
			int num = rand() % 7;
			switch (num) {
				case 0:
					return make_unique<Pieces>(SPiece(this));
				case 1:
					return make_unique<Pieces>(ZPiece(this));
				case 2:
					return make_unique<Pieces>(IPiece(this));
				case 3:
					return make_unique<Pieces>(JPiece(this));
				case 4:
					return make_unique<Pieces>(LPiece(this));
				case 5:
					return make_unique<Pieces>(OPiece(this));
				case 6:
					return make_unique<Pieces>(TPiece(this));
			}
		}
		case 3: case 4: {
			// Check if we have the random flag enabled
			if (isRandom) {
				// S and Z have probability 2/9, other blocks are 1/9
				int num = rand() % 9;
				switch (num) {
					case 0: case 1:
						return make_unique<Pieces>(SPiece(this));
					case 2: case 3:
						return make_unique<Pieces>(ZPiece(this));
					case 4:
						return make_unique<Pieces>(IPiece(this));
					case 5:
						return make_unique<Pieces>(JPiece(this));
					case 6:
						return make_unique<Pieces>(LPiece(this));
					case 7:
						return make_unique<Pieces>(OPiece(this));
					case 8:
						return make_unique<Pieces>(ZPiece(this));
				}
			} else {
				// Otherwise, read in from the random file
				ifstream infile;
				infile.open(noRandomFileName);
				string block;
				for (int i = 0; i < curRandomBlock; ++i) {
					// We want to loop until we get the desired block
					infile >> block;
					// Maybe do some more error checking?
					if (infile.eof()) {
						// Set the counter back to 1
						curRandomBlock = 1;
					}
				}
				// Indicate that we retrieved a block
				++curRandomBlock;
				Command c = i.getCommand(block).second;
				return make_unique<Pieces>(getPiece(c));	
			}
		}
		default: {
			return make_unique<Pieces>(LPiece(this));
		}
	}
	return make_unique<Pieces>(LPiece(this));
}

void Board::clearRow(int stopRow) {
	for (int r = stopRow - 1; r >= 3; --r) { // started from the row that is above the current row
		for (int c = 0; c < 11; ++c) {
			Info cellInfo = theBoard[r][c].getInfo();
				State newS {cellInfo.block, cellInfo.isActive, cellInfo.isDropped, cellInfo.level,cellInfo.id};
				// push down all cells above the stoprow 
				theBoard[r+1][c].setState(newS);
				theBoard[r+1][c].notifyObservers();
		}
	}

}

void Board::checkRow() {
	bool isClear = false;
	for (int r  = 3; r < 18; ++r) {
		bool isRowFilled = true; 
		for (int c = 0; c < 11; ++c) {
			//once we encounter some cells whose block is none, then we found a empty cell
			if (theBoard[r][c].getInfo().block == Block::None) isRowFilled = false;
		}	
		if (isRowFilled) { // This row is filled. We have to clear them
			clearRow(r);
			isClear = true;
			//now increse the score
			score = score + (level+1) * (level+1); // score for clearing one single row
		}
		// if clearRow is called create a new map on current board and compare that with blockDic
	}
	if (isClear) {
		map<int, Difficulty> curBlocks;
		for(int r = 0; r < 18; ++r) {
			for(int c = 0; c < 11; ++c) {
				// create a new map which has current blocks
				Info cellInfo = theBoard[r][c].getInfo();
				curBlocks[cellInfo.id] = cellInfo.level;
			}
		}
		// now, you have to compare all blocks to curblocks to see if anything is missing
		for (map<int, Difficulty>::iterator it = blockDic.begin(); it != blockDic.end(); ++it) {
			// if keys form blockDic don't appear in curBlocks, we have to increase score
			if (curBlocks.count(it->first) == 0) {
				int level2; 
				// now see which level is the block 
				if (it->second == Difficulty::Level0) level2 = 0;
				else if (it->second == Difficulty::Level1) level2 = 1;
				else if (it->second == Difficulty::Level2) level2 = 2;
				else if (it->second == Difficulty::Level3) level2 = 3;
				else if (it->second == Difficulty::Level4) level2 = 4;
				score = score + (level2+1) * (level2+1);

				// finally, erase that block in blockDic so we don't double count next time
				blockDic.erase(it->first);
			}
		}
	}


	if (score >= highScore) highScore = score;
	if (isGraphic) ob->changeScore(*this); // tell graphicdisplay the score has updated
}

bool Board::isFull() {
	//check through each cell in the first three rows and see
	// if any cell has block that's not none or active
	for(int r = 3; r < 4; ++r) {
		for(int c = 0; c < 4; ++c) {
			if ((theBoard[r][c].getInfo().block != Block::None)
				&& (!theBoard[r][c].getInfo().isActive)) return true;
		}
	}
	return false;
}

std::ostream &operator<<(std::ostream &out, const Board &b) {
	out << "Level:      " << b.level << endl;
	out << "Score:      " << b.score << endl;
	out << "Hi Score:   " << b.highScore << endl;
	out << "------------" << endl;
	out << endl;
	out << *(b.td);
	out << "Next:"<<endl;
	Block blockType = (b.nextPiece)->getBlockType();
	if (blockType == Block::IBlock) out << endl <<"IIII"<<endl;
	if (blockType == Block::JBlock) out << "J   "<< endl <<"JJJ"<<endl;
	if (blockType == Block::LBlock) out << "  L"<< endl <<"LLL"<<endl;
	if (blockType == Block::OBlock) out << "OO"<< endl << "OO"<<endl;
	if (blockType == Block::SBlock) out << " SS"<<endl << "SS "<<endl;
	if (blockType == Block::ZBlock) out << "ZZ "<<endl << " ZZ"<<endl;
	if (blockType == Block::TBlock) out << "TTT"<<endl << " T "<<endl;
	out << "------------" << endl;
	return out;
}


