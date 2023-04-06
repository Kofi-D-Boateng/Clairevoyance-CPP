
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
#include "include/series.h"

using std::map;
using std::vector;
using std::pair;
using std::unique_ptr;
using std::queue;
using std::stack;
using std::greater;
using std::less;
using std::future;
using std::async;


TradingStrategy::TradingStrategy(Analyzer &a,double &strong_buy_percent,double &buy_percent,double &sell_percent,double &strong_sell_percent) : analyzer(a), strong_buy_percent(strong_buy_percent),buy_percent(buy_percent), sell_percent(sell_percent), strong_sell_percent(strong_sell_percent) {}
//===================================================== PRIVATE METHODS ==================================================================//

//===================================================== PUBLIC METHODS ==================================================================//

unique_ptr<vector<pair<PriceHistory,TradeSignal>>> TradingStrategy::execute_moving_average_strategy(vector<PriceHistory> &stockVec, double &window, MovingAverageType &type)
{   
    unique_ptr<vector<pair<PriceHistory,TradeSignal>>> trade_result_vec;
    auto vec = trade_result_vec.get();
    for(PriceHistory stock:stockVec){
        auto result = execute_moving_average_strategy(stock,window,type);
        vec->push_back(pair<PriceHistory,TradeSignal>{stock,result});
    }
    return trade_result_vec;    
}

// FINISH THIS METHOD UP
// SET UP TRADE ALERTS WHEN THERE IS NO AVERAGE YET.
TradeSignal TradingStrategy::execute_moving_average_strategy(PriceHistory &stock, double &window, MovingAverageType &type){    
    unique_ptr<Series> series_ptr(this->analyzer.generate_moving_average(stock,window,type));
    TradeSignal signal = TradeSignal::HOLD;
    queue<double> stock_volume;
    double volume_average{0.0};
    
    vector<MarketDataFrame> frames = series_ptr.get()->get();
    for(int i{0}; i < frames.size();i++){
        auto average = frames[i].get_mean();
        auto close = frames[i].get_candle().close;
        auto standard_dev = frames[i].get_standard_deviation();
        auto avg_standard_dev = frames[i].get_average_standard_deviation();
        if(average != 0.0){
            if(close > average){
                if(standard_dev != 0.0 && avg_standard_dev !=0.0){
                    
                }
            }
        }
    }

    return signal;
}

TradeSignal TradingStrategy::execute_arbitrage_strategy(Portfolio &port, vector<PriceHistory> &stockVec) {}

unique_ptr<vector<pair<PriceHistory,TradeSignal>>> TradingStrategy::execute_mean_reversion_strategy(vector<PriceHistory> &stock_vec, const double &window_size, const MovingAverageType &type) {
    unique_ptr<vector<pair<PriceHistory,TradeSignal>>>  trade_result_vec;
    vector<future<TradeSignal>> futures;
    for(const PriceHistory &stock:stock_vec){
        auto asynFunc = async(std::launch::async, [this, stock, window_size, type]() { 
            // std::cout << "Starting Thread for stock pair: " << stock << std::endl;   
            return this->mean_reversion_strategy(stock, window_size, type);
         });
        futures.push_back(asynFunc);
    }
    auto vec = trade_result_vec.get();
    for(int i{0}; i < futures.size(); i++){
        (*vec).push_back(pair<PriceHistory,TradeSignal>{stock_vec[i],futures[i].get()});
    }

    return trade_result_vec;
}

TradeSignal TradingStrategy::mean_reversion_strategy(const PriceHistory &stock, const double &window_size, const MovingAverageType &type) {}

TradeSignal TradingStrategy::execute_scalping_strategy(vector<PriceHistory> &stocks, const double &window_size, const MovingAverageType &type, const int &duration) {}

unique_ptr<vector<pair<pair<PriceHistory, PriceHistory>,TradeSignal>>> TradingStrategy::execute_pairs_trading_strategy(vector<pair<PriceHistory, PriceHistory>> &stock_pair_vec,const MovingAverageType &type) {
    unique_ptr<vector<pair<pair<PriceHistory, PriceHistory>,TradeSignal>>> trade_result_vec;
    vector<future<TradeSignal>> futures;
    for(const pair<PriceHistory, PriceHistory> &stock:stock_pair_vec){
        auto asynFunc = async(std::launch::async, [this, stock,type]() {
            // std::cout << "Starting Thread for stock pair: " << stock << std::endl;
            return this->pairs_trading_strategy(stock,type);
         });
        futures.push_back(asynFunc);
    }
    auto vec = trade_result_vec.get();
    for(int i{0}; i < futures.size();i++){
        vec->push_back(pair<pair<PriceHistory, PriceHistory>,TradeSignal>{stock_pair_vec[i],futures[i].get()});
    }
    return trade_result_vec;
}

TradeSignal TradingStrategy::pairs_trading_strategy(const pair<PriceHistory, PriceHistory> &stock_pair,const MovingAverageType &type) {}

unique_ptr<vector<pair<PriceHistory,TradeSignal>>> TradingStrategy::execute_bollinger_band_strategy(vector<PriceHistory> &stock_vec, const MovingAverageType &type,const double &window_size, const int &std) {
    unique_ptr<vector<pair<PriceHistory,TradeSignal>>> trade_result_vec;
    
    vector<future<TradeSignal>> futures;
    for(const PriceHistory &stock:stock_vec){
        auto asynFunc = async(std::launch::async, [this, stock,type,window_size,std]() { 
            // std::cout << "Starting Thread for stock pair: " << stock << std::endl;   
            return this->bollinger_band_strategy(stock,type,window_size,std);
         });
        futures.push_back(asynFunc);
    }
    auto vec = trade_result_vec.get();
    for(int i{0}; i < futures.size(); i++){
        vec->push_back(pair<PriceHistory,TradeSignal>{stock_vec[i],futures[i].get()});
    }
    
    return trade_result_vec; 
}

TradeSignal TradingStrategy::bollinger_band_strategy(const PriceHistory &stock, const MovingAverageType &type, const double &window_size, const int &std) {}