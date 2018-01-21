#ifndef OPIECE_H
#define OPIECE_H
#include "pieces.h"
#include <iostream>
#include <vector>

class OPiece: public Pieces {
	public:
		OPiece(Board* boardPtr);
		void rotate(Direction direction) override;
};

#endif
