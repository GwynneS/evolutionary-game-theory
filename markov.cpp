#include "markov.h"
#include <utility>
#include <vector>

namespace {
    std::pair<Move, Move> stateMoves(int state) {
        switch (state) {
            case 0: return {Move::Cooperate, Move::Cooperate};
            case 1: return {Move::Cooperate, Move::Defect};
            case 2: return {Move::Defect, Move::Cooperate};
            default: return {Move::Defect, Move::Defect};
        }
    }

    double observedCooperationProbability(
        StrategyType strategy,
        Move ownPrevious,
        Move opponentPrevious,
        double errorProbability,
        double generosity
    ) {
        std::vector<Move> ownHistory = {ownPrevious};
        std::vector<Move> opponentHistory = {opponentPrevious};

        double intended = cooperationProbability(
            strategy,
            ownHistory,
            opponentHistory,
            generosity
        );

        return intended * (1.0 - errorProbability)
             + (1.0 - intended) * errorProbability;
    }
}

Matrix buildMemoryOneTransitionMatrix(
    StrategyType playerOne,
    StrategyType playerTwo,
    double errorProbability,
    double generosity
) {
    Matrix transition(4, Vector(4, 0.0));

    for (int state = 0; state < 4; ++state) {
        auto previous = stateMoves(state);

        double p1Cooperate = observedCooperationProbability(
            playerOne,
            previous.first,
            previous.second,
            errorProbability,
            generosity
        );

        double p2Cooperate = observedCooperationProbability(
            playerTwo,
            previous.second,
            previous.first,
            errorProbability,
            generosity
        );

        transition[state][0] = p1Cooperate * p2Cooperate;
        transition[state][1] = p1Cooperate * (1.0 - p2Cooperate);
        transition[state][2] = (1.0 - p1Cooperate) * p2Cooperate;
        transition[state][3] = (1.0 - p1Cooperate) * (1.0 - p2Cooperate);
    }

    return transition;
}

Vector stationaryDistribution(const Matrix& transitionMatrix) {
    Vector initial = {0.25, 0.25, 0.25, 0.25};
    return powerIteration(transitionMatrix, initial);
}

double expectedLongRunPayoff(
    const PrisonersDilemma& game,
    const Vector& stationary,
    bool playerOne
) {
    double expected = 0.0;

    for (int state = 0; state < 4; ++state) {
        auto moves = stateMoves(state);
        Move ownMove = playerOne ? moves.first : moves.second;
        Move opponentMove = playerOne ? moves.second : moves.first;

        expected += stationary[state] * game.payoff(ownMove, opponentMove);
    }

    return expected;
}
