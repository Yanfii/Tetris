#ifndef INFO_H
#define INFO_H
#include "state.h"
struct Info {
	int row, column;
	Block block;
	bool isActive;
	bool isDropped;
	Difficulty level;
	int id;
};

#endif

