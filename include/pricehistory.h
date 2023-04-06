/**
 * @file Strategy.h
 * @author Kofi Boateng
 * @date 2023-01-05
 */

#pragma once

#include <iostream>
#include <stdexcept>
#include <ostream>
#include <string>
#include <vector>

using std::string;
using std::vector;


enum class AssetType{
    STOCK,
    BOND,
    FOREX,
    CRYPTO,
    ETF
};

enum class IntervalType
{
    SECOND,
    MINUTE,
    DAY,
    WEEK,
    MONTH,
    QUARTER,
    YEAR,
    YTD
};

enum class Interval{
    NONE,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    TEN,
    FIFTEN,
    TWENTY,
    THIRTY
};

enum class Range{
    NONE,
    DAY,
    WEEK,
    MONTH,
    YEAR
};

/**
 * @class PriceHistory
 * @author Kofi Boateng
 * @details A class that represent a Time Series for a ticker.
 */
class PriceHistory
{
public:
    class CandleStick
    {
    public:
        double datetime;
        double open;
        double close;
        double high;
        double low;
        double volume;

        CandleStick();
        CandleStick(const double &datetime, const double &open, const double &close, const double &high, const double &low, const double &volume);
    };

private:
    /*
        The type of asset the Time Series represents
    */
    AssetType asset_type;
    /*
        The ticker symbol associated with the given history
    */
    string ticker;
    /*
        A vector of candles
    */
    vector<CandleStick> candles;
    /*
        The range for which an interval is stretched
        Interval types include: Second, Minute, Hour, Day, etc.
    */
    IntervalType interval_type;

    /*
        The frequency of the time series
        Intervals include, but not limited to: One, Two, Three, Four, Ten, etc
    */
    Interval interval;

    /*
        The range represents the type of chart the stock data is modeled after.
        For example, if the data is from a 2 day chart, the range will be DAY.
        NONE is used only when the Time Series is a customized length.
    */
    Range range;

    /*
        The allotted amount of time the Time Series is supposed to represent.
        For example, if the Time Series is from a 5 day chart. Then the
        range_interval = FIVE, and range = DAY 
    */
    Interval range_interval;
    

public:
    // Constructor
    PriceHistory();
    PriceHistory(const AssetType &aseet_type, const string &ticker, const vector<CandleStick> &candles, const int &period, const IntervalType &interval_type, const Interval &interval, const Range &range, const Interval &range_interval);

    // Copy Constructor
    PriceHistory(const PriceHistory &obj);

    // Copy Assignment
    PriceHistory &operator=(const PriceHistory &obj);

    // Destructor
    ~PriceHistory();

    //============================================== PUBLIC METHODS ========================================//

    AssetType get_asset_type()const;

    string get_ticker() const;

    vector<CandleStick> get_candles() const;

    IntervalType get_interval_type() const;

    Interval get_interval() const;

    Range get_range()const;

    Interval get_range_interval()const;

    void set_asset_type(const AssetType &asset_type);

    void set_ticker(const string &ticker);

    void set_candles(const vector<CandleStick> &stock_data);

    void set_interval_type(const IntervalType &interval_type);

    void set_interval(const Interval &interval);

    void set_range(const Range &range);

    void set_range_interval(const Interval &interval);
};