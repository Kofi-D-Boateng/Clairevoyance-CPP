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

class PriceHistory
{

private:
    // The ticker symbol associated with the given history
    string ticker;

    // A Map containing the open,close,high,low, and adjusted volume
    // of a stock.
    // The outer mapping key will be a some sort of time series to
    // keep the inner maps in order from latest time slot, to earliest.
    map<double, map<string, double>> ticker_info;

public:
    // Constructor
    PriceHistory();
    PriceHistory(const string &ticker, const map<double, map<string, double>> &info);

    // Copy Constructor
    PriceHistory(const PriceHistory &obj);

    // Copy Assignment
    PriceHistory &operator=(const PriceHistory &obj);

    // Destructor
    ~PriceHistory();

    //============================================== PUBLIC METHODS ========================================//

    string get_ticker() const;

    map<double, map<string, double>> get_ticker_info() const;

    void set_ticker(const string &ticker);

    void set_ticker_info(const map<double, map<string, double>> &ticker_info);
};