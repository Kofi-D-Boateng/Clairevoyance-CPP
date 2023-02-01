#include <vector>
#include <string>
#include "include/pricehistory.h"

using std::string;
using std::vector;

PriceHistory::PriceHistory() {}

PriceHistory::PriceHistory(const string &ticker, const vector<CandleStick> &candles, const int &period, const PeriodType &period_type, const FrequencyType &freq_type, const int &frequency) : ticker(ticker), candles(candles), period(period), periodType(periodType), frequency(frequency), frequencyType(freq_type) {}

PriceHistory::PriceHistory(const PriceHistory &obj) : ticker(obj.get_ticker()), candles(obj.candles) {}

PriceHistory::CandleStick::CandleStick() {}

PriceHistory::CandleStick::CandleStick(const double &datetime, const double &open, const double &close, const double &high, const double &low, const double &volume) : datetime(datetime), open(open), close(close), high(high), low(low), volume(volume) {}

PriceHistory &PriceHistory::operator=(const PriceHistory &obj)
{
    ticker = obj.get_ticker();
    candles = obj.candles;

    return *this;
}

PriceHistory::~PriceHistory() {}

string PriceHistory::get_ticker() const { return ticker; }

vector<PriceHistory::CandleStick> PriceHistory::get_candles() const { return candles; }

int PriceHistory::get_period() const { return period; }

PeriodType PriceHistory::get_period_type() const { return periodType; }

FrequencyType PriceHistory::get_frequecy_type() const { return frequencyType; }

int PriceHistory::get_frequency() const { return frequency; }

void PriceHistory::set_ticker(const string &str) { ticker = str; }

void PriceHistory::set_candles(const vector<CandleStick> &candles) { this->candles = candles; }

void PriceHistory::set_period(const int &period) { this->period = period; }

void PriceHistory::set_period_type(const PeriodType &per_type) { periodType = per_type; }

void PriceHistory::set_frequency(const int &frequency) { this->frequency = frequency; }

void PriceHistory::set_frequency_type(const FrequencyType &freq_type) { frequencyType = freq_type; }
