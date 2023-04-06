#include <vector>
#include "include/series.h"
#include "include/pricehistory.h"

using std::vector;

MarketDataFrame::MarketDataFrame(const PriceHistory::CandleStick &candle, const double &mean,const double &std,const double &avg_std) : candle(candle), mean(mean), standard_deviation(std), average_standard_deviation(avg_std){}

MarketDataFrame::~MarketDataFrame(){};

PriceHistory::CandleStick MarketDataFrame::get_candle()const { return candle;}

double MarketDataFrame::get_mean()const {return mean;}

double MarketDataFrame::get_standard_deviation()const {return standard_deviation;}

double MarketDataFrame::get_average_standard_deviation()const {return average_standard_deviation;}

Series::Series(const vector<MarketDataFrame> &series): time_series(series){}

Series::~Series(){}

vector<MarketDataFrame> Series::get()const {return time_series;}