#include "csv_utils.h"
#include <fstream>

void writeMatrixCSV(
    const std::string& filename,
    const std::vector<std::string>& rowLabels,
    const std::vector<std::string>& columnLabels,
    const Matrix& matrix
) {
    std::ofstream file(filename);

    file << "Row";
    for (const std::string& label : columnLabels) {
        file << "," << label;
    }
    file << "\n";

    for (int i = 0; i < static_cast<int>(matrix.size()); ++i) {
        file << rowLabels[i];
        for (double value : matrix[i]) {
            file << "," << value;
        }
        file << "\n";
    }
}

void writePopulationHistoryCSV(
    const std::string& filename,
    const std::vector<StrategyType>& strategies,
    const Matrix& history
) {
    std::ofstream file(filename);

    file << "Step";
    for (StrategyType strategy : strategies) {
        file << "," << strategyName(strategy);
    }
    file << "\n";

    for (int step = 0; step < static_cast<int>(history.size()); ++step) {
        file << step;
        for (double value : history[step]) {
            file << "," << value;
        }
        file << "\n";
    }
}
