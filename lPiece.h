#ifndef LPIECE_H
#define LPIECE_H
#include "pieces.h"
#include <iostream>
#include <vector>

class LPiece: public Pieces {
	public:
		LPiece(Board* boardPtr);
};

#endif

