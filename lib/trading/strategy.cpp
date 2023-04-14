
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



Strategy::Strategy(Analyzer &a,double &strong_buy_percent,double &buy_percent,double &sell_percent,double &strong_sell_percent): analyzer(a), strong_buy_percent(strong_buy_percent),buy_percent(buy_percent), sell_percent(sell_percent), strong_sell_percent(strong_sell_percent){}

BackTester::BackTester(Analyzer &a,double &strong_buy_percent,double &buy_percent,double &sell_percent,double &strong_sell_percent) : Strategy(a,strong_buy_percent,buy_percent,sell_percent,strong_sell_percent){}

Trader::Trader(Analyzer &a,double &strong_buy_percent,double &buy_percent,double &sell_percent,double &strong_sell_percent) : Strategy(a,strong_buy_percent,buy_percent,sell_percent,strong_sell_percent) {}
//===================================================== PRIVATE METHODS ==================================================================//



//===================================================== PUBLIC METHODS ==================================================================//

void Trader::moving_average_strategy(vector<PriceHistory> &stockVec, double &window, MovingAverageType &type,vector<pair<PriceHistory,unique_ptr<TradeSignal>>> &signal_pair_vec)
{   
    vector<future<void>> futures;
    vector<unique_ptr<TradeSignal>> signals;
    for(PriceHistory stock:stockVec){
        unique_ptr<TradeSignal> signal(new TradeSignal(TradeSignal::HOLD));
        auto asynFunc = async(std::launch::async,[this,&stock,&window,&type,&signal_pair_vec,&signal](){
            this->moving_average_strategy(stock,window,type,signal);
            signal_pair_vec.push_back(pair<PriceHistory,unique_ptr<TradeSignal>>{stock,std::move(signal)});
        });
        futures.push_back(asynFunc);
        
    }
    for(int i{0}; i < futures.size(); i++) futures[i].wait();
}

void Trader::moving_average_strategy(PriceHistory &stock, double &window, MovingAverageType &type, unique_ptr<TradeSignal> &signal){    
    Series series(stock);
    TradeSignal *s = signal.get();
    Rolling * rolling = series.rolling(window).get();
    rolling->moving_average(type);
    rolling->standard_deviation();
    rolling->average_standard_deviation();
    vector<MarketDataFrame> * frames = series.get();
    /*
        For now, we will use 2.0 as the max deviation movemnets from the mean
        we will allow the close to be. However, we will come back to this and
        adjust parametes and add more analysis to pinpoint the perfect spot to
        trigger signals.
    */
    for(int i{0}; i < frames->size();i++){
        auto average = frames->at(i).get_mean();
        auto close = frames->at(i).get_candle().close;
        auto std = frames->at(i).get_standard_deviation();
        if(average != 0.0){
            if(close > average){
                if(std > 2.0){
                    *s = TradeSignal::HOLD;
                }else{
                    *s = TradeSignal::LONG;
                }
            }else if(close < average){
                if(std < 2.0){
                    *s = TradeSignal::HOLD;
                }
                *s = TradeSignal::SHORT;
            }else{
                *s = TradeSignal::HOLD;
            }
        }
    }
}

void Trader::mean_reversion_strategy(vector<PriceHistory> &stock_vec, const double &window_size, MovingAverageType &type,vector<pair<PriceHistory,unique_ptr<TradeSignal>>> &signal_pair_vec) {
    vector<future<void>> futures;
    for(PriceHistory &stock:stock_vec){
        unique_ptr<TradeSignal> signal(new TradeSignal(TradeSignal::HOLD));
        auto asynFunc = async(std::launch::async, [this, &stock, &window_size, &type,&signal_pair_vec,&signal]() { 
            // std::cout << "Starting Thread for stock pair: " << stock << std::endl; 

            this->mean_reversion_strategy(stock, window_size, type,signal);
            signal_pair_vec.push_back(pair<PriceHistory,unique_ptr<TradeSignal>>{stock,std::move(signal)});
        });
        futures.push_back(asynFunc);
    }

    for(int i{0}; i < futures.size(); i++) futures[i].wait();
}

void Trader::mean_reversion_strategy(PriceHistory &stock,  const double &window_size, MovingAverageType &type,unique_ptr<TradeSignal> &signal) {
    Series series(stock);
    TradeSignal *s = signal.get();
    Rolling *rolling = series.rolling(window_size).get();
    rolling->moving_average(type);
    rolling->standard_deviation();
    vector<MarketDataFrame> *frames = series.get();

    for(int i{0}; i < frames->size(); i++){
        auto average = frames->at(i).get_mean();
        auto close = frames->at(i).get_candle().close;
        auto std = frames->at(i).get_standard_deviation();

        /*
            Next we need to figure out how to calculate levels of support and resistance
            ,Fibonnaci Retracment, or the levels of deviation in order to signal when the
            stock is retracting back to the mean
        */
    }
}

void Trader::pairs_trading_strategy(vector<pair<PriceHistory, PriceHistory>> &stock_pair_vec,const MovingAverageType &type,vector<pair<pair<PriceHistory, PriceHistory>,unique_ptr<TradeSignal>>> &signal_pairs_vec) {

    vector<future<void>> futures;
    for(pair<PriceHistory, PriceHistory> &stock:stock_pair_vec){
        unique_ptr<TradeSignal> signal(new TradeSignal(TradeSignal::HOLD));
        auto asynFunc = async(std::launch::async, [this, &stock,&type,&signal,&signal_pairs_vec]() {
            // std::cout << "Starting Thread for stock pair: " << stock << std::endl;
            this->pairs_trading_strategy(stock,type,signal);
            signal_pairs_vec.push_back(pair<pair<PriceHistory,PriceHistory>,unique_ptr<TradeSignal>>{stock,std::move(signal)});

         });
        futures.push_back(asynFunc);
    }
    for(int i{0}; i < futures.size();i++) futures[i].wait();
}

void Trader::pairs_trading_strategy(pair<PriceHistory, PriceHistory> &stock_pair,const MovingAverageType &type,unique_ptr<TradeSignal> &signal) {}

void Trader::bollinger_band_strategy(vector<PriceHistory> &stock_vec, const MovingAverageType &type,const double &window_size, const int &std,vector<pair<PriceHistory,unique_ptr<TradeSignal>>> &signal_pairs_vec) {

    vector<future<void>> futures;
    for(PriceHistory &stock:stock_vec){
        unique_ptr<TradeSignal> signal(new TradeSignal(TradeSignal::HOLD));
        auto asynFunc = async(std::launch::async, [this, &stock,&type,&window_size,std,&signal,&signal_pairs_vec]() { 
            // std::cout << "Starting Thread for stock pair: " << stock << std::endl;   
            this->bollinger_band_strategy(stock,type,window_size,std,signal);
            signal_pairs_vec.push_back(pair<PriceHistory,unique_ptr<TradeSignal>>{stock,std::move(signal)});
        });
        futures.push_back(asynFunc);
    }
    for(int i{0}; i < futures.size(); i++) futures[i].wait();
    
}

void Trader::bollinger_band_strategy(PriceHistory &stock, const MovingAverageType &type, const double &window_size, const int &std,unique_ptr<TradeSignal> &signal) {}

void Trader::arbitrage_strategy(Portfolio &portfolio, vector<PriceHistory> &stocks, unique_ptr<TradeSignal> &signal) {}

void Trader::scalping_strategy(vector<PriceHistory> &stocks, const double &window_size, const MovingAverageType &type, vector<pair<PriceHistory,unique_ptr<TradeSignal>>> &signal_pair_vec) {}