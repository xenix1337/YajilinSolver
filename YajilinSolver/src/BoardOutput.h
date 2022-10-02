#pragma once

#include <string>

#include "YajilinBoard.h"

class BoardOutput {
public:
	virtual std::string Format(YajilinBoard board) = 0;
};