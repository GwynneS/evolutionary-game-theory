#include "finance.h"
#include <cmath>

double normalCDF(double x) {
    return 0.5 * std::erfc(-x / std::sqrt(2.0));
}

double blackScholesCall(
    double stockPrice,
    double strikePrice,
    double riskFreeRate,
    double volatility,
    double timeToMaturity
) {
    double d1 =
        (
            std::log(stockPrice / strikePrice)
            + (riskFreeRate + 0.5 * volatility * volatility) * timeToMaturity
        )
        /
        (volatility * std::sqrt(timeToMaturity));

    double d2 = d1 - volatility * std::sqrt(timeToMaturity);

    return
        stockPrice * normalCDF(d1)
        - strikePrice
        * std::exp(-riskFreeRate * timeToMaturity)
        * normalCDF(d2);
}
