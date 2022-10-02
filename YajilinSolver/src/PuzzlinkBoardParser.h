#pragma once

#include <stack>

#include "BoardParser.h"

// This parser works with puzz.link (or pzv.jp) link
// 
// Example code:
// https://puzz.link/p?yajilin/10/10/e32m23f22p32k42h22e12o31m
// The details of this implementation are hard to explain. This class is basically original JS code rewritten in C++


class PuzzlinkBoardParser : public BoardParser {
public:
	YajilinBoard Parse(std::string s);
private:
	std::stack<std::string> SplitString(std::string& s, char delimiter);
	int32_t ParseHex(std::string s);
	int32_t ParseHex(char c);
};