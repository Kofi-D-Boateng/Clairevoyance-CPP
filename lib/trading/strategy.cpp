
#include "include/portfolio.h"
#include "include/pricehistory.h"
#include "include/strategy.h"
#include "include/analyzer.h"
#include <vector>
#include <utility>
using namespace std;

TradingStrategy::TradingStrategy(Analyzer &a) : analyzer(a) {}
//===================================================== PRIVATE METHODS ==================================================================//

//===================================================== PUBLIC METHODS ==================================================================//

void TradingStrategy::execute_moving_average_strategy(Portfolio &port, vector<PriceHistory> &stockVec, const double &window_size, MovingAverageType &type)
{
    double settled_funds = port.get_current_capital();
    double useable_funds = (settled_funds * 0.10) / stockVec.size();

    unordered_map<PriceHistory, map<double, vector<pair<double, double>>>> ma;

    if (type == MovingAverageType::SIMPLE)
    {
        ma = this->analyzer.generate_moving_averages_map(stockVec, window_size, type);
    }
    else if (type == MovingAverageType::EXPONENTIAL)
    {
        ma = this->analyzer.generate_moving_averages_map(stockVec, window_size, type);
    }

    for (auto &stock : stockVec)
    {
        auto twenty_day_ma = ma[stock][window_size];
        auto candles = stock.get_candles();

        for (auto candle : candles)
        {
            if (candle.close > twenty_day_ma.at(candle.datetime).second)
            {
                // SINGLE LONG (GENERATE LONG POSITION)
            }
            else
            {
                // SINGLE SHORT (GENERATE SHORT POSITION || OFFLOAD)
            }
        }
    }
}

void TradingStrategy::execute_arbitrage_strategy(Portfolio &port, vector<PriceHistory> &stockVec) {}

void TradingStrategy::execute_mean_reversion_strategy(Portfolio &port, vector<PriceHistory> &stockVec) {}

void TradingStrategy::execute_scalping_strategy(Portfolio &port, vector<PriceHistory> &stockVec, const int &duration) {}

void TradingStrategy::execute_momentum_strategy(Portfolio &port, vector<PriceHistory> &stockVec, MovingAverageType &type)
{
}

void TradingStrategy::execute_pairs_trading_strategy(Portfolio &port, vector<pair<PriceHistory, PriceHistory>> &stockPairVec) {}

void TradingStrategy::execute_bollinger_band_strategy(Portfolio &port, vector<PriceHistory> &stockVec, const double &window_size, const int &std) {}