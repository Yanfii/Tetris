#include <sstream>
#include <string>
#include "graphicsdisplay.h"
#include "info.h"
#include "subject.h"
#include "board.h"
#include "pieces.h"
using namespace std;

const int cellSize = 18;

void GraphicsDisplay::drawNext(Block bType) {
	xw.fillRectangle(0,324,200,56,Xwindow::White);
	xw.drawBigString(0,340, "Next:");
	if (bType == Block::IBlock) {
		xw.fillRectangle(0,358, cellSize,cellSize,Xwindow::Orange);
		xw.fillRectangle(18,358, cellSize,cellSize,Xwindow::Orange);
		xw.fillRectangle(36,358, cellSize,cellSize,Xwindow::Orange);
		xw.fillRectangle(54,358, cellSize,cellSize,Xwindow::Orange);
	}
	else if (bType == Block::JBlock){
		xw.fillRectangle(0,340, cellSize,cellSize,Xwindow::Red);
		xw.fillRectangle(0,358, cellSize,cellSize,Xwindow::Red);
		xw.fillRectangle(18,358, cellSize,cellSize,Xwindow::Red);
		xw.fillRectangle(36,358, cellSize,cellSize,Xwindow::Red);
	}
	else if (bType == Block::LBlock) {
		xw.fillRectangle(36,340, cellSize,cellSize,Xwindow::Green);
		xw.fillRectangle(0,358, cellSize,cellSize,Xwindow::Green);
		xw.fillRectangle(18,358, cellSize,cellSize,Xwindow::Green);
		xw.fillRectangle(36,358, cellSize,cellSize,Xwindow::Green);	
	}
	else if (bType == Block::OBlock) {
		xw.fillRectangle(0,340, cellSize,cellSize,Xwindow::Blue);
		xw.fillRectangle(18,340, cellSize,cellSize,Xwindow::Blue);
		xw.fillRectangle(0,358, cellSize,cellSize,Xwindow::Blue);
		xw.fillRectangle(18,358, cellSize,cellSize,Xwindow::Blue);	
	} 
	else if (bType == Block::SBlock) {
		xw.fillRectangle(18,340, cellSize,cellSize,Xwindow::Cyan);
		xw.fillRectangle(36,340, cellSize,cellSize,Xwindow::Cyan);
		xw.fillRectangle(0,358, cellSize,cellSize,Xwindow::Cyan);
		xw.fillRectangle(18,358, cellSize,cellSize,Xwindow::Cyan);	
	}
	else if (bType == Block::ZBlock) {
		xw.fillRectangle(0,340, cellSize,cellSize,Xwindow::Yellow);
		xw.fillRectangle(18,340, cellSize,cellSize,Xwindow::Yellow);
		xw.fillRectangle(18,358, cellSize,cellSize,Xwindow::Yellow);
		xw.fillRectangle(36,358, cellSize,cellSize,Xwindow::Yellow);		
	}
	else if (bType == Block::TBlock) {
		xw.fillRectangle(0,340, cellSize,cellSize,Xwindow::Magenta);
		xw.fillRectangle(18,340, cellSize,cellSize,Xwindow::Magenta);
		xw.fillRectangle(36,340, cellSize,cellSize,Xwindow::Magenta);
		xw.fillRectangle(18,358, cellSize,cellSize,Xwindow::Magenta);	
	}
	else {
		return;
	}
}

GraphicsDisplay::GraphicsDisplay(Board *boardPtr): boardPtr{boardPtr} ,xw{200,375}, w2{200,200}  {
	nextBlock = boardPtr->nextPiece->getBlockType(); // get next block type
	xw.fillRectangle(0,0,200,324,Xwindow::Black); // the main board
	drawNext(nextBlock);
	w2.fillRectangle(0, 0, 200,200, Xwindow::White); // the score board
	int lv = boardPtr->level;
	int curScore = boardPtr->score;
	int hiScore = boardPtr->score;
	ostringstream ss;
	ss << lv;
	string lev  = ss.str();
	w2.drawBigString(0, 15, "Level:    ");
	w2.drawBigString(100, 15, lev); // this should be the level
	ostringstream ss2;
	ss2 << curScore;
	string boardScore  = ss2.str();
	w2.drawBigString(0, 98, "Score:    ");
	w2.drawBigString(100, 98, boardScore); // this should be the current score
	ostringstream ss3;
	ss3 << hiScore;
	string boardHiscore  = ss3.str();
	w2.drawBigString(0, 198, "Hi Score:    ");
	w2.drawBigString(100, 198, boardHiscore); // this should be the high score
}

void GraphicsDisplay::notify(Subject &whoNotified) {
	Block realNext = boardPtr->nextPiece->getBlockType();
	if (realNext != nextBlock) {
		nextBlock = realNext;
		drawNext(nextBlock);
	}
	Info cellInfo = whoNotified.getInfo();
	switch(cellInfo.block) {
		case Block::IBlock:
		xw.fillRectangle(cellInfo.column * cellSize, cellInfo.row * cellSize, cellSize, cellSize, Xwindow::Orange);
		break;
		case Block::JBlock:
		xw.fillRectangle(cellInfo.column * cellSize, cellInfo.row * cellSize, cellSize, cellSize, Xwindow::Red);
		break;
		case Block::LBlock:
		xw.fillRectangle(cellInfo.column * cellSize, cellInfo.row * cellSize, cellSize, cellSize, Xwindow::Green);
		break;
		case Block::OBlock:
		xw.fillRectangle(cellInfo.column * cellSize, cellInfo.row * cellSize, cellSize, cellSize, Xwindow::Blue);
		break;
		case Block::SBlock:
		xw.fillRectangle(cellInfo.column * cellSize, cellInfo.row * cellSize, cellSize, cellSize, Xwindow::Cyan);
		break;
		case Block::ZBlock:
		xw.fillRectangle(cellInfo.column * cellSize, cellInfo.row * cellSize, cellSize, cellSize, Xwindow::Yellow);
		break;
		case Block::TBlock:
		xw.fillRectangle(cellInfo.column * cellSize, cellInfo.row * cellSize, cellSize, cellSize, Xwindow::Magenta);
		break;
		case Block::starBlock:
		xw.fillRectangle(cellInfo.column * cellSize, cellInfo.row * cellSize, cellSize, cellSize, Xwindow::Brown);
		break;
		default:
		xw.fillRectangle(cellInfo.column * cellSize, cellInfo.row * cellSize, cellSize, cellSize, Xwindow::Black);
	}
}

void GraphicsDisplay::changeScore(Board &whoNotified) { // this function is called when there is score change 
	
	w2.fillRectangle(0,0,200,200,Xwindow::White); // redraw the score board
	int lv = boardPtr->level;
	int curScore = boardPtr->score;
	int hiScore = boardPtr->score;
	ostringstream ss;
	ss << lv;
	string lev  = ss.str();
	w2.drawBigString(0, 15, "Level:    ");
	w2.drawBigString(100, 15, lev); // this should be the level
	ostringstream ss2;
	ss2 << curScore;
	string boardScore  = ss2.str();
	w2.drawBigString(0, 98, "Score:    ");
	w2.drawBigString(100, 98, boardScore); // this should be the current score
	ostringstream ss3;
	ss3 << hiScore;
	string boardHiscore  = ss3.str();
	w2.drawBigString(0, 198, "Hi Score:    ");
	w2.drawBigString(100, 198, boardHiscore); // this should be the high score
	
}


