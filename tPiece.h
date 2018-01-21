#ifndef TPIECE_H
#define TPIECE_H
#include "pieces.h"
#include <iostream>
#include <vector>

class TPiece: public Pieces {
	public:
		TPiece(Board* boardPtr);
};

#endif
