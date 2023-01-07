#include <unordered_map>
#include "headers/portfolio.h"
using std::string;
using std::unordered_map;

Portfolio::Portfolio(const double &current_capital, const double &total_capital, const unordered_map<string, unordered_map<string, double>> &holdings, const double &perc) : current_capital(current_capital), total_port_capital(total_capital), holdings(holdings), percent_of_funds_available(perc){};

Portfolio::Portfolio(const Portfolio &obj) : current_capital(obj.current_capital), total_port_capital(obj.total_port_capital), holdings(obj.holdings), percent_of_funds_available(obj.percent_of_funds_available){};

Portfolio &Portfolio::operator=(const Portfolio &obj)
{
    current_capital = obj.current_capital;
    total_port_capital = obj.total_port_capital;
    holdings = obj.holdings;
    return *this;
}

Portfolio::~Portfolio() {}

double Portfolio::get_current_capital() { return current_capital; }

double Portfolio::get_total_capital() { return total_port_capital; }

unordered_map<string, unordered_map<string, double>> Portfolio::get_holdings() { return holdings; }

void Portfolio::set_current_capital(const double &value) { current_capital = value; }

void Portfolio::set_total_capital(const double &value) { total_port_capital = value; }

void Portfolio::set_holdings(const unordered_map<string, unordered_map<string, double>> &value) { holdings = value; }
