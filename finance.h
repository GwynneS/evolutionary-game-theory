#ifndef FINANCE_H
#define FINANCE_H

double normalCDF(double x);

double blackScholesCall(
    double stockPrice,
    double strikePrice,
    double riskFreeRate,
    double volatility,
    double timeToMaturity
);

#endif
