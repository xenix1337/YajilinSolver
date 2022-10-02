#pragma once

#include <vector>
#include <cstdint>
#include <map>

#include "Tile.h"
#include "Clue.h"

class YajilinBoard
{
public:
	YajilinBoard(int w, int h);

	Tile GetTile(int x, int y);
	Tile GetTile(int i);
	void SetTile(int x, int y, Tile t);
	void SetTile(int i, Tile t);

	std::map<int, Clue>& GetClues() { return m_clues; }
	Clue GetClue(int x, int y);
	Clue GetClue(int i);
	void AddClue(int x, int y, Clue c);
	void AddClue(int i, Clue c);

	int32_t GetWidth() { return m_width; }
	int32_t GetHeight() { return m_height; }
private:
	int32_t m_width;
	int32_t m_height;
	std::vector<Tile> m_tiles;
	std::map<int, Clue> m_clues;
};

