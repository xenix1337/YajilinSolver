#include "SolutionVerifier.h"

#include <stdexcept>
#include <stack>
#include <array>

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

	// 2. Check for overflown and underflown arrows
    // Note: This is redundant code from ResolveArrowsStrategy. No idea how to reuse code smartly now.
	auto& clues = board->GetClues();
	for (auto& clue : clues) {
		if (clue.second.direction == Direction::UNDEFINED) continue;

        auto delta = GetDeltaMove(clue.second.direction);
        int deltaX = delta.first, deltaY = delta.second;

		int x = (clue.first % w) + deltaX;
		int y = (clue.first / w) + deltaY;

        int placedBlockades = 0;
		bool wereAllSolvedAlongTheClue = true;

        while (x >= 0 && y >= 0 && x < w && y < h) {
            int i = x + y * w;
            if (tiles[i].solved && tiles[i].GetTile() == BLOCKADE)
                placedBlockades++;

			if (!tiles[i].solved) wereAllSolvedAlongTheClue = false;

            x += deltaX; y += deltaY;
        }
        if (placedBlockades > clue.second.value) return SolutionStatus::IMPOSSIBLE;
		if (wereAllSolvedAlongTheClue && placedBlockades != clue.second.value) return SolutionStatus::IMPOSSIBLE;
	}

	// Before we check the number of colors (disjoint loop fragments) we will
	// check if the solution can be even considered finished, as while solving
	// we will often have more than one color, eventually going to join
	// and that's not impossible case
	for (int i = 0; i < tiles.size(); i++)
		if (!tiles[i].solved) return SolutionStatus::INCOMPLETE;

	// 3. Check for two or more loops
    // Note: This is redundant code from AvoidLoopsStrategy. No idea how to reuse code smartly now.
    // TODO: Avoid loops
	int colorCount = 0;
	m_colors.resize(w * h, -1);
	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			if ((tiles[x + y * w].GetTile() & 0b1111) > 0 && m_colors[x + y * w] == -1) {
				DFS(board, tiles, x, y, colorCount++);
				if (colorCount == 2) {
					break;
				}
			}
		}
	}
	if (colorCount > 1) return SolutionStatus::IMPOSSIBLE;

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

void SolutionVerifier::DFS(YajilinBoard* board, STiles& tiles, int x, int y, int32_t colorID)
{
	int w = board->GetWidth();
	int h = board->GetHeight();

	std::stack<std::pair<int, int>> s;
	s.push({ x, y });
	m_colors[x + y * w] = colorID;

	const std::array<std::pair<std::pair<int32_t, int32_t>, int32_t>, 4> directions = { {
		{{ 0,-1},0x1},
		{{ 1, 0},0x2},
		{{ 0, 1},0x4},
		{{-1, 0},0x8}
	} };

	while (!s.empty()) {
		auto current = s.top();
		s.pop();
		x = current.first; //TODO: Probably shouldn't reuse function parameters here
		y = current.second;

		for (int dir = 0; dir < 4; dir++) {
			if (!(tiles[x + y * w].GetTile() & directions[dir].second)) continue; // Look only in directions of this tile

			int32_t nx = x + directions[dir].first.first;
			int32_t ny = y + directions[dir].first.second;

			int ni = nx + ny * w;
			if (tiles[ni].solved && m_colors[ni] != colorID) s.push({ nx, ny });
			m_colors[ni] = colorID;
		}
	}
}
