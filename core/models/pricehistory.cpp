#include <map>
#include <string>
#include <core/models/headers/pricehistory.h>

using std::map;
using std::string;

PriceHistory::PriceHistory() : ticker(""), ticker_info() {}

PriceHistory::PriceHistory(const string &ticker, const map<double, map<string, double>> &info) : ticker(ticker), ticker_info(info) {}

PriceHistory::PriceHistory(const PriceHistory &obj) : ticker(obj.get_ticker()), ticker_info(obj.get_ticker_info()) {}

PriceHistory &PriceHistory::operator=(const PriceHistory &obj)
{
    ticker = obj.get_ticker();
    ticker_info = obj.get_ticker_info();

    return *this;
}

PriceHistory::~PriceHistory() {}

string PriceHistory::get_ticker() const { return ticker; }

map<double, map<string, double>> PriceHistory::get_ticker_info() const { return ticker_info; }

void PriceHistory::set_ticker(const string &str) { ticker = str; }

void PriceHistory::set_ticker_info(const map<double, map<string, double>> &info_map) { ticker_info = info_map; }
