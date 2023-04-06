
/**
 * @file cusomterhashes
 * @author Kofi Boateng
 * 
 */

#pragma once
#include "include/pricehistory.h"
#include <string>
#include <utility>

using std::hash;
using std::string;
using std::pair;


struct PriceHistoryHash {
    size_t operator()(const PriceHistory &obj)const{
        return hash<string>{}(obj.get_ticker());
    }
};

struct PairPriceHistoryHash {
    size_t operator()(const pair<PriceHistory,PriceHistory> &obj)const{
        string concatted_string = obj.first.get_ticker() + obj.second.get_ticker();
        return hash<string>{}(concatted_string);
    }
};