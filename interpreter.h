#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <map>
#include <string>
#include <utility>
#include "board.h"
#include "pieces.h"
#include "state.h"

class Interpreter {
    // We want to keep a Dictionary of our commands
    std::map<std::string, Command> commands;
    public:
        Interpreter();
        std::pair<int, Command> getCommand(std::string command);
};

#endif
