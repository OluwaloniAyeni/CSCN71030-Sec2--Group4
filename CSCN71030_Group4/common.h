#pragma once

#include <stddef.h>

/**
 * @file common.h
 * @brief Contains common utility functions.
 * @details This header file declares helper functions used for
 * string processing, comparison, parsing, and safe copying.
 * @author Oluwaloni Ayeni
 * @date 2026-04-13
 */


 /**
  * @brief Removes newline characters from a string.
  * @details Removes '\n' and '\r' from the end of the string.
  * @author Oluwaloni Ayeni
  * @param s Pointer to string.
  * @return void
  */
void trim_newline(char* s);


/**
 * @brief Removes leading and trailing spaces from a string.
 * @details Trims whitespace from the beginning and end of the string.
 * @author Oluwaloni Ayeni
 * @param s Pointer to string.
 * @return void
 */
void trim_spaces(char* s);


/**
 * @brief Converts a string to lowercase.
 * @details Changes all uppercase characters to lowercase.
 * @author Oluwaloni Ayeni
 * @param s Pointer to string.
 * @return void
 */
void toLowercase(char* s);


/**
 * @brief Compares two strings ignoring case.
 * @details Checks if two strings are equal regardless of uppercase/lowercase.
 * @author Oluwaloni Ayeni
 * @param a First string.
 * @param b Second string.
 * @return int Returns 1 if equal, otherwise 0.
 */
int strings_equal_ignore_case(const char* a, const char* b);


/**
 * @brief Converts a string to a double safely.
 * @details Parses a string into a double and ensures it is valid.
 * @author Oluwaloni Ayeni
 * @param text Input string.
 * @param out Pointer to store result.
 * @return int Returns 1 if successful, otherwise 0.
 */
int parse_double_strict(const char* text, double* out);


/**
 * @brief Safely copies one string into another.
 * @details Copies source string into destination without overflow.
 * @author Oluwaloni Ayeni
 * @param dest Destination string.
 * @param destSize Size of destination buffer.
 * @param src Source string.
 * @return void
 */
void safe_strcpy(char* dest, size_t destSize, const char* src);