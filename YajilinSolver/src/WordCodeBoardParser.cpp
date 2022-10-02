#include "WordCodeBoardParser.h"

#include <sstream>
#include <cstdint>

YajilinBoard WordCodeBoardParser::Parse(std::string s)
{
	std::stringstream ss(s);
	int32_t width, height;

	ss >> width >> height;
	YajilinBoard returnBoard(width, height);

	// TODO: Check if length is OK
	// TODO: Validate inputs
	for (int i = 0; i < width * height; i++) {
		std::string word;
		ss >> word;

		char lastLetter = word[word.length() - 1];
		if (lastLetter == 'X') {
			returnBoard.SetTile(i, Tile::BLOCKADE_GIVEN);
			continue;
		}
		
		Direction dir = ParseDirection(lastLetter);
		if (dir != Direction::UNDEFINED) {
			int val = atoi(word.substr(0, word.length() - 1).c_str());
			returnBoard.AddClue(i, Clue(dir, val));
			returnBoard.SetTile(i, Tile::BLOCKADE_GIVEN);
			continue;
		}

		if (word == "0") {
			returnBoard.SetTile(i, EMPTY);
			continue;
		}

		throw std::runtime_error("Input word is invalid!");
	}
	return returnBoard;
}

Direction WordCodeBoardParser::ParseDirection(char c)
{
	switch (c) {
	case 'U':
	case 'u':
		return Direction::UP;
	case 'R':
	case 'r':
		return Direction::RIGHT;
	case 'D':
	case 'd':
		return Direction::DOWN;
	case 'L':
	case 'l':
		return Direction::LEFT;
	default:
		return Direction::UNDEFINED;
	}
}
