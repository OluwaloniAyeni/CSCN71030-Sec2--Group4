#pragma once
#ifndef USER_INPUT_H
#define USER_INPUT_H

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

#endif
