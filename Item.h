#pragma once
#include "BigNumber.h"

enum class Line
{
    START,
    AFTER_FIRST,
    AFTER_SECOND,
    AFTER_THIRD
};

struct Item
{
    bigNumber x, y, a, b, c, d, ac, bd, aPlusBcPlusD;
    Line line;
    int size;
};
