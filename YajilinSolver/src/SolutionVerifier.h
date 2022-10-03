#pragma once

#include "YajilinBoard.h"
#include "SuperpositionTile.h"

enum class SolutionStatus {
	INCOMPLETE,
	COMPLETE,
	IMPOSSIBLE
};

class SolutionVerifier {
public:
	SolutionStatus VerifySolution(YajilinBoard* board, STiles& tiles);
private:
	std::pair<int32_t, int32_t> GetDeltaMove(Direction dir);

	void DFS(YajilinBoard* board, STiles& tiles, int x, int y, int32_t colorID);
	std::vector<int32_t> m_colors;
};