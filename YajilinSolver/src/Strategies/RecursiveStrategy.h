#pragma once

#include "../SolveStrategy.h"

class RecursiveStrategy : public SolveStrategy {
	/*
	Most stupid, yet most powerful strategy.
	Requires a lot of computing power, as it is mostly guessing from now on.
	Basic plan:
		1. Pick a cell with the least amount of possibilities
		2. Take a guess on duplicated STiles object
		3. Call whole Solver on the duplicate:
			a) puzzle in unsolveable -> remove guess from the original possibilities list
			b) puzzle is solved -> hurrah! copy solution to original object
			c) puzzle is still unsolved -> call ResursiveStrategy again, up to a limit
			d) limit is reached and puzzle is still unsolved -> take another guess at the top level
	*/
public:
	RecursiveStrategy(int32_t recursionDepth);
	bool SolveStep(YajilinBoard* board, STiles& tiles);
private:
	int32_t FindLeastEntropyTile(STiles& tiles);

	int32_t m_recursionDepth;
};