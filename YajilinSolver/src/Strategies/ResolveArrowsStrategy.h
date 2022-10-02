#pragma once

#include "../SolveStrategy.h"

class ResolveArrowsStrategy : public SolveStrategy {
	/*
	How does this resolving work?
	First, let's imagine a clue and every cell that it sees:
	[2>] [?] [?] [ ] [X] [ ], where:
		[ ] is any cell that will never be a blockade,
		[?] is a cell that could be still a blockade, and
		[X] is a solved blockade

	Let's group cells and count every disjoint group of [?] and [X] ([?] will never be next to [X]):
	{2, 1} - we have two [?] cells, then one [X] cell.

	Now, for each count, divide that number by two and round up. This gives a total number of blockades
	that can fit in this group. Then, sum it up.
	{2, 1} -> {1, 1} -> Sum of 2
	Another example: {5, 4, 3, 2, 1} -> {3, 2, 2, 1, 1} -> Sum of 9, etc.

	To check if any resolving is possible, check this sum with the clue value:
	[2>] == 2; if numbers are equal, then proceed to the next step. Otherwise leave that clue for later.

	For every odd sized group there is only one possible arrangement of blockades (maxing out the blockade count):
	{3} -> [ ] [ ] [ ] -> [X] [ ] [X]

	Unfortunately, we must leave even sized groups with no changes, as:
	{4} -> [ ] [ ] [ ] [ ] can either be:
		[X] [ ] [X] [ ], or
		[ ] [X] [ ] [X]

	This method should be quite fast, but it works only for any obvious clue arrangement. 
	The only edge-case is a clue with value = 0, 
	in this case we skip everything above and just remove blockade from possibles of any cell that it sees.

	TODO: Mark clues as completely resolved, to avoid further calculations with it, as this strategy is early on and will do
	a lot of recalculations over and over again.
	*/
public:
	bool SolveStep(YajilinBoard* board, STiles& tiles);

private:
	std::pair<int32_t, int32_t> GetDeltaMove(Direction dir);
};