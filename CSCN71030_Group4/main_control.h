#pragma once

#include "item.h"

/**
 * @file main_control.h
 * @brief Controls the main program flow.
 * @details This file declares functions responsible for starting
 * the program and managing the overall workflow of the system,
 * including filtering, recommendation, and displaying results.
 * @author Oluwaloni Ayeni
 * @date 2026-04-13
 */


 /**
  * @brief Starts the recommendation system.
  * @details This function initializes the system, loads data from file,
  * and begins the main program loop.
  * @author Oluwaloni Ayeni
  * @param filename Name of the data file to load.
  * @return int Returns 1 if the program runs successfully, otherwise 0.
  * @date 2026-04-13
  */
int startProgram(const char* filename);


/**
 * @brief Manages one full program flow.
 * @details This function handles user input, validation,
 * filtering, recommendation, and displaying results.
 * @author Oluwaloni Ayeni
 * @param allItems Pointer to all facility records.
 * @param count Number of facilities.
 * @return void
 * @date 2026-04-13
 */
void manageFlow(Facility* allItems, int count);