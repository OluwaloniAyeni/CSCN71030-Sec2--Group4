#pragma once

#include <stddef.h>

/**
 * @file item.h
 * @brief Defines data structures used in the system.
 * @details This file contains all the structures used in the
 * Budget-Based Recommendation System including Facility,
 * UserRequest, and data storage structures.
 * @author Oluwaloni Ayeni
 * @date 2026-04-13
 */

 /**
  * @struct Facility
  * @brief Stores information about a facility.
  * @details Contains details such as name, category, price,
  * rating, and available features like Wi-Fi and parking.
  */
typedef struct {
    int facilityID;        // Unique ID of the facility //
    char name[50];         // Name of the facility //
    char category[50];     // Category (gym, hotel, restaurant, cafe) //
    float price;           // Price of the facility //
    float rating;          // Rating (0.0 - 5.0) //
    int hasWifi;           // 1 if Wi-Fi is available, 0 otherwise //
    int hasParking;        // 1 if parking is available, 0 otherwise //
} Facility;

/**
 * @struct FacilityList
 * @brief Stores a list of facilities.
 * @details Holds a dynamic array of Facility items and the count.
 */
typedef struct {
    Facility* items;       //Pointer to list of facilities //
    size_t count;          // Number of facilities //
} FacilityList;

/**
 * @struct UserRequest
 * @brief Stores user input data.
 * @details Contains selected category and budget entered by the user.
 */
typedef struct {
    char category[50];     // Selected category //
    double budget;         // User's budget //
} UserRequest;

/**
 * @struct BudgetRecord
 * @brief Stores a single budget history record.
 * @details Keeps track of category and budget used previously.
 */
typedef struct {
    char category[50];     // Category searched //
    double budget;         // Budget used //
} BudgetRecord;

/**
 * @struct BudgetHistory
 * @brief Stores multiple budget records.
 * @details Maintains a list of previous user budget searches.
 */
typedef struct {
    BudgetRecord* items;   // Pointer to budget records //
    size_t count;          // Number of records //
} BudgetHistory;