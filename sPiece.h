#ifndef SPIECE_H
#define SPIECE_H
#include "pieces.h"
#include <iostream>
#include <vector>

class SPiece: public Pieces {
	public:
		SPiece(Board* boardPtr);
};

#endif
