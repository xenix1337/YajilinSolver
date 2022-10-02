#include "AvoidDeadEndsStrategy.h"

#include <iostream>

bool AvoidDeadEndsStrategy::SolveStep(YajilinBoard* board, STiles& tiles)
{
    int w = board->GetWidth();
    int h = board->GetHeight();

    bool stepSucceed = false;

    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            auto& tile = tiles[x + y * w];
            if (!tile.CanBe(Tile::BLOCKADE)) continue;
            if (tile.solved) continue;

            // Virtually set this as a blockade, but we don't really want to change anything in memory
            // tile.Set(BLOCKADE);
            bool canThisBeBlockade = true;
            for (int dir = 0; dir < 4; dir++) {
                int32_t nx = x + directions[dir].first.first;
                int32_t ny = y + directions[dir].first.second;

                if (nx < 0 || nx >= w || ny < 0 || ny >= h) {
                    continue;
                }

                if (tiles[nx + ny * w].solved) continue; // Solved neighbours won't limit this cell as a blockade more than strategy one

                auto stNeighbour = tiles[nx + ny * w]; // Note that we create a copy, not reference
                // This is because we don't want to mess up this tile in case we 'backtrack'

                stNeighbour.RemovePossible(Tile::BLOCKADE);
                int32_t oppositeDirectionMask = directions[(dir + 2) % 4].second;
                stNeighbour.RemovePossibleDirection(oppositeDirectionMask);

                bool canNeighbourExist = stNeighbour.possibles.size() > 0;
                if (!canNeighbourExist) {
                    canThisBeBlockade = false;
                    break;
                }
            }

            if (!canThisBeBlockade) {
                stepSucceed = true;
                tile.RemovePossible(Tile::BLOCKADE);
            }
        }
    }
    return stepSucceed;
}
