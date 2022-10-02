#pragma once

#include <string>

#include "BoardOutput.h"

class AsciiBoardOutput : public BoardOutput {
public:
	std::string Format(YajilinBoard board);
	
private:
	std::string VerticalLine(int n);
};