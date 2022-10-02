#pragma once

#include <vector>
#include <algorithm>

#include "Tile.h"

enum BoardStatus {
	UNSOLVED,
	SOLVED,
	IMPOSSIBLE
};

struct SuperpositionTile;
typedef std::vector<SuperpositionTile> STiles;

struct SuperpositionTile {
	bool solved;
	std::vector<Tile> possibles;

	SuperpositionTile() {
		SetDefault();
	}

	Tile GetTile() {
		return possibles[0];
	}

	void SetDefault() {
		possibles.clear();
		possibles.push_back(Tile::BLOCKADE);
		possibles.push_back(Tile::UP_LEFT);
		possibles.push_back(Tile::UP_RIGHT);
		possibles.push_back(Tile::UP_DOWN);
		possibles.push_back(Tile::DOWN_LEFT);
		possibles.push_back(Tile::DOWN_RIGHT);
		possibles.push_back(Tile::LEFT_RIGHT);
		solved = false;
	}

	void SetAsGiven() {
		solved = true;
		possibles.clear();
		possibles.push_back(Tile::BLOCKADE_GIVEN);
	}

	bool RemovePossible(Tile t) {
		size_t s = possibles.size();
		possibles.erase(std::remove(possibles.begin(), possibles.end(), t), possibles.end());
		CheckForSolved();
		return (s != possibles.size());
	}

	bool RemovePossibleDirection(int32_t directionMask) {
		size_t s = possibles.size();
		possibles.erase(
			std::remove_if(possibles.begin(), possibles.end(), 
				[directionMask](Tile& t) { return (t & directionMask); }
		), possibles.end());
		CheckForSolved();
		return (s != possibles.size());
	}

	bool KeepOnlyPossibleDirection(int32_t directionMask) {
		size_t s = possibles.size();
		possibles.erase(
			std::remove_if(possibles.begin(), possibles.end(),
				[directionMask](Tile& t) { return !(t & directionMask); }
		), possibles.end());
		CheckForSolved();
		return (s != possibles.size());
	}

	void CheckForSolved() {
		if (possibles.size() == 1) solved = true;
	}

	bool CanBe(Tile t) {
		return std::find(possibles.begin(), possibles.end(), t) != possibles.end();
	}

	bool Set(Tile t) {
		if (possibles.size() == 1 && possibles[0] == t) return false;
		possibles.clear();
		possibles.push_back(t);
		solved = true;
		return true;
	}

	static BoardStatus GetBoardStatus(STiles& tiles) {
		bool allPossible = true;
		bool allSolved = true;
		for (int i = 0; i < tiles.size(); i++) {
			if (!tiles[i].solved) allSolved = false;
			if (tiles[i].possibles.size() == 0) allPossible = false;
		}
		if (!allPossible) return BoardStatus::IMPOSSIBLE;
		if (!allSolved) return BoardStatus::UNSOLVED;
		return BoardStatus::SOLVED;
	}
};