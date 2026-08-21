#ifndef CSV_UTILS_H
#define CSV_UTILS_H

#include "linear_algebra.h"
#include "strategies.h"
#include <string>
#include <vector>

void writeMatrixCSV(
    const std::string& filename,
    const std::vector<std::string>& rowLabels,
    const std::vector<std::string>& columnLabels,
    const Matrix& matrix
);

void writePopulationHistoryCSV(
    const std::string& filename,
    const std::vector<StrategyType>& strategies,
    const Matrix& history
);

#endif
