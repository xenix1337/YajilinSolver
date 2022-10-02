#pragma once

#include <vector>
#include <array>

#include "SuperpositionTile.h"
#include "YajilinBoard.h"

class SolveStrategy {
public:
	virtual bool SolveStep(YajilinBoard* board, STiles& tiles) = 0;
protected:
	const std::array<std::pair<std::pair<int32_t, int32_t>, int32_t>, 4> directions = { {
		{{ 0,-1},0x1},
		{{ 1, 0},0x2},
		{{ 0, 1},0x4},
		{{-1, 0},0x8}
	} };
};