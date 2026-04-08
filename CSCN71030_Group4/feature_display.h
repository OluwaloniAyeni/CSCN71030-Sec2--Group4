#pragma once

#include "item.h"

int filterFeatures(
    const Facility* input,
    size_t inputCount,
    Facility** output,
    size_t* outputCount
);
