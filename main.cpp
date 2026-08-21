#include "csv_utils.h"
#include "dynamics.h"
#include "finance.h"
#include "markov.h"
#include "simulation.h"
#include "strategies.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void printMatrix(
    const vector<StrategyType>& strategies,
    const Matrix& matrix
) {
    cout << "\nEvolutionary Payoff Matrix\n\n";
    cout << setw(25) << "";

    for (StrategyType strategy : strategies) {
        cout << setw(22) << strategyName(strategy);
    }

    cout << "\n";

    for (int i = 0; i < static_cast<int>(matrix.size()); ++i) {
        cout << setw(25) << strategyName(strategies[i]);

        for (double value : matrix[i]) {
            cout << setw(22)
                 << fixed
                 << setprecision(2)
                 << value;
        }

        cout << "\n";
    }
}

int main() {
    vector<StrategyType> strategies = {
        StrategyType::AlwaysCooperate,
        StrategyType::AlwaysDefect,
        StrategyType::TitForTat,
        StrategyType::GrimTrigger,
        StrategyType::WinStayLoseShift,
        StrategyType::GenerousTitForTat
    };

    PrisonersDilemma game(3.0, 0.0, 5.0, 1.0);

    int rounds = 75;
    double discountFactor = 0.97;
    double errorProbability = 0.02;
    int repetitions = 100;

    Matrix payoffMatrix = buildStrategyPayoffMatrix(
        game,
        strategies,
        rounds,
        discountFactor,
        errorProbability,
        repetitions
    );

    printMatrix(strategies, payoffMatrix);

    Vector initialPopulation(
        strategies.size(),
        1.0 / strategies.size()
    );

    int steps = 400;
    double stepSize = 0.002;
    double mutationRate = 0.001;

    Matrix populationHistory = simulateReplicatorDynamics(
        payoffMatrix,
        initialPopulation,
        steps,
        stepSize,
        mutationRate
    );

    cout << "\nFinal Population Shares\n\n";
    const Vector& finalPopulation = populationHistory.back();

    for (int i = 0; i < static_cast<int>(strategies.size()); ++i) {
        cout << setw(25)
             << strategyName(strategies[i])
             << ": "
             << fixed
             << setprecision(4)
             << finalPopulation[i]
             << "\n";
    }

    StrategyType markovOne = StrategyType::TitForTat;
    StrategyType markovTwo = StrategyType::GenerousTitForTat;

    Matrix transition = buildMemoryOneTransitionMatrix(
        markovOne,
        markovTwo,
        errorProbability
    );

    Vector stationary = stationaryDistribution(transition);

    cout << "\nMarkov Analysis: "
         << strategyName(markovOne)
         << " vs "
         << strategyName(markovTwo)
         << "\n\n";

    vector<string> stateNames = {"CC", "CD", "DC", "DD"};

    for (int i = 0; i < 4; ++i) {
        cout << stateNames[i]
             << ": "
             << fixed
             << setprecision(6)
             << stationary[i]
             << "\n";
    }

    cout << "\nLong-run expected payoff for "
         << strategyName(markovOne)
         << ": "
         << expectedLongRunPayoff(game, stationary, true)
         << "\n";

    cout << "Long-run expected payoff for "
         << strategyName(markovTwo)
         << ": "
         << expectedLongRunPayoff(game, stationary, false)
         << "\n";

    vector<string> strategyLabels;
    for (StrategyType strategy : strategies) {
        strategyLabels.push_back(strategyName(strategy));
    }

    writeMatrixCSV(
        "payoff_matrix.csv",
        strategyLabels,
        strategyLabels,
        payoffMatrix
    );

    writePopulationHistoryCSV(
        "population_history.csv",
        strategies,
        populationHistory
    );

    writeMatrixCSV(
        "markov_transition_matrix.csv",
        stateNames,
        stateNames,
        transition
    );

    double callPrice = blackScholesCall(
        100.0,
        100.0,
        0.05,
        0.20,
        1.0
    );

    cout << "\nOptional Finance Extension\n";
    cout << "Black-Scholes call price: $"
         << fixed
         << setprecision(2)
         << callPrice
         << "\n";

    cout << "\nCSV files written successfully.\n";
    return 0;
}
