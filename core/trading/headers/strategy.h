
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
#include "core/models/headers/portfolio.h"
#include "core/models/headers/pricehistory.h"
using std::pair;
using std::string;
using std::vector;

class TradingStrategy
{
private:
    // A vector of moving averages that can be used to calculate
    // simple moving averages. These averages will help smooth
    // out the noise regarding the price movement and trend of
    // the stock.
    vector<int> moving_averages;

    // A vector of exponentional moving averages. These averages
    // add more weight to the most recent of prices, reflecting
    // current movements within the stock pricing.
    vector<int> exponential_moving_averages;

public:
    // Constructors
    TradingStrategy();
    TradingStrategy(const vector<int> moving_averages);
    TradingStrategy(const vector<int> moving_averages, vector<int> exponential_moving_averages);

    // Copy Constructor
    TradingStrategy(const TradingStrategy &obj);
    // Copy Assignment
    TradingStrategy &operator=(const TradingStrategy &obj);

    // Deconstructor
    ~TradingStrategy(){};

    // ===================================== PUBLIC METHODS =========================================

    void set_moving_averages(const vector<int> values);

    void set_exponential_moving_averages(const vector<int> values);

    void execute_arbitrage_strategy(Portfolio &portfolio, vector<PriceHistory> &stocks);

    void execute_mean_reversion_strategy(Portfolio &portfolio, vector<PriceHistory> &stocks);

    void execute_scalping_strategy(Portfolio &portfolio, vector<PriceHistory> &stocks);

    void execute_momentum_strategy(Portfolio &portfolio, vector<PriceHistory> &stocks);

    void execute_pairs_trading_strategy(Portfolio &portfolio, vector<pair<PriceHistory, PriceHistory>> &ticker_pairs);

    void execute_bollinger_band_strategy(Portfolio &portfolio, vector<PriceHistory> &stocks);

    // The moving average strategy will take in a portfolio class and vector of stocks
    // and their price history, and will return a unorder mapping of stocks and the
    // amount of shares that should be up for consideration to buy given portfolio
    // constraints designated, and the moving averages and exponential moving averages specified.
    void execute_moving_average_strategy(Portfolio &portfolio, vector<PriceHistory> &stocks);
};