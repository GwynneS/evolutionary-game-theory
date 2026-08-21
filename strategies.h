#ifndef STRATEGIES_H
#define STRATEGIES_H

#include <string>
#include <vector>

enum class Move {
    Cooperate = 0,
    Defect = 1
};

enum class StrategyType {
    AlwaysCooperate,
    AlwaysDefect,
    TitForTat,
    GrimTrigger,
    WinStayLoseShift,
    GenerousTitForTat
};

std::string strategyName(StrategyType strategy);

double cooperationProbability(
    StrategyType strategy,
    const std::vector<Move>& ownHistory,
    const std::vector<Move>& opponentHistory,
    double generosity = 0.10
);

Move chooseMove(
    StrategyType strategy,
    const std::vector<Move>& ownHistory,
    const std::vector<Move>& opponentHistory,
    double errorProbability = 0.0,
    double generosity = 0.10
);

#endif
