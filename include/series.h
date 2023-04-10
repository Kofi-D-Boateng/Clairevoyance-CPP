/**
 * @file Series
 * @author Kofi Boateng
 * @date 2023-04-04
*/

#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "include/pricehistory.h"
#include "include/serializable.h"

using std::vector;
using std::unique_ptr;

/*
    The MarketDataFrame class mimics a single point in time of a time series. 
*/
class MarketDataFrame : Serializable{
    private:
        /*
            A Candle stick backed by the PriceHistory Class
        */
        PriceHistory::CandleStick candle;
        /*
            The current average up to the current candle.
        */
        double mean;
        /*
            The standard deviation of the candle stick.
        */
        double standard_deviation;
        /*
            The current average standard of the standard deviation.
        */
       double average_standard_deviation;

    public:
        MarketDataFrame(const PriceHistory::CandleStick &candle, const double &mean,const double &std,const double &avg_std);
        MarketDataFrame(PriceHistory::CandleStick &candle);
        ~MarketDataFrame();
        /*
            @return CandleStick cnalde - candle stick backed by the CandleStick class
        */
        PriceHistory::CandleStick get_candle()const;
        /*
            @return double mean
        */
        double get_mean() const;
        /*
            @return double standard deviation
        */
        double get_standard_deviation() const;
        /*
            @return double average standard deviation
        */
        double get_average_standard_deviation()const;

};

class Rolling : Serializable {

    private:
        Series& series_ref;
        double &window;
    public:
        Rolling(Series &ref, double &window);
        
        ~Rolling();
        
        Series& moving_average(MovingAverageType &type);

        Series& standard_deviation();

        Series& average_standard_deviation();

};


/*
    The Series class is a wrapper class backed by a vector that will
    hold a post processed collection of market data. This data can
    be used to create different trading algorithms. The MarketDataFrame
    class is subjected to change as well as the Series.
*/
class Series : Serializable{
    private:
        /*
            A post-processed time series of data that can be used for
            creating algorithmic trading
        */
        unique_ptr<vector<MarketDataFrame>> time_series;
    public:
        Series(vector<MarketDataFrame> &series);
        Series(PriceHistory &history);
        ~Series();
        /*
            @return vector<MarketDataFrame> * frames --> a pointer to the wrapped time_series vector of market data
        */
        vector<MarketDataFrame> * get();

        /*
            @param double window --> window to be set for the rolling object
            @return Rolling rolling object --> returns a reference to the Rolling Class (similar to Python)
        */
        Rolling& rolling(const double& window);
        
};