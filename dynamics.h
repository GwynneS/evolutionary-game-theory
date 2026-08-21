#ifndef DYNAMICS_H
#define DYNAMICS_H

#include "linear_algebra.h"

Vector replicatorStep(
    const Matrix& payoffMatrix,
    const Vector& population,
    double stepSize,
    double mutationRate = 0.0
);

Matrix simulateReplicatorDynamics(
    const Matrix& payoffMatrix,
    const Vector& initialPopulation,
    int steps,
    double stepSize,
    double mutationRate = 0.0
);

#endif
