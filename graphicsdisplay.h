#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "observer.h"
#include "state.h"
#include "window.h"
#include "info.h"
#undef None

class cell;
class Board;

class GraphicsDisplay: public Observer {
	  const int height = 380; //  (324 for blocks before next,72 for two rows of next block and 20 for next)
	  const int width = 200;
	  Board *boardPtr; // 
	  Xwindow xw;  // this is for the actual board
	  Xwindow w2; // this is for score board
	  Block nextBlock;
public:
  GraphicsDisplay(Board *boardPtr);
  void notify(Subject &whoNotified) override;
  void changeScore(Board &whoNotified);
  void drawNext(Block bType);

};

#endif

