#include "ReduceByNeighboursStrategy.h"

#include <array>
#include <iostream>

bool ReduceByNeighboursStrategy::SolveStep(YajilinBoard* board, STiles& tiles)
{
	int w = board->GetWidth();
	int h = board->GetHeight();

	bool stepSuccessful = false;

	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			if (tiles[x + y * w].solved) continue;

			// For each direction, restrict this cell based on its neighbours
			for (int dir = 0; dir < 4; dir++) {
				int32_t nx = x + directions[dir].first.first;
				int32_t ny = y + directions[dir].first.second;

				bool isNeighbourConnectedToThisCell = false;
				bool isNeighbourABlockade = false;

				// We need to determine two things:
				// 1. Can current cell connect to this neighbour (does neighbour 100% connects to this cell)?
				// 2. Can this cell be a blockade (is this neighbour NOT a blockade)?
				if (nx < 0 || nx >= w || ny < 0 || ny >= h) {
					isNeighbourConnectedToThisCell = false;
				}
				else {
					auto& stNeighbour = tiles[nx + ny * w];
					if (!stNeighbour.solved) continue; // TODO: Check also unsolved cells, which definitely limits neighbour

					if (stNeighbour.possibles.size() == 0) continue;
					Tile t = stNeighbour.GetTile();
					if (t == BLOCKADE) {
						isNeighbourABlockade = true;
					}
					else if (t != BLOCKADE_GIVEN) {
						int32_t oppositeDirectionMask = directions[(dir + 2) % 4].second;
						isNeighbourConnectedToThisCell = t & oppositeDirectionMask;
					}
				}

				SuperpositionTile& st = tiles[x + y * w];
				if (isNeighbourABlockade) {
					stepSuccessful |= st.RemovePossible(Tile::BLOCKADE);
				}
				if (isNeighbourConnectedToThisCell) {
					// Delete unconnected possibles
					stepSuccessful |= st.KeepOnlyPossibleDirection(directions[dir].second);
				}
				else {
					// Delete connected possibles
					stepSuccessful |= st.RemovePossibleDirection(directions[dir].second);
				}
			}
		}
	}
	return stepSuccessful;
}
