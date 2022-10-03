#include "RecursiveStrategy.h"

#include "../YajilinSolver.h"
#include "../SolutionVerifier.h"

#include <iostream>

RecursiveStrategy::RecursiveStrategy(int32_t recursionDepth)
{
    m_recursionDepth = recursionDepth;
}

bool RecursiveStrategy::SolveStep(YajilinBoard* board, STiles& tiles)
{
    bool stepSucceed = false;

    int32_t leastEntropyTile = FindLeastEntropyTile(tiles); //TODO: Sort by entropy
    if (leastEntropyTile == -1) return false;

    YajilinSolver solver(m_recursionDepth - 1);
    auto& st = tiles[leastEntropyTile];
    for (Tile t : st.possibles) {
        STiles tilesCopy = tiles;
        tilesCopy[leastEntropyTile].Set(t);

        STiles result = solver.Solve(board, tilesCopy);
        // A guess could lead to seemingly working solution, but incorrect. We have to ensure that
        // we discard any illegal solution.

        SolutionVerifier verifier;
        SolutionStatus status = verifier.VerifySolution(board, result);

        if (status == SolutionStatus::IMPOSSIBLE) {
            stepSucceed |= tiles[leastEntropyTile].RemovePossible(t);
        }
        else if (status == SolutionStatus::COMPLETE) {
            stepSucceed = true;
            tiles = result;
        }

        if (stepSucceed) return true; // Return from this strategy as soon as possible, as it is slow.
    }

    return stepSucceed;
}

int32_t RecursiveStrategy::FindLeastEntropyTile(STiles& tiles)
{
    size_t min = 99;
    int32_t minIndex = -1;
    for (int i = 0; i < tiles.size(); i++) {
        if (tiles[i].solved) continue;
        if (tiles[i].possibles.size() == 1) continue;

        if (tiles[i].possibles.size() < min) {
            min = tiles[i].possibles.size();
            minIndex = i;
        }
        if (min == 2) break;
    }
    return minIndex;
}
