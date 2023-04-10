
#include <memory>
#include <vector>
#include "include/series.h"
#include "include/pricehistory.h"
#include "include/analyzer.h"

using std::vector;
using std::unique_ptr;
using std::make_unique;

MarketDataFrame::MarketDataFrame(const PriceHistory::CandleStick &candle, const double &mean,const double &std,const double &avg_std) : Serializable(), candle(candle), mean(mean), standard_deviation(std), average_standard_deviation(avg_std){}

MarketDataFrame::MarketDataFrame(PriceHistory::CandleStick &candle): Serializable(), candle(candle), mean(0.0), standard_deviation(0.0), average_standard_deviation(0.0){}

MarketDataFrame::~MarketDataFrame(){};

PriceHistory::CandleStick MarketDataFrame::get_candle()const { return candle;}

double MarketDataFrame::get_mean()const {return mean;}

double MarketDataFrame::get_standard_deviation()const {return standard_deviation;}

double MarketDataFrame::get_average_standard_deviation()const {return average_standard_deviation;}

Series::Series(vector<MarketDataFrame> &series): Serializable(),time_series(&series){}

Series::Series(PriceHistory &history): Serializable(){
    auto candles = history.get_candles();
    auto frames_vec = make_unique<std::vector<MarketDataFrame>>();
    for(PriceHistory::CandleStick stick:candles){
        MarketDataFrame frame(stick);
        frames_vec->push_back(frame);
    }
    time_series = std::move(frames_vec);
}

Series::~Series(){}

vector<MarketDataFrame> * Series::get(){return time_series.get();}


Rolling::Rolling(Series &ref, double &window): Serializable(), series_ref(ref), window(window){}

Rolling::~Rolling(){}

Series& Rolling::standard_deviation(){}

Series& Rolling::average_standard_deviation(){}

Series& Rolling::moving_average(MovingAverageType &type){
    Analyzer analyzer(0.0,0.0);
    auto t = series_ref.get();

    return series_ref;
}