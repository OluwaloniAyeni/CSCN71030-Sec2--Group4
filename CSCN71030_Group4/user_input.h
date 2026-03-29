#pragma once

typedef enum {
    GYM,
    HOTEL,
    RESTAURANT
} CategoryType;

typedef struct {
    CategoryType category;
    float maxBudget;
} UserRequest;

UserRequest getUserInput();
