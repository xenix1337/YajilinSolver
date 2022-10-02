#pragma once

#include <cstdint>

enum Direction {
	UP = 0x1,
	RIGHT = 0x2,
	DOWN = 0x4,
	LEFT = 0x8,
	UNDEFINED = 0
};

struct Clue {
	Direction direction;
	int32_t value;

	Clue(Direction dir, int32_t val) {
		direction = dir;
		value = val;
	}

	Clue() { direction = UNDEFINED; value = 0; }
};