#include "headers/strategy.h"
#include "core/models/headers/portfolio.h"
#include <vector>
using std::string;
using std::vector;

TradingStrategy::TradingStrategy() : moving_averages(), exponential_moving_averages() {}

TradingStrategy::TradingStrategy(const vector<int> moving_averages) : moving_averages(moving_averages), exponential_moving_averages() {}

TradingStrategy::TradingStrategy(const vector<int> moving_a, vector<int> exp_mov_a) : moving_averages(moving_a), exponential_moving_averages(exp_mov_a) {}

TradingStrategy::TradingStrategy(const TradingStrategy &obj) : moving_averages(obj.moving_averages), exponential_moving_averages(obj.exponential_moving_averages) {}

TradingStrategy &TradingStrategy::operator=(const TradingStrategy &obj)
{
    moving_averages = obj.moving_averages;
    exponential_moving_averages = obj.exponential_moving_averages;
    return *this;
}

//===================================================== PRIVATE METHODS ==================================================================//

//===================================================== PUBLIC METHODS ==================================================================//

void TradingStrategy::set_moving_averages(const vector<int> value) { moving_averages = value; }

void TradingStrategy::set_exponential_moving_averages(const vector<int> value) { exponential_moving_averages = value; }

void TradingStrategy::execute_moving_average_strategy(Portfolio &port, vector<string> &tickers) {}

void TradingStrategy::execute_arbitrage_strategy(Portfolio &port, vector<string> &tickers) {}

void TradingStrategy::execute_mean_reversion_strategy(Portfolio &port, vector<string> &tickers) {}

void TradingStrategy::execute_scalping_strategy(Portfolio &port, vector<string> &tickers) {}

void TradingStrategy::execute_momentum_strategy(Portfolio &port, vector<string> &tickers) {}

void TradingStrategy::execute_pairs_trading_strategy(Portfolio &port, vector<string> &tickers) {}