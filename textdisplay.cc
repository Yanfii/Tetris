#include "textdisplay.h"
#include "state.h"
#include "info.h"
#include "cell.h"
using namespace std;

TextDisplay::TextDisplay(int row, int col): row{row}, col{col} {
	for (int r = 0; r < row; ++r) {
		vector<char> charArr;
		for (int c = 0; c < col; ++c) {
			charArr.emplace_back(' '); // 
		}
		theDisplay.emplace_back(charArr);
	}
}

void TextDisplay::notify(Subject &whoNotified) {
	Info cellInfo = whoNotified.getInfo();
	int rowNum = cellInfo.row;
	int colNum = cellInfo.column; 
	Block theBlock = cellInfo.block;
	if (theBlock == Block::IBlock) theDisplay[rowNum][colNum] = 'I';
	else if (theBlock == Block::JBlock) theDisplay[rowNum][colNum] = 'J';
	else if (theBlock == Block::LBlock) theDisplay[rowNum][colNum] = 'L';
	else if (theBlock == Block::OBlock) theDisplay[rowNum][colNum] = 'O';
	else if (theBlock == Block::SBlock) theDisplay[rowNum][colNum] = 'S';
	else if (theBlock == Block::ZBlock) theDisplay[rowNum][colNum] = 'Z';
	else if (theBlock == Block::TBlock) theDisplay[rowNum][colNum] = 'T';
	else if (theBlock == Block::starBlock) theDisplay[rowNum][colNum] = '*';
	else theDisplay[rowNum][colNum] = ' '; // replace this with space when this class is done
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
	for (int r = 0; r < td.row; ++r) {
		for (int c = 0; c < td.col; ++c) {
			out << td.theDisplay[r][c];
		}
		out << '\n';
	}
	return out;
}
