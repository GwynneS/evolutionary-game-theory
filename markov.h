#ifndef MARKOV_H
#define MARKOV_H

#include "linear_algebra.h"
#include "simulation.h"

enum class InteractionState {
    CC = 0,
    CD = 1,
    DC = 2,
    DD = 3
};

Matrix buildMemoryOneTransitionMatrix(
    StrategyType playerOne,
    StrategyType playerTwo,
    double errorProbability,
    double generosity = 0.10
);

Vector stationaryDistribution(const Matrix& transitionMatrix);

double expectedLongRunPayoff(
    const PrisonersDilemma& game,
    const Vector& stationary,
    bool playerOne
);

#endif
