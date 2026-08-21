#include "dynamics.h"

Vector replicatorStep(
    const Matrix& payoffMatrix,
    const Vector& population,
    double stepSize,
    double mutationRate
) {
    Vector fitness = multiply(payoffMatrix, population);
    double averageFitness = dot(population, fitness);

    int n = static_cast<int>(population.size());
    Vector next(n, 0.0);

    for (int i = 0; i < n; ++i) {
        double growth = population[i] * (fitness[i] - averageFitness);
        next[i] = population[i] + stepSize * growth;

        if (mutationRate > 0.0) {
            double uniformShare = 1.0 / n;
            next[i] = (1.0 - mutationRate) * next[i]
                    + mutationRate * uniformShare;
        }

        if (next[i] < 0.0) next[i] = 0.0;
    }

    return normalizeProbability(next);
}

Matrix simulateReplicatorDynamics(
    const Matrix& payoffMatrix,
    const Vector& initialPopulation,
    int steps,
    double stepSize,
    double mutationRate
) {
    Matrix history;
    Vector population = normalizeProbability(initialPopulation);

    history.push_back(population);

    for (int step = 0; step < steps; ++step) {
        population = replicatorStep(
            payoffMatrix,
            population,
            stepSize,
            mutationRate
        );
        history.push_back(population);
    }

    return history;
}
