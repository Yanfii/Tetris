#ifndef STATE_H
#define STATE_H

/* State types are:
    Difficulty -- I am a new piece.  I was just placed on the board.  I'm letting
                you know that I exist, in case you need to change colour.

    Block -- I have a neighbour (or a neighbour's neighbour, etc.) who is a 
             new piece, not of my colour, and is a straight line away from me.
             I'm letting you know that that neighbour exists, and in which
             direction it is, in case you need to change colour.
*/
enum class Block { None, IBlock, JBlock, LBlock, OBlock, SBlock, ZBlock, TBlock, starBlock, hintBlock};

enum class Direction {Left, Right, Down, Drop, Clockwise, CounterClockwise};

enum class Command {
  Left, Right, Down, Clockwise, CounterClockwise, Drop,
  LevelUp, LevelDown, NoRandom, Random, Sequence,
  Restart, Hint, Invalid,
  // Blocks
  I, J, L, O, S, Z, T
};
enum class Difficulty {Level0, Level1, Level2, Level3, Level4};
struct State {
  Block block;   
  bool isActive = true;
  bool isDropped = false;
  Difficulty level;
  int id;
};

#endif
