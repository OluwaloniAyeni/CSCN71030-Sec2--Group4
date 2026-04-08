#ifndef MODELS_H
#define MODELS_H

#include <stddef.h>

#define NAME_LEN 128
#define CATEGORY_LEN 32

typedef struct {
    char name[NAME_LEN];
    char category[CATEGORY_LEN];
    double price;
    double rating;
    int hasWifi;
    int hasParking;
} Facility;

typedef struct {
    Facility* items;
    size_t count;
} FacilityList;

typedef struct {
    char category[CATEGORY_LEN];
    double budget;
} UserRequest;

typedef struct {
    char category[CATEGORY_LEN];
    double budget;
} BudgetRecord;

typedef struct {
    BudgetRecord* items;
    size_t count;
} BudgetHistory;

#endif

