#include <iostream>
#include <sstream>
#include <stdexcept>
#include <ostream>
#include <unordered_map>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <utility>
#include <memory>
#include <cmath>

#include "include/analyzer.h"
#include "include/pricehistory.h"
#include "include/series.h"
#include "include/customhashes.h"

using std::vector;
using std::unordered_map;
using std::map;
using std::queue;
using std::pair;
using std::string;
using std::stringstream;
using std::unique_ptr;


Analyzer::Analyzer() : arbitrage_threshold(0), correlation_threshold(0){};

Analyzer::Analyzer(const double &arb_thresh) : arbitrage_threshold(arb_thresh), correlation_threshold(0){};

Analyzer::Analyzer(const double &arb, const double &corr) : arbitrage_threshold(arb), correlation_threshold(corr){};

Analyzer::Analyzer(const Analyzer &obj) : arbitrage_threshold(obj.get_arbitrage_threshold()), correlation_threshold(obj.get_correlation_threshold()){};

Analyzer &Analyzer::operator=(const Analyzer &obj)
{
    arbitrage_threshold = obj.get_arbitrage_threshold();
    correlation_threshold = obj.get_correlation_threshold();
    return *this;
}

Analyzer::~Analyzer(){};

double Analyzer::get_arbitrage_threshold() const { return arbitrage_threshold; }

double Analyzer::get_correlation_threshold() const { return correlation_threshold; }

void Analyzer::set_arbitrage_threshold(const double &arb) { arbitrage_threshold = arb; }

void Analyzer::set_correlation_threshold(const double &corr) { correlation_threshold = corr; }

// FIND A COMPUTATIONAL LIBRARY TO ADD TO THE ANALYZER
double Analyzer::generate_correlation_value(PriceHistory &stock1, PriceHistory &stock2)
{
}

double Analyzer::generate_percent_change(const double &new_price, const double &old_price)const{
    return ((new_price-old_price)/old_price) * 100.00;
}

double Analyzer::generate_std(const double &value, const double &mean, const int &size)const { return sqrt(pow(value - mean,2)/size);}

unique_ptr<unordered_map<pair<PriceHistory, PriceHistory>, double,PairPriceHistoryHash>> Analyzer::generate_correlation_map(const vector<pair<PriceHistory, PriceHistory>> &stock_pairs_list)
{   
    unordered_map<pair<PriceHistory, PriceHistory>, double,PairPriceHistoryHash> *map = new unordered_map<pair<PriceHistory, PriceHistory>, double,PairPriceHistoryHash>();
    for (pair<PriceHistory,PriceHistory> stock_pair : stock_pairs_list)
    {
        auto value = generate_correlation_value(stock_pair.first, stock_pair.second);
        (*map)[stock_pair] = value;
    }
    return unique_ptr<unordered_map<pair<PriceHistory, PriceHistory>, double,PairPriceHistoryHash>>(map);
}

unique_ptr<unordered_map<PriceHistory, unordered_map<PriceHistory, double,PriceHistoryHash>,PriceHistoryHash>> Analyzer::generate_correlation_map(const vector<PriceHistory> &stock_vec)
{
    unordered_map<PriceHistory, unordered_map<PriceHistory, double,PriceHistoryHash>,PriceHistoryHash> *corr_map = new unordered_map<PriceHistory, unordered_map<PriceHistory, double,PriceHistoryHash>,PriceHistoryHash>();
    for (int i = 0; i < stock_vec.size(); i++)
    {
        int j = i + 1;
        while (j++ != stock_vec.size() - 1)
        {
            PriceHistory s1 = stock_vec.at(i);
            PriceHistory s2 = stock_vec.at(j);
            auto value = generate_correlation_value(s1, s2);
            (*corr_map)[s1][s2] = value;
        }
    }
    return unique_ptr<unordered_map<PriceHistory, unordered_map<PriceHistory, double,PriceHistoryHash>,PriceHistoryHash>>(corr_map);
}

// vector<pair<PriceHistory::CandleStick,double>> * Analyzer::generate_dynamic_ema(const PriceHistory &stock, const double &window) const
// {
//     vector<pair<PriceHistory::CandleStick,double>> * ema = new vector<pair<PriceHistory::CandleStick,double>>();
//     vector<PriceHistory::CandleStick> candles = stock.get_candles();

//     if (window > candles.size())
//     {
//         cout << "There is not enough data to create a " << window << " day moving average" << endl;
//         return nullptr;
//     }

//     int start{0}, end{1}, endOfCandles{candles.size() - 1};
//     (*ema).at(0) = pair<PriceHistory::CandleStick,double>{candles.at(0),0.0};
//     while (end <= endOfCandles)
//     {
//         int counter{0};
//         double alpha{1.0 / window}, weight = 0;
//         double curr_ema{candles.at(start).close}, date{0};
//         while (counter <= window)
//         {
//             weight += alpha;
//             curr_ema = (candles.at(end).close * alpha) + (curr_ema * (1 - alpha));
//             if(counter != window) (*ema).push_back({candles.at(end),0.0});
//             end++;
//             counter++;
//         }

//         pair<double, double> dateAvgPair;
//         dateAvgPair.first = candles.at(end).close;
//         dateAvgPair.second = curr_ema;
//         (*ema)[candles.at(end).datetime] = dateAvgPair;

//         start++;
//         end = start + 1;
//         counter = 0;
//     }

//     return ema;
// }

// Calculate average standard deviation
unique_ptr<Series>  Analyzer::generate_ema(const PriceHistory &stock, const double &window) const
{
    vector<PriceHistory::CandleStick> candles = stock.get_candles();
    vector<MarketDataFrame> frames;
    int endOfCandles{candles.size() - 1};
    double alpha{2.0 / (window + 1.0)};
    long extended_trading_day{60*60*24*1000};
    long extended_trading_day{60*60*7*1000};

    /*
        We will start with a SMA for the first window and then calculate EMAs from then on.
    */
    double sum{candles.at(0).close};
    for(int i{1}; i < window; i++){
        sum+=candles.at(i).close;
        if(i < window -1){
            MarketDataFrame frame = MarketDataFrame(candles.at(i),0.0,generate_std(candles.at(i).close,0.0,candles.size()),0.0);
            frames.push_back(frame);
        }
    }

    MarketDataFrame frame = MarketDataFrame(candles.at(window-1),sum/window,generate_std(candles.at(window-1).close,sum/window,candles.size()),0.0);
    frames.push_back(frame);
    
    int lp = 0, rp = window-1;
    double curr_ema = sum/window;
    /*
        Once we have the initial window set, we will loop through the rest of the array
        following these two steps before taking the average:
        1. We subtract the start from the sum, then shift start once.
        2. We will shift the end up once, then add the new number.
        3. We will then get the average.
    */
    while (rp < endOfCandles)
    {
        sum-=candles.at(lp++).close;
        sum+=candles.at(++rp).close;
        curr_ema = (candles.at(rp).close*alpha) + (curr_ema *(1-alpha));
        MarketDataFrame frame = MarketDataFrame(candles.at(rp),curr_ema,generate_std(candles.at(rp).close,curr_ema,candles.size()),0.0);
        frames.push_back(frame);
    }

    return unique_ptr<Series>(new Series(frames));
}
// Calculate average standard deviation
unique_ptr<Series> Analyzer::generate_sma(const PriceHistory &stock, const double &window) const
{
    vector<PriceHistory::CandleStick> candles = stock.get_candles();
    vector<MarketDataFrame> frames; 

    /*
        We will loop through the window, calculate the average, and slide
        the start pointer up one spot and bring end pointer to start+1
        until we reach the end of the candle stack. We will handle other
        averages in another loop.
    */
    double sum{0};
    for(int i{0}; i < window;i++){
        if(i < window -1){
            double standard_deviation = generate_std(candles.at(i).close,0.0,candles.size());
            MarketDataFrame frame = MarketDataFrame(candles.at(i),0.0,standard_deviation,0.0);
            frames.push_back(frame);
        }
        sum += candles.at(i).close;
    }

    /*
        Creating a pair where first is the timestamp where the average is calculated to,
        and second is the average.
    */
    MarketDataFrame frame = MarketDataFrame(candles.at(window-1),sum,generate_std(candles.at(window-1).close,sum,candles.size()),0.0);
    frames.push_back(frame);

    /*
        Once we have the initial window set, we will loop through the rest of the array
        following these two steps before taking the average:
        1. We subtract the start from the sum, then shift start once.
        2. We will shift the end up once, then add the new number.
        3. We will then get the average.
    */
    int lp = 0, rp = window-1;
    while(rp < candles.size()-1){
        sum-=candles.at(lp++).close;
        sum+=candles.at(++rp).close;
        double mean = sum/window;
        double standard_deviation = generate_std(candles.at(rp).close,mean,candles.size());
        MarketDataFrame frame = MarketDataFrame(candles.at(rp),mean,standard_deviation,0.0);
        frames.push_back(frame);
    }

    return unique_ptr<Series>(new Series(frames));
}

unique_ptr<Series> Analyzer::generate_moving_average(PriceHistory &stock, double &window, MovingAverageType &type)
{
    if (type == MovingAverageType::EXPONENTIAL)
    {
        return generate_ema(stock, window);   
    }
    return generate_sma(stock, window);
}

unique_ptr<unordered_map<double, unique_ptr<Series>>> Analyzer::generate_moving_averages_map(PriceHistory &stock, vector<double> &windows,  MovingAverageType &type)
{
    unordered_map<double,unique_ptr<Series>> *map = new unordered_map<double,unique_ptr<Series>>();
    for (auto window : windows) (*map)[window] = generate_moving_average(stock, window, type);
    return unique_ptr<unordered_map<double,unique_ptr<Series>>>(map);
}

unique_ptr<unordered_map<string, unique_ptr<Series>>> Analyzer::generate_moving_averages_map(vector<PriceHistory> &stock_vec,  double &window, MovingAverageType &type)
{
    unordered_map<string,unique_ptr<Series>> *series_map = new unordered_map<string,unique_ptr<Series>>();
    for (PriceHistory stock : stock_vec)
    {
        (*series_map)[stock.get_ticker()] = generate_moving_average(stock, window, type);
    }
    return unique_ptr<unordered_map<string,unique_ptr<Series>>>(series_map);
}

// vector<map<string, vector<pair<PriceHistory::CandleStick,double>>*>*> * Analyzer::generate_moving_averages_map(vector<PriceHistory> &stock_vec,  vector<double> &windows, MovingAverageType &type)
// {
//     vector<map<string, vector<pair<PriceHistory::CandleStick,double>>*>*>* ma_map = new  vector<map<string, vector<pair<PriceHistory::CandleStick,double>>*>*>();
//     for (PriceHistory stock : stock_vec)
//     {
//         map<string, vector<pair<PriceHistory::CandleStick,double>>*>* inner_map = new map<string, vector<pair<PriceHistory::CandleStick,double>>*>*>();
//         for (auto window : windows)
//         {
//             auto ma_vec = generate_moving_average(stock, window, type);
//             (*inner_map)[window] = ma_vec;
//         }
//         (*ma_map).push_back(inner_map);
//     }
//     return ma_map;
// }

unique_ptr<string>  Analyzer::generate_stock_trend(const PriceHistory &stock, const double &short_term_window, const double &long_term_window, const MovingAverageType &type) const
{
    auto short_term_series = type == MovingAverageType::EXPONENTIAL ? generate_ema(stock, short_term_window) : generate_sma(stock,short_term_window);
    auto long_term_series =  type == MovingAverageType::EXPONENTIAL ? generate_ema(stock, long_term_window) : generate_sma(stock,long_term_window);
    vector<PriceHistory::CandleStick> candles = stock.get_candles();
    // Use Futures API to run parallel percent change functions for the
    // regular stock price, and the short & long term windows.

    auto short_term_frames_vec = short_term_series.get()->get();
    auto long_term_frames_vec = short_term_series.get()->get();
    bool short_term_trend = short_term_frames_vec.at(short_term_frames_vec.size()-1).get_candle().close > short_term_frames_vec.at(short_term_frames_vec.size()-1).get_mean();
    bool long_term_trend = long_term_frames_vec.at(long_term_frames_vec.size()-1).get_candle().close > long_term_frames_vec.at(long_term_frames_vec.size()-1).get_mean();


    stringstream long_term;
    stringstream short_term;
    stringstream message;

    if (long_term_trend)
    {
        long_term << "The long term trend for" << stock.get_ticker() << " is downard with by " << long_term_frames_vec.at(long_term_frames_vec.size()-1).get_standard_deviation() << "standard deviations.";
    }
    else
    {
        long_term << "The long term trend for" << stock.get_ticker() << " is upward with a percent change of " << long_term_frames_vec.at(long_term_frames_vec.size()-1).get_standard_deviation() << "standard deviations.";
    }

    if (short_term_trend)
    {
        short_term << "The long term trend for" << stock.get_ticker() << " is downard with a percent change of " << short_term_frames_vec.at(short_term_frames_vec.size()-1).get_standard_deviation() << "standard deviations.";
    }
    else
    {
        short_term << "The long term trend for" << stock.get_ticker() << " is upward with a percent change of " << short_term_frames_vec.at(short_term_frames_vec.size()-1).get_standard_deviation() << "standard deviations.";
    }

    message << long_term.str() << ". " << short_term.str();
    return unique_ptr<string>(new string(message.str())) ;
}

unique_ptr<unordered_map<string, unique_ptr<string>>> Analyzer::generate_stocks_trend_map(const vector<PriceHistory> &stock_vec, const double &short_term_window, const double &long_term_window, const MovingAverageType &type) const
{
    unordered_map<string, unique_ptr<string>> * momentum_map = new unordered_map<string, unique_ptr<string>>();
    for (PriceHistory stock : stock_vec)
    {
        (*momentum_map)[stock.get_ticker()] = generate_stock_trend(stock, short_term_window, long_term_window,type);
    }
    return  unique_ptr<unordered_map<string, unique_ptr<string>>>(momentum_map);
}