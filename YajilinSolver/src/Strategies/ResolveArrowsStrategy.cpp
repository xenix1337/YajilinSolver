#include "ResolveArrowsStrategy.h"

#include <stdexcept>
#include <iostream>

bool ResolveArrowsStrategy::SolveStep(YajilinBoard* board, STiles& tiles)
{
    bool stepSucceed = false;
    auto& clues = board->GetClues();
    for (auto& cluePair : clues) {
        int cluePosition = cluePair.first;
        Clue& clue = cluePair.second;

        if (clue.direction == Direction::UNDEFINED) continue; // Those are really empty tiles, not clues

        int w = board->GetWidth();
        int h = board->GetHeight();

        // Assign delta of cluePosition to step one cell in the direction of the arrow
        auto delta = GetDeltaMove(clue.direction);
        int deltaX = delta.first, deltaY = delta.second;

        int x = (cluePosition % w) + deltaX;
        int y = (cluePosition / w) + deltaY;

        // Trivial case, just remove blockade as possibility from all cells that it sees
        if (clue.value == 0) {
            while (x >= 0 && y >= 0 && x < w && y < h) {
                // (x, y) cell is affected by this clue
                int i = x + y * w;
                SuperpositionTile& st = tiles[i];
                stepSucceed |= st.RemovePossible(Tile::BLOCKADE);

                x += deltaX;
                y += deltaY;
            }
        }
        else {
            // (More info about this algorithm in ResolveArrowsStrategy.h)

            // First loop, find group sizes
            std::vector<int32_t> groups(1);
            std::vector<int32_t> possibleBlockadePlacement;
            while (x >= 0 && y >= 0 && x < w && y < h) {
                // (x, y) cell is affected by this clue
                int i = x + y * w;
                SuperpositionTile& st = tiles[i];

                bool canBeOrIsBlockade = st.CanBe(Tile::BLOCKADE);

                if (canBeOrIsBlockade) {
                    groups[groups.size() - 1]++;
                    possibleBlockadePlacement.push_back(i);
                }
                else groups.push_back(0);

                x += deltaX;
                y += deltaY;
            }
            // Remove last group, if empty
            if (groups[groups.size() - 1] == 0) groups.resize(groups.size() - 1);

            int32_t totalBlockadesThatFit = 0;
            for (int32_t groupSize : groups) {
                int32_t maxBlockadesThatFit = (groupSize + 1) / 2;
                totalBlockadesThatFit += maxBlockadesThatFit;
            }

            if (totalBlockadesThatFit != clue.value) continue;

            // Current state allows to determine positions of blockades in odd-sized groups
            int32_t i = 0; // Holds index of the next element in possibleBlockadePlacement
            for (int32_t groupSize : groups) {
                int32_t maxBlockadesThatFit = (groupSize + 1) / 2;
                if (groupSize % 2 == 0) {
                    // Pass on even group
                    i += groupSize;

                    // TODO: Cells adjacent to this group can almost never be a blockade. Test that
                }
                else {
                    // Set blockades in odd group
                    for (int j = 0; j < maxBlockadesThatFit; j++) {
                        stepSucceed |= tiles[possibleBlockadePlacement[i]].Set(BLOCKADE);
                        i += 2;
                    }
                    i--; // Previous loop overshoot i, decrement
                }
            }
        }
    }
    return stepSucceed;
}

std::pair<int32_t, int32_t> ResolveArrowsStrategy::GetDeltaMove(Direction dir)
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
