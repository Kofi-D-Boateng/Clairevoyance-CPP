
#include <vector>
#include <utility>
#include <map>
#include <mutex>
#include <future>
#include <memory>
#include <queue>
#include <stack>
#include <functional>
#include <cmath>

#include "include/portfolio.h"
#include "include/pricehistory.h"
#include "include/strategy.h"
#include "include/analyzer.h"

using std::map;
using std::vector;
using std::pair;
using std::unique_ptr;
using std::priority_queue;
using std::stack;
using std::greater;
using std::less;
using std::future;
using std::async;


TradingStrategy::TradingStrategy(Analyzer &a,double &strong_buy_percent,double &buy_percent,double &sell_percent,double &strong_sell_percent) : analyzer(a), strong_buy_percent(strong_buy_percent),buy_percent(buy_percent), sell_percent(sell_percent), strong_sell_percent(strong_sell_percent) {}
//===================================================== PRIVATE METHODS ==================================================================//

//===================================================== PUBLIC METHODS ==================================================================//

vector<pair<PriceHistory,TradeSignal>> * TradingStrategy::execute_moving_average_strategy(vector<PriceHistory> &stockVec, double &window, MovingAverageType &type)
{   
    vector<pair<PriceHistory,TradeSignal>> * trade_result_vec = new vector<pair<PriceHistory,TradeSignal>>();
    for(PriceHistory stock:stockVec){

        auto result = execute_moving_average_strategy(stock,window,type);
        (*trade_result_vec).push_back(pair<PriceHistory,TradeSignal>{stock,result});
    }
    return trade_result_vec;    
}

// FINISH THIS METHOD UP
// SET UP TRADE ALERTS WHEN THERE IS NO AVERAGE YET.
TradeSignal TradingStrategy::execute_moving_average_strategy(PriceHistory &stock, double &window, MovingAverageType &type){    
    unique_ptr<std::vector<std::pair<PriceHistory::CandleStick, double>>> avg_vec(this->analyzer.generate_moving_average(stock,window,type));
    TradeSignal signal = TradeSignal::HOLD;
    stack<double> price_change_stack;

    auto vec_ptr = avg_vec.get();
    for (const auto& candle_avg_pair : *vec_ptr) {
        /*
            Accessing the Average Value of our pairs.
        */
        if (candle_avg_pair.second == 0) {

        }
        else {
            if (candle_avg_pair.first.close > candle_avg_pair.second) {
                /*
                    At this moment, the price of the stock is greater than the moving average.
                    We can begin looking at going long, however we will conduct some more analysis on stock
                */
                signal = TradeSignal::LONG;
            }else if(candle_avg_pair.first.close < candle_avg_pair.second){

            }else{

                signal = TradeSignal::HOLD;
            }
        }
    };

    return signal;
}

TradeSignal TradingStrategy::execute_arbitrage_strategy(Portfolio &port, vector<PriceHistory> &stockVec) {}

vector<pair<PriceHistory,TradeSignal>> * TradingStrategy::execute_mean_reversion_strategy(vector<PriceHistory> &stock_vec, const double &window_size, const MovingAverageType &type) {
    vector<pair<PriceHistory,TradeSignal>> * trade_result_vec = new vector<pair<PriceHistory,TradeSignal>>();
    vector<future<TradeSignal>> futures;
    for(const PriceHistory &stock:stock_vec){
        auto asynFunc = async(std::launch::async, [this, stock, window_size, type]() { 
            // std::cout << "Starting Thread for stock pair: " << stock << std::endl;   
            return this->mean_reversion_strategy(stock, window_size, type);
         });
        futures.push_back(asynFunc);
    }

    for(int i{0}; i < futures.size(); i++){
        (*trade_result_vec).push_back(pair<PriceHistory,TradeSignal>{stock_vec[i],futures[i].get()});
    }

    return trade_result_vec;
}

TradeSignal TradingStrategy::mean_reversion_strategy(const PriceHistory &stock, const double &window_size, const MovingAverageType &type) {}

TradeSignal TradingStrategy::execute_scalping_strategy(vector<PriceHistory> &stocks, const double &window_size, const MovingAverageType &type, const int &duration) {}

vector<pair<pair<PriceHistory, PriceHistory>,TradeSignal>> * TradingStrategy::execute_pairs_trading_strategy(vector<pair<PriceHistory, PriceHistory>> &stock_pair_vec,const MovingAverageType &type) {
    vector<pair<pair<PriceHistory, PriceHistory>,TradeSignal>> * trade_result_vec = new vector<pair<pair<PriceHistory, PriceHistory>,TradeSignal>>();
    vector<future<TradeSignal>> futures;
    for(const pair<PriceHistory, PriceHistory> &stock:stock_pair_vec){
        auto asynFunc = async(std::launch::async, [this, stock,type]() {
            // std::cout << "Starting Thread for stock pair: " << stock << std::endl;
            return this->pairs_trading_strategy(stock,type);
         });
        futures.push_back(asynFunc);
    }
    
    for(int i{0}; i < futures.size();i++){
        (*trade_result_vec).push_back(pair<pair<PriceHistory, PriceHistory>,TradeSignal>{stock_pair_vec[i],futures[i].get()});
    }
    return trade_result_vec;
}

TradeSignal TradingStrategy::pairs_trading_strategy(const pair<PriceHistory, PriceHistory> &stock_pair,const MovingAverageType &type) {}

vector<pair<PriceHistory,TradeSignal>> * TradingStrategy::execute_bollinger_band_strategy( vector<PriceHistory> &stock_vec, const MovingAverageType &type,const double &window_size, const int &std) {
    vector<pair<PriceHistory,TradeSignal>> * trade_result_vec = new vector<pair<PriceHistory,TradeSignal>>();
    
    vector<future<TradeSignal>> futures;
    for(const PriceHistory &stock:stock_vec){
        auto asynFunc = async(std::launch::async, [this, stock,type,window_size,std]() { 
            // std::cout << "Starting Thread for stock pair: " << stock << std::endl;   
            return this->bollinger_band_strategy(stock,type,window_size,std);
         });
        futures.push_back(asynFunc);
    }

    for(int i{0}; i < futures.size(); i++){
        (*trade_result_vec).push_back(pair<PriceHistory,TradeSignal>{stock_vec[i],futures[i].get()});
    }
    
    return trade_result_vec; 
}

TradeSignal TradingStrategy::bollinger_band_strategy(const PriceHistory &stock, const MovingAverageType &type, const double &window_size, const int &std) {}