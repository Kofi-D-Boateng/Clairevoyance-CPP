
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
#include <memory>
#include "include/portfolio.h"
#include "include/pricehistory.h"
#include "include/analyzer.h"
#include "include/enums.h"

using std::pair;
using std::string;
using std::vector;
using std::unique_ptr;

/*
    A class that handles all the different type of trading strategies that
    can be implemented in the stock market.
*/
class TradingStrategy
{
private:
    /*
        The analyzer class is a standalone class that includes several
        features such as generating moving averages.
    */
    Analyzer analyzer;

    /*
        A percent that is used to single a strong buy response.
    */
    double strong_buy_percent;

    /*
        A percent that is used to single a buy response.
    */
    double buy_percent;

    /*
        A percent that is used to single a sell response.
    */
    double sell_percent;

    /*
        A percent that is used to single a strong sell response.
    */
    double strong_sell_percent;

public:
    // Constructors
    TradingStrategy(Analyzer &analyzer, double &strong_buy_percent,double &buy_percent,double &sell_percent,double &strong_sell_percent);
    // Deconstructor
    ~TradingStrategy(){};

    // ===================================== PUBLIC METHODS =========================================

    TradeSignal execute_arbitrage_strategy(Portfolio &portfolio, vector<PriceHistory> &stocks);
    /*
        The Mean Reversion Strategy will look for opportunities to make trades where the current trend in the stock is attempting
        to revert back to the mean. 
    */
   unique_ptr<vector<pair<PriceHistory,TradeSignal>>> execute_mean_reversion_strategy(vector<PriceHistory> &stocks, const double &window_size, const MovingAverageType &type);

    TradeSignal mean_reversion_strategy(const PriceHistory &stocks, const double &window_size, const MovingAverageType &type);

    TradeSignal execute_scalping_strategy(vector<PriceHistory> &stocks, const double &window_size, const MovingAverageType &type, const int &duration);

    TradeSignal execute_momentum_strategy(vector<PriceHistory> &stocks, MovingAverageType &type);

    unique_ptr<vector<pair<pair<PriceHistory, PriceHistory>,TradeSignal>>> execute_pairs_trading_strategy(vector<pair<PriceHistory, PriceHistory>> &ticker_pairs,const MovingAverageType &type);

    TradeSignal pairs_trading_strategy(const pair<PriceHistory, PriceHistory> &stock_pairs,const MovingAverageType &type);

    unique_ptr<vector<pair<PriceHistory,TradeSignal>>> execute_bollinger_band_strategy(vector<PriceHistory> &stocks, const MovingAverageType &type, const double &window_size, const int &std);

    TradeSignal bollinger_band_strategy(const PriceHistory &stocks,const MovingAverageType &type, const double &window_size, const int &std);


    /*
        The moving average strategy will take in a portfolio class and vector of stocks
        and their price history, and will return a unorder mapping of stocks and the
        amount of shares that should be up for consideration to buy given portfolio
        constraints designated, and the moving averages and exponential moving averages specified.
    */
    unique_ptr<vector<pair<PriceHistory,TradeSignal>>> execute_moving_average_strategy(vector<PriceHistory> &stocks, double &window, MovingAverageType &type);

    /*
        The MA strategy uses a single average as the bases to which we will decide
        whether to go long or go short.
    */
    TradeSignal execute_moving_average_strategy(PriceHistory &stock, double &window, MovingAverageType &type); 
    /*
        The DMAC strategy will use two averages of either simple or exponential,
        with one being fast, to capture the current trend of the stock, and one
        slow, to caputre the overall trend of the stock, over a period of time.
    */
    TradeSignal execute_dual_moving_average_strategy(PriceHistory& stock, double& fast_window, double& slow_window, MovingAverageType& type);
};