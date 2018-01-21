#ifndef IPIECE_H
#define IPIECE_H
#include "pieces.h"
#include <iostream>
#include <vector>

class IPiece: public Pieces {
	public:
		IPiece(Board* boardPtr);
};

#endif

