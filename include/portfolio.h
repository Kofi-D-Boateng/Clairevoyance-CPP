/**
 * @file Strategy.h
 * @author Kofi Boateng
 * @date 2023-01-05
 */

#pragma once

#include <iostream>
#include <stdexcept>
#include <ostream>
#include <unordered_map>
#include <string>
using std::string;
using std::unordered_map;

class Portfolio
{

private:
    double current_capital;
    double total_port_capital;
    unordered_map<string, unordered_map<string, double>> holdings;
    double percent_of_funds_available;

public:
    // Constructor
    Portfolio(const double &current_capital, const double &total_capital, const unordered_map<string, unordered_map<string, double>> &holdings, const double &perc);

    // Copy Constructor
    Portfolio(const Portfolio &obj);

    // Copy Assignment
    Portfolio &operator=(const Portfolio &obj);

    // Deconstructor
    ~Portfolio();

    // ======================================PUBLIC METHODS====================================================================

    double get_current_capital();

    double get_total_capital();

    unordered_map<string, unordered_map<string, double>> get_holdings();

    void set_current_capital(const double &current_capital);

    void set_total_capital(const double &total_capital);

    void set_holdings(const unordered_map<string, unordered_map<string, double>> &holdings);
};