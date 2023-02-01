#include <iostream>
#include <sstream>
#include <stdexcept>
#include <ostream>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include "include/analyzer.h"
#include "include/pricehistory.h"

using std::vector;
using std::map;
using std::pair;
using std::string;
using std::stringstream;

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

// FIND A COMPUTATIONAL LIBRARY TO ADD TO THE ANALYZER
double Analyzer::generate_correlation_value(PriceHistory &stock1, PriceHistory &stock2)
{
}

map<pair<PriceHistory, PriceHistory>, double> Analyzer::generate_correlation_map(const vector<pair<PriceHistory, PriceHistory>> &stock_pairs_list)
{
    map<pair<PriceHistory, PriceHistory>, double> pair_map;
    for (auto stock_pair : stock_pairs_list)
    {
        auto value = generate_correlation_value(stock_pair.first, stock_pair.second);
        pair_map[stock_pair] = value;
    }
    return pair_map;
}

map<PriceHistory, map<PriceHistory, double>> Analyzer::generate_correlation_map(const vector<PriceHistory> &stock_vec)
{
    map<PriceHistory, map<PriceHistory, double>> corr_map;
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

vector<pair<double, double>> Analyzer::generate_dynamic_ema(const PriceHistory &stock, const double &window) const
{
    vector<pair<double, double>> ema;
    vector<PriceHistory::CandleStick> candles = stock.get_candles();

    if (window > candles.size())
    {
        cout << "There is not enough data to create a " << window << " day moving average" << endl;
        return ema;
    }

    int start{0}, end{1}, endOfCandles{candles.size() - 1};

    while (end <= endOfCandles)
    {
        int counter{0};
        double alpha{1.0 / window}, weight = 0;
        double curr_ema{candles.at(start).close}, date{0};
        while (counter++ <= window)
        {
            weight += alpha;
            curr_ema = (candles.at(end++).close * alpha) + (curr_ema * (1 - alpha));
        }

        pair<double, double> dateAvgPair;
        dateAvgPair.first = candles.at(end).datetime;
        dateAvgPair.second = curr_ema;
        ema.push_back(dateAvgPair);

        start++;
        end = start + 1;
        counter = 0;
    }

    return ema;
}

vector<pair<double, double>> Analyzer::generate_ema(const PriceHistory &stock, const double &window) const
{
    vector<pair<double, double>> ema;
    vector<PriceHistory::CandleStick> candles = stock.get_candles();
    int start{0}, end{1}, endOfCandles{candles.size() - 1};
    double alpha{2.0 / (window + 1.0)};

    while (end <= endOfCandles)
    {
        int counter{0};
        double curr_ema{candles.at(start).close};
        while (counter++ <= window)
        {
            curr_ema = (candles.at(end++).close * alpha) + (curr_ema * (1 - alpha));
        }

        pair<double, double> dateAvgPair;
        dateAvgPair.first = candles.at(end).datetime;
        dateAvgPair.second = curr_ema;
        ema.push_back(dateAvgPair);

        start++;
        end = start + 1;
        counter = 0;
    }

    return ema;
}

vector<pair<double, double>> Analyzer::generate_sma(const PriceHistory &stock, const double &window) const
{
    vector<pair<double, double>> sma;
    vector<PriceHistory::CandleStick> candles = stock.get_candles();
    int start{0}, end{1}, endOfCandles{candles.size() - 1};

    /*
        We will loop through the window, calculate the average, and slide
        the start pointer up one spot and bring end pointer to start+1
        until we reach the end of the candle stack. We will handle other
        averages in another loop.
    */
    while (end <= endOfCandles)
    {
        int counter{0};
        double sum{candles.at(start).close};
        while (counter++ <= window)
        {
            sum += candles.at(end++).close;
        }

        /*
            Creating a pair where first is the timestamp where the average is calculated to,
            and second is the average.
        */

        pair<double, double> dateAvgPair;
        dateAvgPair.first = candles.at(end).datetime;
        dateAvgPair.second = sum / window;
        sma.push_back(dateAvgPair);

        start++;
        end = start + 1;
        counter = 0;
    }

    return sma;
}

vector<pair<double, double>> Analyzer::generate_moving_average(const PriceHistory &stock, const double &window, const MovingAverageType type) const
{
    if (type == MovingAverageType::SIMPLE)
    {
        return generate_sma(stock, window);
    }

    if (type == MovingAverageType::EXPONENTIAL)
    {
        return generate_ema(stock, window);
    }

    vector<pair<double, double>> empty;
    return empty;
}

map<PriceHistory, map<double, vector<pair<double, double>>>> Analyzer::generate_moving_averages_map(const PriceHistory &stock, const vector<double> &windows, const MovingAverageType type) const
{
    map<PriceHistory, map<double, vector<pair<double, double>>>> ma_map;
    map<double, vector<pair<double, double>>> inner_map;
    for (auto window : windows)
    {
        auto ma = generate_moving_average(stock, window, type);
        inner_map[window] = ma;
    }
    ma_map[stock] = inner_map;
    return ma_map;
}

map<PriceHistory, map<double, vector<pair<double, double>>>> Analyzer::generate_moving_averages_map(const vector<PriceHistory> &stock_vec, const double &window, const MovingAverageType type) const
{
    map<PriceHistory, map<double, vector<pair<double, double>>>> ma_map;
    for (auto stock : stock_vec)
    {
        auto ma = generate_moving_average(stock, window, type);
        map<double, vector<pair<double, double>>> inner_map;
        inner_map[window] = ma;
        ma_map[stock] = inner_map;
    }
    return ma_map;
}

map<PriceHistory, map<double, vector<pair<double, double>>>> Analyzer::generate_moving_averages_map(const vector<PriceHistory> &stock_vec, const vector<double> &windows, const MovingAverageType type) const
{
    map<PriceHistory, map<double, vector<pair<double, double>>>> ma_map;
    for (auto stock : stock_vec)
    {
        map<double, vector<pair<double, double>>> inner_map;
        for (auto window : windows)
        {
            auto ma_vec = generate_moving_average(stock, window, type);
            inner_map[window] = ma_vec;
        }
        ma_map[stock] = inner_map;
    }
    return ma_map;
}

string Analyzer::generate_stock_trend(const PriceHistory &stock, const double &short_term_window, const double &long_term_window) const
{
    vector<pair<double, double>> short_term_ema = generate_ema(stock, short_term_window);
    vector<pair<double, double>> long_term_sma = generate_sma(stock, long_term_window);
    vector<PriceHistory::CandleStick> candles = stock.get_candles();
    // Use Futures API to run parallel percent change functions for the
    // regular stock price, and the short & long term windows.

    double stock_percentage_change = ((candles.at(candles.size() - 1).close - candles.at(0).close) / candles.at(0).close) * 100.00;
    double short_term_percentage_change = ((short_term_ema.at(short_term_ema.size() - 1).second - short_term_ema.at(0).second) / short_term_ema.at(0).second) * 100.00;
    double long_term_percentage_change = ((long_term_sma.at(long_term_sma.size() - 1).second - long_term_sma.at(0).second) / long_term_sma.at(0).second) * 100.00;

    stringstream long_term;
    stringstream short_term;
    stringstream message;

    if (long_term_percentage_change <= 0)
    {
        long_term << "The long term trend for" << stock.get_ticker() << " is downard with a percent change of " << long_term_percentage_change;
    }
    else
    {
        long_term << "The long term trend for" << stock.get_ticker() << " is upward with a percent change of " << long_term_percentage_change;
    }

    if (short_term_percentage_change <= 0)
    {
        short_term << "The long term trend for" << stock.get_ticker() << " is downard with a percent change of " << short_term_percentage_change;
    }
    else
    {
        short_term << "The long term trend for" << stock.get_ticker() << " is upward with a percent change of " << short_term_percentage_change;
    }

    message << long_term.str() << ". " << short_term.str();

    return message.str();
}

map<PriceHistory, string> Analyzer::generate_stocks_trend_map(const vector<PriceHistory> &stock_vec, const double &short_term_window, const double &long_term_window) const
{
    map<PriceHistory, string> momentum_map;
    for (auto stock : stock_vec)
    {
        string momentum = generate_stock_trend(stock, short_term_window, long_term_window);
        momentum_map[stock] = momentum;
    }
    return momentum_map;
}