#include "strategies.h"
#include <random>

namespace {
    std::mt19937& generator() {
        static std::mt19937 gen(std::random_device{}());
        return gen;
    }

    bool randomEvent(double probability) {
        std::bernoulli_distribution distribution(probability);
        return distribution(generator());
    }
}

std::string strategyName(StrategyType strategy) {
    switch (strategy) {
        case StrategyType::AlwaysCooperate: return "Always Cooperate";
        case StrategyType::AlwaysDefect: return "Always Defect";
        case StrategyType::TitForTat: return "Tit for Tat";
        case StrategyType::GrimTrigger: return "Grim Trigger";
        case StrategyType::WinStayLoseShift: return "Win-Stay Lose-Shift";
        case StrategyType::GenerousTitForTat: return "Generous Tit for Tat";
    }
    return "Unknown";
}

double cooperationProbability(
    StrategyType strategy,
    const std::vector<Move>& ownHistory,
    const std::vector<Move>& opponentHistory,
    double generosity
) {
    switch (strategy) {
        case StrategyType::AlwaysCooperate:
            return 1.0;
        case StrategyType::AlwaysDefect:
            return 0.0;
        case StrategyType::TitForTat:
            if (opponentHistory.empty()) return 1.0;
            return opponentHistory.back() == Move::Cooperate ? 1.0 : 0.0;
        case StrategyType::GrimTrigger:
            for (Move move : opponentHistory) {
                if (move == Move::Defect) return 0.0;
            }
            return 1.0;
        case StrategyType::WinStayLoseShift:
            if (ownHistory.empty() || opponentHistory.empty()) return 1.0;
            if (ownHistory.back() == opponentHistory.back()) {
                return ownHistory.back() == Move::Cooperate ? 1.0 : 0.0;
            }
            return ownHistory.back() == Move::Cooperate ? 0.0 : 1.0;
        case StrategyType::GenerousTitForTat:
            if (opponentHistory.empty()) return 1.0;
            if (opponentHistory.back() == Move::Cooperate) return 1.0;
            return generosity;
    }
    return 1.0;
}

Move chooseMove(
    StrategyType strategy,
    const std::vector<Move>& ownHistory,
    const std::vector<Move>& opponentHistory,
    double errorProbability,
    double generosity
) {
    double pCooperate = cooperationProbability(
        strategy, ownHistory, opponentHistory, generosity
    );

    Move intendedMove = randomEvent(pCooperate) ? Move::Cooperate : Move::Defect;

    if (randomEvent(errorProbability)) {
        return intendedMove == Move::Cooperate ? Move::Defect : Move::Cooperate;
    }

    return intendedMove;
}
