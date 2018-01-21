#include "interpreter.h"

using namespace std;

Interpreter::Interpreter() {
    // Initialize the map with all the available commands
    commands["left"] = Command::Left;
    commands["right"] = Command::Right;
    commands["down"] = Command::Down;
    commands["clockwise"] = Command::Clockwise;
    commands["counterclockwise"] = Command::CounterClockwise;
    commands["drop"] = Command::Drop;
    commands["levelup"] = Command::LevelUp;
    commands["leveldown"] = Command::LevelDown;
    commands["norandom"] = Command::NoRandom;
    commands["random"] = Command::Random;
    commands["sequence"] = Command::Sequence;
    commands["restart"] = Command::Restart;
    commands["hint"] = Command::Hint;
    // All of the block commands
    commands["I"] = Command::I;
    commands["J"] = Command::J;
    commands["L"] = Command::L;
    commands["O"] = Command::O;
    commands["S"] = Command::S;
    commands["Z"] = Command::Z;
    commands["T"] = Command::T;
    // Find out the behaviour when the command
    // isn't even in the map 
}

// isPrefix will determine if string1 is a prefix of string2
bool isPrefix(string s1, string s2) {
    if (s1.length() > s2.length()) return false;
    int s1Length = s1.length();
    for (int i = 0; i < s1Length; ++i) {
        if (s1[i] != s2[i]) return false;
    }
    return true;
}

pair<int, Command> Interpreter::getCommand(string command) {
    // Initialize the pair to be returned
    int numTimes = 0;
    Command c = Command::Invalid;
    // See how many times we should run the command
    int startIndex = 0;
    while (isdigit(command[startIndex])) {
        // Update our numTimes parameter
        numTimes *= 10;
        numTimes += command[startIndex] - '0';
        startIndex++;
    }
    // Set numTimes to be 1 in case there wasn't a multiplier
    if (numTimes == 0) numTimes = 1;
    // See if the indexes make sense here
    // Update our command string
    string comString = command.substr(startIndex, command.length() - startIndex);
    // Check to see if the command is valid or not
    for (auto const& com: commands) {
        // See if the command is a prefix of the key
        string key = com.first;
        if (isPrefix(comString, key)) {
            // Now, see if the command has already been set, in which case
            // we know that there are >1 matching values. Thus it is invalid
            if (c != Command::Invalid) {
                return make_pair(numTimes, Command::Invalid);
            } else {
                c = com.second;
            }
        }
    }
    // Return the pair
    return make_pair(numTimes, c);
}

