#ifndef SIMULATION_H
#define SIMULATION_H

#include "strategies.h"
#include <array>
#include <vector>

struct GameResult {
    double playerOneScore;
    double playerTwoScore;
};

class PrisonersDilemma {
public:
    PrisonersDilemma(
        double reward = 3.0,
        double sucker = 0.0,
        double temptation = 5.0,
        double punishment = 1.0
    );

    double payoff(Move playerMove, Move opponentMove) const;

    GameResult playRepeatedGame(
        StrategyType playerOne,
        StrategyType playerTwo,
        int rounds,
        double discountFactor = 1.0,
        double errorProbability = 0.0,
        double generosity = 0.10
    ) const;

private:
    std::array<std::array<double, 2>, 2> payoffMatrix;
};

std::vector<std::vector<double>> buildStrategyPayoffMatrix(
    const PrisonersDilemma& game,
    const std::vector<StrategyType>& strategies,
    int rounds,
    double discountFactor,
    double errorProbability,
    int repetitions
);

#endif
