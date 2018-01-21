#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"

class Cell;
class Subject;

class TextDisplay: public Observer {
	std::vector<std::vector<char>> theDisplay;
	const int row;
	const int col;
public:
	TextDisplay(int row, int col);
	void notify(Subject &whoNotified) override;
	
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif

