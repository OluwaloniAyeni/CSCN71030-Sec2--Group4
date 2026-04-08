#pragma once



typedef struct {
    int itemID;
    char name[50];
    char category[50];
    float price;
    float rating;
} Item;

typedef struct {
    char name[50];
    char category[50];
    float price;
    float rating;
    int hasWifi;
    int hasParking;
} Facility;

typedef struct {
    Facility* items;
    size_t count;
} FacilityList;

typedef struct {
    char category[50];
    double budget;
} UserRequest;

typedef struct {
    char category[50];
    double budget;
} BudgetRecord;

typedef struct {
    BudgetRecord* items;
    size_t count;
} BudgetHistory;