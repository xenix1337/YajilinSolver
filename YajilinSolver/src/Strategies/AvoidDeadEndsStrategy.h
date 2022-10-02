#pragma once

#include "../SolveStrategy.h"

class AvoidDeadEndsStrategy : public SolveStrategy {
	/*
	How does this avoiding work?
	This is almost the same as the last strategy used - recursion.
	For each cell, we will virtually set it as blockade and analyse neighbour cells.
	Often it will leave no choice for at least one of them, then we know that this cell can't be a blockade.

	Why don't just leave that to recursion?
	Because this is MUCH faster, and gives some results at least once per puzzle.
	Also, removing a blockade from possibilities can give snowball effect with some other strategies (resolving arrows, mostly)
	*/
public:
	bool SolveStep(YajilinBoard* board, STiles& tiles);

};