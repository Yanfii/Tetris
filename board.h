#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include "info.h"
#include <map>
#include "state.h"

class TextDisplay;
class GraphicsDisplay;
class Cell;
class Pieces;
class IPiece;
class Observer;

class Board{
	const int row = 18;
	const int col = 11;
	int starCounter = 0;
	std::map<int, Difficulty> blockDic;
	int blockNum = 0; // increase this by one when a new piece is created(piece's responsibility to increase this)
	const int maxLevel = 4;
	const int minLevel = 0;
	std::string fileName;
	int curLevelZeroBlock;
	int curRandomBlock;
	int level;
	Difficulty curDiff;
	int score;
	int highScore;
	bool isRandom;
	std::string noRandomFileName;
	bool isGraphic; // use graphic or not
	std::vector<std::vector<Cell>> theBoard; // actual cells
	std::shared_ptr<GraphicsDisplay> ob;// observer for graphics
	std::shared_ptr<TextDisplay> td; //textdisplay
public:
	Board();
	std::unique_ptr<Pieces> curPiece;
	std::unique_ptr<Pieces> nextPiece;
	void notify(Pieces &whoNotified);
	void setObserver(std::shared_ptr<GraphicsDisplay> ob);
	void setLeveL(int level);
	void setFileName(std::string file);
	void seedRNG(int seed);
	void init(); // initialize the board properly(including reset the board)
	void clearRow(int stopRow);
	void checkRow(); // check if there is any row that is filled after dropping current block and clear those that is full
	int getScore();
	std::unique_ptr<Pieces> createPiece();
	bool isFull();
	int getLevel();
	int getStarCounter();
	int getBlockNum();
	void setStarPiece();
	void setHintPiece();
	Pieces getPiece(Command c);
	void setLevel(int lev);
	void graphSwitch(bool displayGraph);
	void randomize();
	void unRandomize();
	void setNoRandomFileName(std::string fileName);
	void setCurrentPiece(std::unique_ptr<Pieces> &);
	friend class Pieces;
	friend class IPiece;
	friend class JPiece;
	friend class LPiece;
	friend class OPiece;
	friend class SPiece;
	friend class ZPiece;
	friend class TPiece;
	friend class GraphicsDisplay;
	friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif

