#include "YajilinSolver.h"

#include <iostream>

#include "Strategies/ReduceByNeighboursStrategy.h"
#include "Strategies/ResolveArrowsStrategy.h"
#include "Strategies/AvoidDeadEndsStrategy.h"
#include "Strategies/AvoidLoopsStrategy.h"
#include "Strategies/RecursiveStrategy.h"

#include "AsciiBoardOutput.h"
#include "SolutionVerifier.h"

YajilinSolver::YajilinSolver(int32_t allowedRecurenceDepth)
{
    m_allowedRecursionDepth = allowedRecurenceDepth;

    m_strategies.push_back(new ReduceByNeighboursStrategy());
    m_strategies.push_back(new ResolveArrowsStrategy());
    m_strategies.push_back(new AvoidDeadEndsStrategy());
    m_strategies.push_back(new AvoidLoopsStrategy());
}

void YajilinSolver::Solve(YajilinBoard* board)
{
    m_currentBoard = board;

    // Prepare superposition tiles
    int w = board->GetWidth();
    int h = board->GetHeight();
    STiles tiles(w * h);

    for(int i = 0; i < w * h; i++)
        if (board->GetTile(i) == Tile::BLOCKADE_GIVEN)
            tiles[i].SetAsGiven();

    // Solve
    tiles = Solve(tiles);

    // Copy solved cells to board
    for (int i = 0; i < w * h; i++) {
        if (tiles[i].solved) {
            if (tiles[i].possibles.size() > 0)
                board->SetTile(i, tiles[i].GetTile());
        }
    }
}

STiles YajilinSolver::Solve(YajilinBoard* board, STiles& tiles)
{
    m_currentBoard = board;
    return Solve(tiles);
}

STiles YajilinSolver::Solve(STiles tiles)
{
    int stepCounter = 0;
    bool didStepSucceed;
    do {
        didStepSucceed = false;

        SolutionVerifier verifier;
        SolutionStatus status = verifier.VerifySolution(m_currentBoard, tiles);
        if (status == SolutionStatus::IMPOSSIBLE) return tiles;

        for (auto strategy : m_strategies) {
            bool stratSucceed = strategy->SolveStep(m_currentBoard, tiles);
            if (stratSucceed) {
                didStepSucceed = true;
                break;
            }
        }

        if (!didStepSucceed && m_allowedRecursionDepth > 0) {
            RecursiveStrategy recursiveStrategy(m_allowedRecursionDepth);
            didStepSucceed = recursiveStrategy.SolveStep(m_currentBoard, tiles);
        }

        stepCounter++;

#ifdef _DEBUG
        // Copy solved cells to board
        for (int i = 0; i < tiles.size(); i++) {
            if (tiles[i].solved) {
                if (tiles[i].possibles.size() > 0)
                    m_currentBoard->SetTile(i, tiles[i].GetTile());
            }
        }
        AsciiBoardOutput op;
        std::cout << op.Format(*m_currentBoard) << std::endl;
#endif

    } while (didStepSucceed); // Keep doing strategies until they change nothing

#ifdef _DEBUG
    std::cout << "Solving took " << stepCounter << " steps" << std::endl;
#endif

    return tiles;
}
