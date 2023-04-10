#include <utility>
#include <string>
#include <map>
#include "include/portfolio.h"
#include "include/serializable.h"

using std::string;
using std::map;

Portfolio::Portfolio(const double &current_capital, const double &total_capital, const map<string, pair<string, double>> &holdings, const double &mea, const double &stop_loss, const double &limit_order) : Serializable(), current_capital(current_capital), total_port_capital(total_capital), holdings(holdings), max_exposure_allowed(mea), stop_loss(stop_loss),limit_order(limit_order){};

Portfolio::Portfolio(const Portfolio &obj) : Serializable(), current_capital(obj.current_capital), total_port_capital(obj.total_port_capital), holdings(obj.holdings), max_exposure_allowed(obj.max_exposure_allowed), stop_loss(obj.stop_loss),limit_order(obj.limit_order){};

Portfolio &Portfolio::operator=(const Portfolio &obj)
{
    current_capital = obj.current_capital;
    total_port_capital = obj.total_port_capital;
    holdings = obj.holdings;
    max_exposure_allowed = obj.max_exposure_allowed;
    stop_loss = obj.stop_loss;
    limit_order = obj.limit_order;
    return *this;
}

Portfolio::~Portfolio() {}

double Portfolio::get_current_capital() { return current_capital; }

double Portfolio::get_total_capital() { return total_port_capital; }

map<string, pair<string, double>> Portfolio::get_holdings() { return holdings; }

double Portfolio::get_max_exposure_allowed() const { return max_exposure_allowed;}

double Portfolio::get_stop_loss() const {return stop_loss;}

double Portfolio::get_limit_order() const {return limit_order;}

void Portfolio::set_current_capital(const double &value) { current_capital = value; }

void Portfolio::set_total_capital(const double &value) { total_port_capital = value; }

void Portfolio::set_holdings(const map<string, pair<string, double>> &value) { holdings = value; }
