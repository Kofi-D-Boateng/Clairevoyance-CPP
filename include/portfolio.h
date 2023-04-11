/**
 * @file Strategy.h
 * @author Kofi Boateng
 * @date 2023-01-05
 */

#pragma once

#include <iostream>
#include <stdexcept>
#include <ostream>
#include <map>
#include <utility>
#include <string>
#include "include/serializable.h"
using std::string;
using std::pair;

class Portfolio : public Serializable
{

private:
    double current_capital;
    double total_port_capital;
    map<string, pair<string, double>> holdings;
    double max_exposure_allowed;
    double stop_loss;
    double limit_order;

public:
    // Constructor
    Portfolio(const double &current_capital, const double &total_capital, const map<string, pair<string, double>> &holdings, const double &mea,const double& stop_loss, const double &limit_order);

    // Copy Constructor
    Portfolio(const Portfolio &obj);

    // Copy Assignment
    Portfolio &operator=(const Portfolio &obj);

    // Deconstructor
    ~Portfolio();

    // ======================================PUBLIC METHODS====================================================================

    double get_current_capital();

    double get_total_capital();

    map<string, pair<string, double>> get_holdings();

    double get_max_exposure_allowed() const;

    double get_stop_loss() const;

    double get_limit_order() const;

    void set_current_capital(const double &current_capital);

    void set_total_capital(const double &total_capital);

    void set_holdings(const map<string, pair<string, double>> &holdings);

    void print() override {};
};