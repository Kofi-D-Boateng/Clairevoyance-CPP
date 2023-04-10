
#pragma once

enum class MovingAverageType
{
    SIMPLE,
    EXPONENTIAL
};

enum class TrendType{
    UP,
    DOWN,
    NEUTRAL
};

enum class AssetType{
    STOCK,
    BOND,
    FOREX,
    CRYPTO,
    ETF
};

enum class IntervalType
{
    SECOND,
    MINUTE,
    DAY,
    WEEK,
    MONTH,
    QUARTER,
    YEAR,
    YTD
};

enum class Interval{
    NONE,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    TEN,
    FIFTEN,
    TWENTY,
    THIRTY
};

enum class Range{
    NONE,
    DAY,
    WEEK,
    MONTH,
    YEAR
};

/*
    Details the type of trade that should take place after the strategy
    has finished.
 */
enum class TradeSignal {
    LONG = 0,
    SHORT = 1,
    HOLD = 2
};