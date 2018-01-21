#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "cell.h"
#include "board.h"
#include "textdisplay.h"
#include "pieces.h"
#include "iPiece.h"
#include "jPiece.h"
#include "lPiece.h"
#include "oPiece.h"
#include "sPiece.h"
#include "zPiece.h"
#include "tPiece.h"
#include "interpreter.h"
using namespace std;

void Interpret(istream &in, shared_ptr<Board> board) {
	// Parse the command
		string input;
		while (in >> input) {
		Interpreter i = Interpreter();
		pair<int, Command> commandPair = i.getCommand(input);
		int numTimes = commandPair.first;
		Command command = commandPair.second;
		// Find out if the numTimes param is valid or not
		if (command == Command::Restart) {
			// We'll have to find out what board.restart() does
			// For now, assume it's init()
			board->init();
		} else if (command == Command::Hint) {
			// Implement hint lol
		} else if (command == Command::Random) {
			// Implement random lol
			board->randomize();
		} else if (command == Command::NoRandom) {
			// Do conditional checking in generateBlock later on
			string noRandomFileName;
			in >> noRandomFileName;
			board->setNoRandomFileName(noRandomFileName);
			board->unRandomize();
		} else if (command == Command::Invalid) {
			
		} 
		else {
			// Create a new piece here, apply the transformations and check if
			// the move is invalid
			// See if this makes sense, how to make a new unique pointer
			// We are going to be applying the transformations to p
			for (int i = 0; i < numTimes; ++i) {
				// Check which command we have to run
				// Do the gameOver check here maybe? If !board.gameOver?
				if (command == Command::Left) board->curPiece->movePiece(Direction::Left);
				else if (command == Command::Right) board->curPiece->movePiece(Direction::Right);
				else if (command == Command::Down) board->curPiece->movePiece(Direction::Down);
				else if (command == Command::Clockwise) board->curPiece->rotate(Direction::Clockwise);
				else if (command == Command::CounterClockwise) board->curPiece->rotate(Direction::CounterClockwise);
				else if (command == Command::Drop) {
					board->curPiece->movePiece(Direction::Drop);
					// 5 blocks have been dropped.
					if(board->getStarCounter() % 5 == 0 && board->getLevel() == 4 && board->getStarCounter() != 0) {
						// plays the *block in the center 
						board->setStarPiece();
						board->checkRow();
						// RIGHT NOW, need to notify board since the board doesnt automatically clear the row if the * piece completes the row
					}
				}
				else if (command == Command::LevelUp) board->setLevel(board->getLevel() + 1);
				else if (command == Command::LevelDown) board->setLevel(board->getLevel() - 1);
				// curPiece->drop()
				else if (command == Command::Sequence) {
					// Set the new input stream to be a filestream, and execute the commands from there
					string fileName;
					in >> fileName;
					ifstream f;
					f.open(fileName);
					Interpret(f, board);
				}
				else if ((command == Command::I) || (command == Command::S) ||
					(command == Command::J) || (command == Command::L) ||
					(command == Command::O) || (command == Command::Z) ||
					(command == Command::T)) {
						unique_ptr<Pieces> p = make_unique<Pieces>(board->getPiece(command));
						p.swap(board->curPiece);
						board->setCurrentPiece(board->curPiece);
		  		}
			}


			if((board->getLevel() == 3 || board->getLevel() == 4 ) && (command == Command::Right || command == Command::Down || 
				command == Command::Left || command == Command::Clockwise || command == Command::CounterClockwise)) {
				// If the block is heavy, shifts the piece one unit down if possible
				board->curPiece->movePiece(Direction::Down);
			}
			if(board->isFull()) {
				cout << "GAME OVER" << endl;
				break;
			}
			// Maybe do a gameOver check here, find out where it's appropriate to do it
		}
		cout << *board;
	}
}

// Command line interface
int main(int argc, char *argv[]) {
	// Initialize the board
	auto board = make_shared<Board>();
	board->graphSwitch(true);
	int startlevel = 0;

	// Read in the command line arguments, if any
	for (int i = 1; i < argc; ++i) {
		string command = argv[i];
		if (command == "-text") {
			board->graphSwitch(false);
			// Only display the text, we don't have graphics rn but do later
			// if this is activated, don't call set observer on board, 
			// if this is not activated create a graphical display object
			// and set observer
		} else if (command == "-seed") {
			// Read in the seed
			int seed;
			istringstream iss{argv[i+1]};
			iss >> seed;
			board->seedRNG(seed);
			++i;
		} else if (command == "-scriptfile") {
			// Read in the scriptfile
			string fileName = argv[i+1];
			board->setFileName(fileName);
			++i;
		} else if (command == "-startlevel") {
			istringstream iss{argv[i+1]};
			iss >> startlevel;
			++i;
		}
	}

    board->init();
    board->setLevel(startlevel);
    cout << *board;
	// Now we can start reading user input
	Interpret(cin, board);
}

