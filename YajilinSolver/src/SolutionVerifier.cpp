#include "SolutionVerifier.h"

#include <stdexcept>

SolutionStatus SolutionVerifier::VerifySolution(YajilinBoard* board, STiles& tiles)
{
	int w = board->GetWidth();
	int h = board->GetHeight();

	// TODO: Do much more checking for impossible solution, where we could report that state earlier
	// There is nothing bad about returning IMPOSSIBLE status after filling up the whole grid, just
	// the recursion will go deeper and take more time.

	// 1. Check for cells with no solution
	for (int i = 0; i < tiles.size(); i++)
		if (tiles[i].possibles.size() <= 0) return SolutionStatus::IMPOSSIBLE;

	// 2. Check for overflown arrows
    // Note: This is redundant code from ResolveArrowsStrategy. No idea how to reuse code smartly now.
	auto& clues = board->GetClues();
	for (auto& clue : clues) {
        auto delta = GetDeltaMove(clue.second.direction);
        int deltaX = delta.first, deltaY = delta.second;

		int x = (clue.first % w) + deltaX;
		int y = (clue.first / w) + deltaY;
        int placedBlockades = 0;

        while (x >= 0 && y >= 0 && x < w && y < h) {
            int i = x + y * w;
            if (tiles[i].solved && tiles[i].GetTile() == BLOCKADE)
                placedBlockades++;

            x += deltaX; y += deltaY;
        }
        if (placedBlockades > clue.second.value) return SolutionStatus::IMPOSSIBLE;
	}

	// 3. Check for two or more loops
    // Note: This is redundant code from AvoidLoopsStrategy. No idea how to reuse code smartly now.
    // TODO: Avoid loops

    for (int i = 0; i < tiles.size(); i++)
        if (!tiles[i].solved) return SolutionStatus::INCOMPLETE;

	return SolutionStatus::COMPLETE;
}

// TODO: This is redundant code from ResolveArrowsStrategy. No idea how to reuse code smartly here
std::pair<int32_t, int32_t> SolutionVerifier::GetDeltaMove(Direction dir)
{
    int deltaX = 0, deltaY = 0;
    switch (dir)
    {
    case Direction::UP:
        deltaY = -1;
        break;
    case Direction::DOWN:
        deltaY = 1;
        break;
    case Direction::LEFT:
        deltaX = -1;
        break;
    case Direction::RIGHT:
        deltaX = 1;
        break;
    default:
        throw std::runtime_error("Unexpected direction");
        break;
    }
    return { deltaX, deltaY };
}
