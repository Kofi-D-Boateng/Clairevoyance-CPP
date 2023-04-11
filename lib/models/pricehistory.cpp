#include <vector>
#include <string>
#include "include/pricehistory.h"
#include "include/serializable.h"

using std::string;
using std::vector;

PriceHistory::PriceHistory() : Serializable() {}

PriceHistory::PriceHistory(const AssetType &asset_type, const string &ticker, const vector<CandleStick> &candles, const int &period, const IntervalType &interval_type, const Interval &interval, const Range &range, const Interval &range_interval) : Serializable(), asset_type(asset_type), ticker(ticker), candles(candles), interval(interval), interval_type(interval_type), range(range), range_interval(range_interval) {}

PriceHistory::PriceHistory(const PriceHistory &obj) : Serializable(), ticker(obj.get_ticker()), candles(obj.candles) {}

PriceHistory::CandleStick::CandleStick() {}

PriceHistory::CandleStick::CandleStick(const double &datetime, const double &open, const double &close, const double &high, const double &low, const double &volume) : datetime(datetime), open(open), close(close), high(high), low(low), volume(volume) {}

PriceHistory &PriceHistory::operator=(const PriceHistory &obj)
{
    ticker = obj.get_ticker();
    candles = obj.candles;

    return *this;
}

PriceHistory::~PriceHistory() {}

AssetType PriceHistory::get_asset_type()const {return asset_type;}

string PriceHistory::get_ticker() const { return ticker; }

vector<PriceHistory::CandleStick> PriceHistory::get_candles() const { return candles; }

IntervalType PriceHistory::get_interval_type() const { return interval_type; }

Interval PriceHistory::get_interval() const { return interval; }

Range PriceHistory::get_range() const { return range; }

Interval PriceHistory::get_range_interval() const {return range_interval;}

void PriceHistory::set_asset_type(const AssetType &asset_type) {this->asset_type = asset_type;}

void PriceHistory::set_ticker(const string &ticker) { this->ticker = ticker; }

void PriceHistory::set_candles(const vector<CandleStick> &candles) { this->candles = candles; }

void PriceHistory::set_interval(const Interval &interval) {this->interval = interval;}

void PriceHistory::set_interval_type(const IntervalType &interval_type) {this->interval_type = interval_type;}

void PriceHistory::set_range(const Range &range) {this->range = range;}

void PriceHistory::set_range_interval(const Interval &range_interval) {this->range_interval = range_interval;}
