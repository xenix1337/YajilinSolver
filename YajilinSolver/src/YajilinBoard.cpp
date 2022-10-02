#include "YajilinBoard.h"
#include <stdexcept>

YajilinBoard::YajilinBoard(int w, int h)
{
	m_width = w;
	m_height = h;
	m_tiles.resize(w * h);
}

Tile YajilinBoard::GetTile(int x, int y)
{
#ifdef _DEBUG
	if (x < 0 || y < 0 || x >= m_width || y >= m_height) {
		throw std::runtime_error("GetTile(x, y): Tile coordinates are out of bounds");
		return Tile::INVALID;
	}
#endif
	return GetTile(x + y * m_width);
}

Tile YajilinBoard::GetTile(int i)
{
#ifdef _DEBUG
	if (i < 0 || i >= m_tiles.size()) {
		throw std::runtime_error("GetTile(i): Tile coordinates are out of bounds");
	}
#endif
	return m_tiles[i];
}

void YajilinBoard::SetTile(int x, int y, Tile t)
{
#ifdef _DEBUG
	if (x < 0 || y < 0 || x >= m_width || y >= m_height) {
		throw std::runtime_error("SetTile(x, y, t): Tile coordinates are out of bounds");
	}
#endif
	SetTile(x + y * m_width, t);
}

void YajilinBoard::SetTile(int i, Tile t)
{
#ifdef _DEBUG
	if (i < 0 || i >= m_tiles.size()) {
		throw std::runtime_error("SetTile(i, t): Tile coordinates are out of bounds");
	}
#endif
	m_tiles[i] = t;
}

Clue YajilinBoard::GetClue(int x, int y)
{
#ifdef _DEBUG
	if (x < 0 || y < 0 || x >= m_width || y >= m_height) {
		throw std::runtime_error("GetClue(x, y): Tile coordinates are out of bounds");
	}
#endif

	return GetClue(x + y * m_width);
}

Clue YajilinBoard::GetClue(int i)
{
#ifdef _DEBUG
	if (i < 0 || i >= m_tiles.size()) {
		throw std::runtime_error("GetClue(i): Tile coordinates are out of bounds");
	}
#endif

	//TODO: Handle exception where m_clues[i] doesn't exist.
	return m_clues[i];
}

void YajilinBoard::AddClue(int x, int y, Clue c)
{
#ifdef _DEBUG
	if (x < 0 || y < 0 || x >= m_width || y >= m_height) {
		throw std::runtime_error("AddClue(x, y, c): Tile coordinates are out of bounds");
	}
#endif
	AddClue(x + y * m_width, c);
}

void YajilinBoard::AddClue(int i, Clue c)
{
#ifdef _DEBUG
	if (i < 0 || i >= m_tiles.size()) {
		throw std::runtime_error("AddClue(i, t): Tile coordinates are out of bounds");
	}
#endif
	m_clues[i] = c;
	m_tiles[i] = BLOCKADE_GIVEN;
}
