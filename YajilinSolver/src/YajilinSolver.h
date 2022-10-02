#pragma once

#include "YajilinBoard.h"
#include "SuperpositionTile.h"
#include "SolveStrategy.h"

typedef std::vector<SuperpositionTile> STiles;

class YajilinSolver {
public:
	YajilinSolver(int32_t allowedRecurenceDepth = 5);
	void Solve(YajilinBoard* board);
	STiles Solve(YajilinBoard* board, STiles& tiles);

private:
	STiles Solve(STiles tiles);

	int32_t m_allowedRecursionDepth = 0;
	YajilinBoard* m_currentBoard = nullptr;

	std::vector<SolveStrategy*> m_strategies;

};