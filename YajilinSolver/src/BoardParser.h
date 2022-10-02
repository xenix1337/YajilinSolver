#pragma once

#include <string>

#include "YajilinBoard.h"

class BoardParser {
public:
	virtual YajilinBoard Parse(std::string s) = 0;
};