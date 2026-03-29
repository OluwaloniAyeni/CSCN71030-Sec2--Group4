#pragma once

#include "user_input.h"

typedef struct {
    int id;
    CategoryType category;
    float price;
    char name[50];
} Item;

void processBudget(UserRequest req);

