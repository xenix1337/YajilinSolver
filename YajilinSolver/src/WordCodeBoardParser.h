#pragma once

#include "BoardParser.h"

// Example code:
// 5 5 0 0 0 0 0 0 0 0R 0 0 0 0 0 2L 0 0R 0 0 0 0 0 0 0 0 0
// Two first numbers are size of the board
// Next w * h words are cell descriptions. 
// - (int)[U/L/D/R] is arrow in (U)p, (L)eft, (D)own, or (R)ight
// - X is given blockade, but with no arrow
// - 0 is empty cell

class WordCodeBoardParser : public BoardParser {
public:
	YajilinBoard Parse(std::string s);
private:
	Direction ParseDirection(char c);
};