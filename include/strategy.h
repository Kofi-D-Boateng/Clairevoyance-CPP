
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

class Strategy{
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

        Strategy(Analyzer &analyzer, double &strong_buy_percent,double &buy_percent,double &sell_percent,double &strong_sell_percent);

        virtual void arbitrage_strategy(Portfolio &portfolio, vector<PriceHistory> &stocks, unique_ptr<TradeSignal> &signal) = 0;
        /*
            The Mean Reversion Strategy will look for opportunities to make trades where the current trend in the stock is attempting
            to revert back to the mean. 
        */
        virtual void mean_reversion_strategy(vector<PriceHistory> &stocks, const double &window_size, MovingAverageType &type,vector<pair<PriceHistory,unique_ptr<TradeSignal>>> &signal_vec) = 0;

        virtual void mean_reversion_strategy(PriceHistory &stocks, const double &window_size, MovingAverageType &type,unique_ptr<TradeSignal> &signal) = 0;
        
        virtual void scalping_strategy(vector<PriceHistory> &stocks, const double &window_size, const MovingAverageType &type,vector<pair<PriceHistory,unique_ptr<TradeSignal>>> &signal_pair_vec) = 0;

        virtual void pairs_trading_strategy(vector<pair<PriceHistory, PriceHistory>> &ticker_pairs,const MovingAverageType &type, vector<pair<pair<PriceHistory, PriceHistory>,unique_ptr<TradeSignal>>> &signal_pair_vec) = 0;

        virtual void pairs_trading_strategy(pair<PriceHistory, PriceHistory> &stock_pairs,const MovingAverageType &type,unique_ptr<TradeSignal> &signal) = 0;

        virtual void bollinger_band_strategy(vector<PriceHistory> &stocks, const MovingAverageType &type, const double &window_size, const int &std, vector<pair<PriceHistory,unique_ptr<TradeSignal>>> &signal_pair_vec) = 0;

        virtual void bollinger_band_strategy(PriceHistory &stocks,const MovingAverageType &type, const double &window_size, const int &std,unique_ptr<TradeSignal> &signal) = 0;

        /*
            The moving average strategy will take in a portfolio class and vector of stocks
            and their price history, and will return a unorder mapping of stocks and the
            amount of shares that should be up for consideration to buy given portfolio
            constraints designated, and the moving averages and exponential moving averages specified.
        */
        virtual void moving_average_strategy(vector<PriceHistory> &stocks, double &window, MovingAverageType &type,vector<pair<PriceHistory,unique_ptr<TradeSignal>>> &signal_pair_vec) = 0;

        /*
            The MA strategy uses a single average as the bases to which we will decide
            whether to go long or go short.
        */
        virtual void moving_average_strategy(PriceHistory &stock, double &window, MovingAverageType &type, unique_ptr<TradeSignal> &signal) = 0; 
        /*
            The DMAC strategy will use two averages of either simple or exponential,
            with one being fast, to capture the current trend of the stock, and one
            slow, to caputre the overall trend of the stock, over a period of time.
        */
        virtual void execute_dual_moving_average_strategy(PriceHistory& stock, double& first_window, double& second_window, MovingAverageType& type, unique_ptr<TradeSignal> &signal) = 0;

        virtual ~Strategy(){};
};  









/*
    A class that handles all the different type of trading strategies that
    can be implemented in the stock market.
*/
class Trader: Strategy
{

public:
    // Constructors
    Trader(Analyzer &analyzer, double &strong_buy_percent,double &buy_percent,double &sell_percent,double &strong_sell_percent);
    // Deconstructor
    virtual ~Trader(){};

    // ===================================== PUBLIC METHODS =========================================
    virtual void arbitrage_strategy(Portfolio &portfolio, vector<PriceHistory> &stocks, unique_ptr<TradeSignal> &signal)override;
    /*
        The Mean Reversion Strategy will look for opportunities to make trades where the current trend in the stock is attempting
        to revert back to the mean. 
    */
    virtual void mean_reversion_strategy(vector<PriceHistory> &stocks, const double &window_size,  MovingAverageType &type,vector<pair<PriceHistory,unique_ptr<TradeSignal>>> &signal_pair_vec)override;

    virtual void mean_reversion_strategy(PriceHistory &stock, const double &window_size,  MovingAverageType &type,unique_ptr<TradeSignal> &signal)override;

    virtual void scalping_strategy(vector<PriceHistory> &stocks, const double &window_size, const MovingAverageType &type,vector<pair<PriceHistory,unique_ptr<TradeSignal>>> &signal_pair_vec);

    virtual void pairs_trading_strategy(vector<pair<PriceHistory, PriceHistory>> &ticker_pairs,const MovingAverageType &type,vector<pair<pair<PriceHistory, PriceHistory>,unique_ptr<TradeSignal>>> &signal_pairs_vec);

    virtual void pairs_trading_strategy(pair<PriceHistory, PriceHistory> &stock_pairs,const MovingAverageType &type,unique_ptr<TradeSignal> &signal);

    virtual void bollinger_band_strategy(vector<PriceHistory> &stocks, const MovingAverageType &type, const double &window_size, const int &std,vector<pair<PriceHistory,unique_ptr<TradeSignal>>> &signal_pairs_vec);

    virtual void bollinger_band_strategy(PriceHistory &stocks,const MovingAverageType &type, const double &window_size, const int &std,unique_ptr<TradeSignal> &signal);


    /*
        The moving average strategy will take in a portfolio class and vector of stocks
        and their price history, and will return a unorder mapping of stocks and the
        amount of shares that should be up for consideration to buy given portfolio
        constraints designated, and the moving averages and exponential moving averages specified.
    */
    virtual void moving_average_strategy(vector<PriceHistory> &stocks, double &window, MovingAverageType &type,vector<pair<PriceHistory,unique_ptr<TradeSignal>>> &signal_pair_vec)override;

    /*
        The MA strategy uses a single average as the bases to which we will decide
        whether to go long or go short.
    */
    virtual void moving_average_strategy(PriceHistory &stock, double &window, MovingAverageType &type, unique_ptr<TradeSignal> &signal)override; 
    /*
        The DMAC strategy will use two averages of either simple or exponential,
        with one being fast, to capture the current trend of the stock, and one
        slow, to caputre the overall trend of the stock, over a period of time.
    */
    unique_ptr<TradeSignal> execute_dual_moving_average_strategy(PriceHistory& stock, double& fast_window, double& slow_window, MovingAverageType& type);
};


class BackTester : public Strategy{
    public:
        BackTester(Analyzer &analyzer, double &strong_buy_percent,double &buy_percent,double &sell_percent,double &strong_sell_percent);
        virtual ~BackTester(){};

        virtual void arbitrage_strategy(Portfolio &portfolio, vector<PriceHistory> &stocks, unique_ptr<TradeSignal> &signal) = 0;
        /*
            The Mean Reversion Strategy will look for opportunities to make trades where the current trend in the stock is attempting
            to revert back to the mean. 
        */
        virtual void mean_reversion_strategy(vector<PriceHistory> &stocks, const double &window_size, MovingAverageType &type,vector<pair<PriceHistory,unique_ptr<TradeSignal>>> &signal_vec)override;

        virtual void mean_reversion_strategy(PriceHistory &stocks, const double &window_size, MovingAverageType &type,unique_ptr<TradeSignal> &signal)override;

        virtual void scalping_strategy(vector<PriceHistory> &stocks, const double &window_size, const MovingAverageType &type,vector<pair<PriceHistory,unique_ptr<TradeSignal>>> &signal_pair_vec)override;

        virtual void pairs_trading_strategy(vector<pair<PriceHistory, PriceHistory>> &ticker_pairs,const MovingAverageType &type, vector<pair<pair<PriceHistory, PriceHistory>,unique_ptr<TradeSignal>>> &signal_pair_vec)override;

        virtual void pairs_trading_strategy(pair<PriceHistory, PriceHistory> &stock_pairs,const MovingAverageType &type,unique_ptr<TradeSignal> &signal)override;

        virtual void bollinger_band_strategy(vector<PriceHistory> &stocks, const MovingAverageType &type, const double &window_size, const int &std, vector<pair<PriceHistory,unique_ptr<TradeSignal>>> &signal_pair_vec)override;

        virtual void bollinger_band_strategy(PriceHistory &stock,const MovingAverageType &type, const double &window_size, const int &std,unique_ptr<TradeSignal> &signal)override;

        /*
            The moving average strategy will take in a portfolio class and vector of stocks
            and their price history, and will return a unorder mapping of stocks and the
            amount of shares that should be up for consideration to buy given portfolio
            constraints designated, and the moving averages and exponential moving averages specified.
        */
        virtual void moving_average_strategy(vector<PriceHistory> &stocks, double &window, MovingAverageType &type,vector<pair<PriceHistory,unique_ptr<TradeSignal>>> &signal_pair_vec)override;

        /*
            The MA strategy uses a single average as the bases to which we will decide
            whether to go long or go short.
        */
        virtual void moving_average_strategy(PriceHistory &stock, double &window, MovingAverageType &type, unique_ptr<TradeSignal> &signal)override; 
        /*
            The DMAC strategy will use two averages of either simple or exponential,
            with one being fast, to capture the current trend of the stock, and one
            slow, to caputre the overall trend of the stock, over a period of time.
        */
        virtual void execute_dual_moving_average_strategy(PriceHistory& stock, double& first_window, double& second_window, MovingAverageType& type, unique_ptr<TradeSignal> &signal)override;


};