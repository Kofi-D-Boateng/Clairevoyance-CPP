/**
 * @file Series
 * @author Kofi Boateng
 * @date 2023-04-04
*/

#pragma once

#include <iostream>
#include <vector>
#include <pricehistory.h>

using std::vector;

/*
    The MarketDataFrame class mimics a single point in time of a time series. 
*/
class MarketDataFrame{
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


/*
    The Series class is a wrapper class backed by a vector that will
    hold a post processed collection of market data. This data can
    be used to create different trading algorithms. The MarketDataFrame
    class is subjected to change as well as the Series.
*/
class Series{
    private:
        /*
            A post-processed time series of data that can be used for
            creating algorithmic trading
        */
        vector<MarketDataFrame> time_series;
    public:
        Series(const vector<MarketDataFrame> &series);
        ~Series();
        Series get()const;
};