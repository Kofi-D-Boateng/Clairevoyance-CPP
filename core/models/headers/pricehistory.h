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
#include <map>

using std::map;
using std::string;

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
private:
    /*
        The ticker symbol associated with the given history
    */
    string ticker;
    /*
        A Map containing the open,close,high,low, and adjusted volume
        of a stock. The outer mapping key will be a some sort of time
        series to keep the inner maps in order from latest time slot,
        to earliest.
    */
    map<double, map<string, double>> stock_data;
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
    PriceHistory(const string &ticker, const map<double, map<string, double>> &info, const PeriodType &period_type);

    // Copy Constructor
    PriceHistory(const PriceHistory &obj);

    // Copy Assignment
    PriceHistory &operator=(const PriceHistory &obj);

    // Destructor
    ~PriceHistory();

    //============================================== PUBLIC METHODS ========================================//

    string get_ticker() const;

    map<double, map<string, double>> get_stock_data() const;

    PeriodType get_period_type() const;

    void set_ticker(const string &ticker);

    void set_stock_data(const map<double, map<string, double>> &stock_data);

    void set_period_type(const PeriodType &period_type);
};