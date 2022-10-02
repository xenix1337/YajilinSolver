#include "AvoidLoopsStrategy.h"

#include <stack>
#include <iostream>

bool AvoidLoopsStrategy::SolveStep(YajilinBoard* board, STiles& tiles)
{
	// 1. Color
	Colorize(board, tiles);

	int w = board->GetWidth();
	int h = board->GetHeight();

	bool stepSuccessful = false;

	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			if (tiles[x + y * w].solved) continue;

			// Remove all possibilities, that connect the same color
			for (int dir1 = 0; dir1 < 4; dir1++) {
				for (int dir2 = dir1 + 1; dir2 < 4; dir2++) {
					// For each possible tile, described as pair of directions, check
					int32_t nx = x + directions[dir1].first.first;
					int32_t ny = y + directions[dir1].first.second;
					if (nx < 0 || nx >= w || ny < 0 || ny >= h) {
						continue;
					}
					if (m_colors[nx + ny * w] == -1) continue;

					int32_t mx = x + directions[dir2].first.first;
					int32_t my = y + directions[dir2].first.second;
					if (mx < 0 || mx >= w || my < 0 || my >= h) {
						continue;
					}

					if (m_colors[nx + ny * w] != m_colors[mx + my * w]) continue;

					Tile tileToRemove = (Tile) (directions[dir1].second | directions[dir2].second);
					stepSuccessful |= tiles[x + y * w].RemovePossible(tileToRemove);
				}
			}

		}
	}
    return false;
}

void AvoidLoopsStrategy::Colorize(YajilinBoard* board, STiles& tiles)
{
	int32_t lastColorID = 0;
	int w = board->GetWidth();
	int h = board->GetHeight();

	m_colors.clear();
	m_colors.resize(tiles.size(), -1);
	
	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			int i = x + y * w;
			if (!tiles[i].solved) continue; // We can't put color on unsolved cells
			if (m_colors[i] != -1) continue; // We can't put a new color on already colored cells
			Tile t = tiles[i].GetTile();
			if (t == BLOCKADE || t == BLOCKADE_GIVEN) continue; // We can't put color on blockades

			DFS(board, tiles, x, y, lastColorID++);
		}
	}
}

void AvoidLoopsStrategy::DFS(YajilinBoard* board, STiles& tiles, int x, int y, int32_t colorID)
{
	int w = board->GetWidth();
	int h = board->GetHeight();

	std::stack<std::pair<int, int>> s;
	s.push({ x, y });
	m_colors[x + y * w] = colorID;

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
			if (tiles[ni].solved && m_colors[ni] != colorID) s.push({nx, ny});
			m_colors[ni] = colorID;
		}
	}
}
