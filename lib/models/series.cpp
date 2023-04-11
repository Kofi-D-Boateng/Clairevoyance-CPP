
#include <memory>
#include <vector>
#include "include/series.h"
#include "include/pricehistory.h"
#include "include/analyzer.h"
#include "include/enums.h"

using std::vector;
using std::unique_ptr;
using std::make_unique;

MarketDataFrame::MarketDataFrame(const PriceHistory::CandleStick &candle, const double &mean,const double &std,const double &avg_std) : Serializable("MarketDataFrame"), candle(candle), mean(mean), standard_deviation(std), average_standard_deviation(avg_std){}

MarketDataFrame::MarketDataFrame(PriceHistory::CandleStick &candle): Serializable("MarketDataFrame"), candle(candle), mean(0.0), standard_deviation(0.0), average_standard_deviation(0.0){}

MarketDataFrame::~MarketDataFrame(){};

PriceHistory::CandleStick MarketDataFrame::get_candle()const { return candle;}

double MarketDataFrame::get_mean()const {return mean;}

double MarketDataFrame::get_standard_deviation()const {return standard_deviation;}

double MarketDataFrame::get_average_standard_deviation()const {return average_standard_deviation;}

Rolling::Rolling(Series &origin, const double& window): Serializable("Rolling"),original_series(origin),window(window){}

Rolling::~Rolling(){}

void Rolling::standard_deviation(){
    // CALCULATE STD
    vector<MarketDataFrame> * t = original_series.get();
    std::move(original_series);
}

void Rolling::average_standard_deviation(){
    // CALCULATE AVERAGE STD
    vector<MarketDataFrame> * t = original_series.get();
}

void Rolling::moving_average(MovingAverageType &type){
    // WE WORK ANALYZER/HOW TO CALCULATE MOVING AVERAGE
    Analyzer analyzer(0.0,0.0);
    vector<MarketDataFrame> * t = original_series.get();
}



Series::Series(vector<MarketDataFrame> &series,IntervalType &interval_type, Interval &interval): Serializable("Series"),time_series(&series),interval_type(interval_type),interval(interval){}

Series::Series(PriceHistory &history): Serializable("Series"){
    auto candles = history.get_candles();
    auto frames_vec = make_unique<std::vector<MarketDataFrame>>();
    for(PriceHistory::CandleStick stick:candles){
        MarketDataFrame frame(stick);
        frames_vec->push_back(frame);
    }
    time_series = std::move(frames_vec);
    interval = history.get_interval();
    interval_type = history.get_interval_type();
}

Series::~Series(){}

unique_ptr<Rolling> Series::rolling(const double &window){
    return unique_ptr<Rolling>(new Rolling(*this,window));
}

vector<MarketDataFrame> * Series::get(){return time_series.get();}