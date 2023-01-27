#include "headers/strategy.h"
#include "core/models/headers/portfolio.h"
#include "core/models/headers/pricehistory.h"
#include "core/predictor/headers/analyzer.h"
#include <vector>
#include <utility>
using namespace std;

TradingStrategy::TradingStrategy() : moving_averages(), exponential_moving_averages() {}

TradingStrategy::TradingStrategy(const vector<double> moving_averages) : moving_averages(moving_averages), exponential_moving_averages() {}

TradingStrategy::TradingStrategy(const vector<double> moving_a, vector<double> exp_mov_a) : moving_averages(moving_a), exponential_moving_averages(exp_mov_a) {}

TradingStrategy::TradingStrategy(const TradingStrategy &obj) : moving_averages(obj.moving_averages), exponential_moving_averages(obj.exponential_moving_averages) {}

TradingStrategy &TradingStrategy::operator=(const TradingStrategy &obj)
{
    moving_averages = obj.moving_averages;
    exponential_moving_averages = obj.exponential_moving_averages;
    return *this;
}

//===================================================== PRIVATE METHODS ==================================================================//

//===================================================== PUBLIC METHODS ==================================================================//

void TradingStrategy::set_moving_averages(const vector<double> value) { moving_averages = value; }

void TradingStrategy::set_exponential_moving_averages(const vector<double> value) { exponential_moving_averages = value; }

void TradingStrategy::execute_moving_average_strategy(Portfolio &port, vector<PriceHistory> &stockVec) {}

void TradingStrategy::execute_arbitrage_strategy(Portfolio &port, vector<PriceHistory> &stockVec) {}

void TradingStrategy::execute_mean_reversion_strategy(Portfolio &port, vector<PriceHistory> &stockVec) {}

void TradingStrategy::execute_scalping_strategy(Portfolio &port, vector<PriceHistory> &stockVec, const int &duration) {}

void TradingStrategy::execute_momentum_strategy(Portfolio &port, vector<PriceHistory> &stockVec, MovingAverageType &type)
{
    double settled_funds = port.get_current_capital();
    double useable_funds = (settled_funds * 0.10) / stockVec.size();
    Analyzer *analyzer = new Analyzer(5.0, 0.05);

    unordered_map<PriceHistory, map<double, vector<pair<double, double>>>> ma;

    if (type == MovingAverageType::SIMPLE)
    {
        ma = analyzer->generate_moving_averages_map(stockVec, moving_averages, type);
    }
    else if (type == MovingAverageType::EXPONENTIAL)
    {
        ma = analyzer->generate_moving_averages_map(stockVec, moving_averages, type);
    }

    for (auto &stock : stockVec)
    {
        auto twenty_day_ma = ma[stock][20.00];
        auto candles = stock.get_candles();

        for (auto candle : candles)
        {
            if (candle.close > twenty_day_ma.at(candle.datetime).second)
            {
            }
        }
    }
}

void TradingStrategy::execute_pairs_trading_strategy(Portfolio &port, vector<pair<PriceHistory, PriceHistory>> &stockPairVec) {}

void TradingStrategy::execute_bollinger_band_strategy(Portfolio &port, vector<PriceHistory> &stockVec) {}