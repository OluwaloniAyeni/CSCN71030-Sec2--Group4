#ifndef FEATURE_DISPLAY_H
#define FEATURE_DISPLAY_H

#include "models.h"

int filterFeatures(
    const Facility* input,
    size_t inputCount,
    Facility** output,
    size_t* outputCount
);

#endif

