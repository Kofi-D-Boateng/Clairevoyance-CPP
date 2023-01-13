#include <iostream>
#include <stdexcept>
#include <ostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include "core/predictor/headers/analyzer.h"
#include "core/models/headers/pricehistory.h"
using namespace std;

Analyzer::Analyzer() : arbitrage_threshold(0), correlation_threshold(0){};

Analyzer::Analyzer(const double &arb_thresh) : arbitrage_threshold(arb_thresh), correlation_threshold(0){};

Analyzer::Analyzer(const double &arb, const double &corr) : arbitrage_threshold(arb), correlation_threshold(corr){};

Analyzer::Analyzer(const Analyzer &obj) : arbitrage_threshold(obj.get_arbitrage_threshold()), correlation_threshold(obj.get_correlation_threshold()){};

Analyzer &Analyzer::operator=(const Analyzer &obj)
{
    arbitrage_threshold = obj.get_arbitrage_threshold();
    correlation_threshold = obj.get_correlation_threshold();
    return *this;
}

Analyzer::~Analyzer(){};

double Analyzer::get_arbitrage_threshold() const { return arbitrage_threshold; }

double Analyzer::get_correlation_threshold() const { return correlation_threshold; }

void Analyzer::set_arbitrage_threshold(const double &arb) { arbitrage_threshold = arb; }

void Analyzer::set_correlation_threshold(const double &corr) { correlation_threshold = corr; }

double Analyzer::generate_correlation_value(PriceHistory &stock1, PriceHistory &stock2)
{
}

unordered_map<pair<PriceHistory, PriceHistory>, double> Analyzer::generate_correlation_map(const vector<pair<PriceHistory, PriceHistory>> &stock_pairs_list)
{
    unordered_map<pair<PriceHistory, PriceHistory>, double> pair_map;
    for (auto stock_pair : stock_pairs_list)
    {
        auto value = generate_correlation_value(stock_pair.first, stock_pair.second);
        pair_map[stock_pair] = value;
    }
    return pair_map;
}

unordered_map<PriceHistory, unordered_map<PriceHistory, double>> Analyzer::generate_correlation_map(const vector<PriceHistory> &stock_vec)
{
    unordered_map<PriceHistory, unordered_map<PriceHistory, double>> corr_map;
    for (int i = 0; i < stock_vec.size(); i++)
    {
        int j = i + 1;
        while (j++ != stock_vec.size() - 1)
        {
            PriceHistory s1 = stock_vec.at(i);
            PriceHistory s2 = stock_vec.at(j);
            auto value = generate_correlation_value(s1, s2);
            corr_map[s1][s2] = value;
        }
    }
    return corr_map;
}

vector<double> Analyzer::generate_moving_average(const PriceHistory &stock, const int &window, const MovingAverageType type) const
{
}

unordered_map<PriceHistory, map<int, vector<double>>> Analyzer::generate_moving_averages_map(const PriceHistory &stock, const vector<int> &windows, const MovingAverageType type) const
{
    unordered_map<PriceHistory, map<int, vector<double>>> ma_map;
    map<int, vector<double>> inner_map;
    for (auto window : windows)
    {
        auto ma = generate_moving_average(stock, window, type);
        inner_map[window] = ma;
    }
    ma_map[stock] = inner_map;
    return ma_map;
}

unordered_map<PriceHistory, map<int, vector<double>>> Analyzer::generate_moving_averages_map(const vector<PriceHistory> &stock_vec, const int &window, const MovingAverageType type) const
{
    unordered_map<PriceHistory, map<int, vector<double>>> ma_map;
    for (auto stock : stock_vec)
    {
        auto ma = generate_moving_average(stock, window, type);
        map<int, vector<double>> inner_map;
        inner_map[window] = ma;
        ma_map[stock] = inner_map;
    }
    return ma_map;
}

unordered_map<PriceHistory, map<int, vector<double>>> Analyzer::generate_moving_averages_map(const vector<PriceHistory> &stock_vec, const vector<int> &windows, const MovingAverageType type) const
{
    unordered_map<PriceHistory, map<int, vector<double>>> ma_map;
    for (auto stock : stock_vec)
    {
        map<int, vector<double>> inner_map;
        for (auto window : windows)
        {
            auto ma = generate_moving_average(stock, window, type);
            inner_map[window] = ma;
        }
        ma_map[stock] = inner_map;
    }
    return ma_map;
}

string Analyzer::generate_stock_momentum(const PriceHistory &stock, const int &window) const {}

unordered_map<PriceHistory, string> Analyzer::generate_stocks_momentum_map(const vector<PriceHistory> &stock_vec, const int &window) const
{
    unordered_map<PriceHistory, string> momentum_map;
    for (auto stock : stock_vec)
    {
        string momentum = generate_stock_momentum(stock, window);
        momentum_map[stock] = momentum;
    }
    return momentum_map;
}