#ifndef JPIECE_H
#define JPIECE_H
#include "pieces.h"
#include <iostream>
#include <vector>

class JPiece: public Pieces {
	public:
		JPiece(Board* boardPtr);
};

#endif
