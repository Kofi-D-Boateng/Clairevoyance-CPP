/**
 * @file Analyzer
 * @author Kofi Boateng
 * @date 2023-01-11
 *
 */

#pragma once

#include <iostream>
#include <stdexcept>
#include <ostream>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <tuple>
#include "pricehistory.h"

using std::vector;
using std::string;
using std::pair;
using std::map;
using std::tuple;
using std::cout;
using std::endl;


enum class MovingAverageType
{
    SIMPLE,
    EXPONENTIAL
};

enum class TrendType{
    UP,
    DOWN,
    NEUTRAL
};

class Analyzer
{
private:
    /*
        The arbitrage threshold you want the analyzer to act on when
        calculating for arbitrage opportunities.
    */
    double arbitrage_threshold;
    /*
        The correlation threshold you want the analyzer to use
        when making correlation calculations.
    */
    double correlation_threshold;

    /*
        Helper function that is called when the user wants to generate
        an exponential moving average. The number of observations will
        stay constant, however the weights will still reflect stronger
        in recent prices as the previous close EMA is taken into account
        in the formula. (See below)

        Formula: EMA(t) = Closing Price * alpha(multiplier) + EMA(t-1) * (1-alpha)
        Alpha: alpha = 2 / (n+1) [n = number of observations (window)]
        t: time in respect to previous closing price based on data given
    */
    vector<pair<PriceHistory::CandleStick,double>> * generate_ema(const PriceHistory &stock, const double &window) const;

    /*
        Helper function that is called when the user wants to generate
        an exponential moving average. This function performs an
        adaptive moving average, where the alpha term in the formula
        (see below) is dynamically changing, in terms of observations,
        to reflect stronger weights in recent prices.

        Formula: EMA(t) = Closing Price * alpha(multiplier) + EMA(t-1) * (1-alpha)
        Alpha: alpha = 2 / (n+1) [n = number of observations (window)]
        t: time in respect to previous closing price based on data given
    */
    // vector<pair<PriceHistory::CandleStick, double>> * generate_dynamic_ema(const PriceHistory &stock, const double &window) const;
    /*
        Helper function that is called when the user wants to generate
        a simple moving average. The weight of each average will be equal
        across all calculations.
    */
    vector<pair<PriceHistory::CandleStick, double>> * generate_sma(const PriceHistory &stock, const double &window) const;

public:
    Analyzer();
    Analyzer(const double &arbitrage_thresh);
    Analyzer(const double &arbitrage_thresh, const double &correlation_threshold);
    Analyzer(const Analyzer &obj);
    Analyzer &operator=(const Analyzer &obj);
    ~Analyzer();

    //================================ GETTERS & SETTERS ====================================//

    double get_arbitrage_threshold() const;

    void set_arbitrage_threshold(const double &arb_thresh);

    double get_correlation_threshold() const;

    void set_correlation_threshold(const double &corr_thresh);

    //=============================== OTHER METHODS =========================================//

    bool is_arbitrage_present(tuple<PriceHistory> &stock_tuple);

    /*
        Takes in two prices and calculates the derivative, or rate of change between 
        the prices
    */
    double generate_percent_change(const double &new_price,const double &old_price) const;

    /*
        Generates the standard deviation of a set of data
        @param double value - The value to be subtracted from the mean
        @param double mean  - The mean of the data set
        @param double size  - The size of the data set

        @return double std  - The standard deviation from the mean
    */
    double generate_std(double &value, double &mean, const int &size);

    /*
        Takes in a pair of stocks and returns a correlation value between the two stocks.
    */
    double generate_correlation_value(PriceHistory &stock1, PriceHistory &stock2);

    /*
        Takes in a vector of pairs and will return an unordered map of the pairs as the
        key and the mapped value will be the correlation between the pair of stocks
    */
    map<pair<PriceHistory, PriceHistory>, double> * generate_correlation_map(const vector<pair<PriceHistory, PriceHistory>> &stock_pairs);

    /*
        Takes in a tuple of pairs and will return an unordered map with a stock as
        the key and the mapped value will mapping with a stock and its correlation
        to the the stock we are currently iterating over in the tuple.

        The map will return a step mapping. The first map will will have all the
        stocks and their correlation to the first stock. As we move down the vector,
        we will add in n-1 stocks. The mapping will resemble something similar to this

        mapping = [
            s1: {s2:double, s3:double, s4:double},
            s2: {s3:double, s4:double},
            s3: {s4:double}
        ]
    */
    map<PriceHistory, map<PriceHistory, double>> * generate_correlation_map(const vector<PriceHistory> &stock_vec);

    /*
        Takes in a stock and a window, and will return the simple moving average of the
        stock based on the window designated.
    */
    vector<pair<PriceHistory::CandleStick, double>> * generate_moving_average( PriceHistory &stock,  double &window, MovingAverageType &type);

    /*
        Takes in a single stock or a vector of stocks and window or
        vector of windows and returns an unorder map with the key
        being a stock and the value being a ordered map with the
        key being a window and the values being a vector of either
        a simple moving average or exponential moving average.
    */
    map<double,vector<pair<PriceHistory::CandleStick, double>>*> * generate_moving_averages_map( PriceHistory &stock,  vector<double> &windows, MovingAverageType &type);

    /*
        Takes in a single stock or a vector of stocks and window or
        vector of windows and returns an unorder map with the key
        being a stock and the value being a ordered map with the
        key being a window and the values being a vector of either
        a simple moving average or exponential moving average.
    */
    vector<map<string, vector<pair<PriceHistory::CandleStick,double>>*>*> * generate_moving_averages_map(vector<PriceHistory> &stock_vec, double &window, MovingAverageType &type);

    /*
        Takes in a single stock or a vector of stocks and window or
        vector of windows and returns an unorder map with the key
        being a stock and the value being a ordered map with the
        key being a window and the values being a vector of either
        a simple moving average or exponential moving average.
    */
    // vector<map<string, vector<pair<PriceHistory::CandleStick,double>>*>*> * generate_moving_averages_map(vector<PriceHistory> &stock_vec, vector<double> &window, MovingAverageType &type);

    /*
        Takes in a stock and two windows, a long term moving average window,
        and a short term moving average window, and print a string to the
        screen regarding the short term and long term trend of the stock
    */
    string * generate_stock_trend(const PriceHistory &stock, const double &short_term_window, const double &long_term_window) const;

    /*
        Takes in a vector of stocks and two windows, a long term moving average window,
        and a short term moving average window, and print a string to the
        screen regarding the short term and long term trend of the stock
    */
    map<PriceHistory, string*> * generate_stocks_trend_map(const vector<PriceHistory> &stock_vec, const double &short_term_window, const double &long_term_window) const;
};