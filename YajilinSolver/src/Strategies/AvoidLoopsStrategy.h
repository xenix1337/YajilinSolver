#pragma once

#include <vector>

#include "../SolveStrategy.h"

class AvoidLoopsStrategy : public SolveStrategy {
	/*
	How does this avoiding work?
	First, we color each individual line segment.
	Then, we don't allow two line segments with the same color (already connected somehow) to connect again.
	It creates a problem - because the goal of this puzzle is to eventually make a big loop.

	Currently it is not a problem - that's because of strategies order. There is no known case, where other strategies
	fail and this strategy discard the correct solution. Why? That's because the only time this strategy will
	discard the correct solution is at the very end, where one huge line segment connects with itself to make a final loop.
	In this case, the move is really obvious for ReduceByNeighboursStrategy.

	However, I keep this problem in mind, as it may become serious later.
	*/
public:
	bool SolveStep(YajilinBoard* board, STiles& tiles);
private:
	void Colorize(YajilinBoard* board, STiles& tiles);
	void DFS(YajilinBoard* board, STiles& tiles, int x, int y, int32_t colorID);

	std::vector<int32_t> m_colors;
};