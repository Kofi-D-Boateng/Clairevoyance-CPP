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
#include "include/enums.h"

using std::vector;
using std::unique_ptr;
using std::shared_ptr;

/*
    The MarketDataFrame class mimics a single point in time of a time series. 
*/
class MarketDataFrame : public Serializable{
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

class Rolling : public Serializable {

    private:
        Series &original_series;
        const double &window;
    public:
        Rolling(Series &series_ptr, const double &window);
        
        ~Rolling();
        /*
            @param MovingAverageType type: The type of moving average to calculate
            @return unique_ptr<Series> original_series: This will return the original series object that called the rolling method

        */
        void moving_average(MovingAverageType &type);
        /*
            @return unique_ptr<Series> original_series: This will return the original series object that called the rolling method

        */
        void standard_deviation();
        /*
            @return unique_ptr<Series> original_series: This will return the original series object that called the rolling method

        */
        void average_standard_deviation();

};


/*
    The Series class is a wrapper class backed by a vector that will
    hold a post processed collection of market data. This data can
    be used to create different trading algorithms. The MarketDataFrame
    class is subjected to change as well as the Series.
*/
class Series : public Serializable{
    private:
        /*
            A post-processed time series of data that can be used for
            creating algorithmic trading
        */
        unique_ptr<vector<MarketDataFrame>> time_series;

        /*
            The type of interval that the series will match,
            which is inheritied from the PriceHistory class
            for which the Series is built upon
        */
        IntervalType interval_type;
        /*
            The interval amount that the series will match,
            which is inheritied from the PriceHistory class
            for which the Series is built upon
        */
        Interval interval;
    public:
        Series(vector<MarketDataFrame> &series, IntervalType &interval_type, Interval &interval);
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
        unique_ptr<Rolling> rolling(const double& window);
        
};