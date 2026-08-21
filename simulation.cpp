#include "simulation.h"
#include <cmath>

PrisonersDilemma::PrisonersDilemma(
    double reward,
    double sucker,
    double temptation,
    double punishment
) {
    payoffMatrix = {{
        {{reward, sucker}},
        {{temptation, punishment}}
    }};
}

double PrisonersDilemma::payoff(Move playerMove, Move opponentMove) const {
    int row = static_cast<int>(playerMove);
    int column = static_cast<int>(opponentMove);
    return payoffMatrix[row][column];
}

GameResult PrisonersDilemma::playRepeatedGame(
    StrategyType playerOne,
    StrategyType playerTwo,
    int rounds,
    double discountFactor,
    double errorProbability,
    double generosity
) const {
    std::vector<Move> playerOneHistory;
    std::vector<Move> playerTwoHistory;
    double playerOneScore = 0.0;
    double playerTwoScore = 0.0;

    for (int round = 0; round < rounds; ++round) {
        Move moveOne = chooseMove(
            playerOne, playerOneHistory, playerTwoHistory,
            errorProbability, generosity
        );

        Move moveTwo = chooseMove(
            playerTwo, playerTwoHistory, playerOneHistory,
            errorProbability, generosity
        );

        double weight = std::pow(discountFactor, round);
        playerOneScore += weight * payoff(moveOne, moveTwo);
        playerTwoScore += weight * payoff(moveTwo, moveOne);

        playerOneHistory.push_back(moveOne);
        playerTwoHistory.push_back(moveTwo);
    }

    return {playerOneScore, playerTwoScore};
}

std::vector<std::vector<double>> buildStrategyPayoffMatrix(
    const PrisonersDilemma& game,
    const std::vector<StrategyType>& strategies,
    int rounds,
    double discountFactor,
    double errorProbability,
    int repetitions
) {
    int n = static_cast<int>(strategies.size());
    std::vector<std::vector<double>> matrix(n, std::vector<double>(n, 0.0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double total = 0.0;

            for (int r = 0; r < repetitions; ++r) {
                GameResult result = game.playRepeatedGame(
                    strategies[i], strategies[j], rounds,
                    discountFactor, errorProbability
                );
                total += result.playerOneScore;
            }

            matrix[i][j] = total / repetitions;
        }
    }

    return matrix;
}
