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

enum class PeriodType
{
    DAY,
    MONTH,
    YEAR,
    YTD
};

enum class FrequencyType
{
    MINUTE,
    DAILY,
    WEEKLY,
    MONTHLY
};

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
        The ticker symbol associated with the given history
    */
    string ticker;
    /*
        A vector of candles
    */
    vector<CandleStick> candles;
    /*
        The period of time for which the stock data was pulled from.
        (i.e. 2 day or 3 month).

        Valid Period numbers range as follow (asterisks mark defaults)
        day: 1* to 5 or 10
        month: 1-11
        year: 1*-20
        ytd: 1*

        These values should match according to the type of data and periodType
        you have chosen.

    */
    int period;
    /*
        The period for which the stock data is taken from.
        The periods within the enum are DAY,MONTH,YEAR,YTD
        (Year to date). These flags represent the type of
        charting style the data was pulled as (i.e. 2-DAY chart)

        If using a price history that was generated with timestamps,
        set period to 0.
    */
    PeriodType periodType;
    /*
        The frequency of the stock data.
        The frequency should match with the alloted amount of time
        each Time Series data point was taken from. These are the
        valid frequencies (asterisk marks defaults)

        minute: 1*, 5, 10, 15, 30
        daily: 1*
        weekly: 1*
        monthly: 1*
    */
    int frequency;

    FrequencyType frequencyType;

public:
    // Constructor
    PriceHistory();
    PriceHistory(const string &ticker, const vector<CandleStick> &candles, const int &period, const PeriodType &period_type, const FrequencyType &freq_type, const int &frequency);

    // Copy Constructor
    PriceHistory(const PriceHistory &obj);

    // Copy Assignment
    PriceHistory &operator=(const PriceHistory &obj);

    // Destructor
    ~PriceHistory();

    //============================================== PUBLIC METHODS ========================================//

    string get_ticker() const;

    vector<CandleStick> get_candles() const;

    PeriodType get_period_type() const;

    FrequencyType get_frequecy_type() const;

    int get_period() const;

    int get_frequency() const;

    void set_ticker(const string &ticker);

    void set_candles(const vector<CandleStick> &stock_data);

    void set_period(const int &period);

    void set_period_type(const PeriodType &period_type);

    void set_frequency_type(const FrequencyType &freq_type);

    void set_frequency(const int &freq);
};