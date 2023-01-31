
/**
 * @file Strategy.h
 * @author Kofi Boateng
 * @date 2023-01-05
 */

#pragma once

#include <iostream>
#include <stdexcept>
#include <ostream>
#include <vector>
#include <string>
#include <utility>
#include "portfolio.h"
#include "pricehistory.h"
#include "analyzer.h"
using std::pair;
using std::string;
using std::vector;

class TradingStrategy
{
private:
    /*
        The analyzer class is a standalone class that includes several
        features such as generating moving averages.
    */
    Analyzer analyzer;

public:
    // Constructors
    TradingStrategy(Analyzer &analyzer);
    // Deconstructor
    ~TradingStrategy(){};

    // ===================================== PUBLIC METHODS =========================================

    void execute_arbitrage_strategy(Portfolio &portfolio, vector<PriceHistory> &stocks);

    void execute_mean_reversion_strategy(Portfolio &portfolio, vector<PriceHistory> &stocks);

    void execute_scalping_strategy(Portfolio &portfolio, vector<PriceHistory> &stocks, const int &duration);

    void execute_momentum_strategy(Portfolio &portfolio, vector<PriceHistory> &stocks, MovingAverageType &type);

    void execute_pairs_trading_strategy(Portfolio &portfolio, vector<pair<PriceHistory, PriceHistory>> &ticker_pairs);

    void execute_bollinger_band_strategy(Portfolio &portfolio, vector<PriceHistory> &stocks, const double &window_size, const int &std);

    // The moving average strategy will take in a portfolio class and vector of stocks
    // and their price history, and will return a unorder mapping of stocks and the
    // amount of shares that should be up for consideration to buy given portfolio
    // constraints designated, and the moving averages and exponential moving averages specified.
    void execute_moving_average_strategy(Portfolio &portfolio, vector<PriceHistory> &stocks, const double &window_size, MovingAverageType &type);
};