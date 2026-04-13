#define _CRT_SECURE_NO_WARNINGS

#include "common.h"
#include "item.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file common.c
 * @brief Contains common helper functions used in the system.
 * @details This file provides utility functions for cleaning strings,
 * converting text, comparing strings, parsing numbers, and safely copying strings.
 * @author Oluwaloni Ayeni
 * @date 2026-04-13
 */


 /**
  * @brief Removes newline characters from a string.
  * @details This function removes trailing '\n' and '\r' characters
  * from the end of a string.
  * @author Oluwaloni Ayeni
  * @param s Pointer to the string to modify.
  * @return void
  * @date 2026-04-13
  */
void trim_newline(char* s) {
    size_t len;

	// check if string is valid before processing
    if (s == NULL) {
        return;
    }

	// remove newline and carriage return characters from the end of the string
    len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[len - 1] = '\0';
        len--;
    }
}

/**
 * @brief Removes leading and trailing spaces from a string.
 * @details This function trims whitespace from the beginning and end
 * of the given string.
 * @author Oluwaloni Ayeni
 * @param s Pointer to the string to modify.
 * @return void
 * @date 2026-04-13
 */
void trim_spaces(char* s) {
    size_t start = 0;
    size_t end;
    size_t i;

	// check if string is empty or invalid before processing
    if (s == NULL || s[0] == '\0') {
        return;
    }

	// find first non-space character from the start of the string
    while (s[start] != '\0' && isspace((unsigned char)s[start])) {
        start++;
    }

	// find last non-space character from the end of the string
    end = strlen(s);
    while (end > start && isspace((unsigned char)s[end - 1])) {
        end--;
    }

    // shift string left if there are leading spaces.
    if (start > 0) {
        for (i = 0; i + start < end; ++i) {
            s[i] = s[i + start];
        }
        s[i] = '\0';
    }

    // remove trailing spaces.
    s[end - start] = '\0';
}

/**
 * @brief Converts a string to lowercase.
 * @details This function changes all uppercase letters in the string
 *          to lowercase letters.
 * @author Oluwaloni Ayeni
 * @param s Pointer to the string to modify.
 * @return void
 * @date 2026-04-13
 */
void toLowercase(char* s) {
    size_t i;

	// check if string is valid before processing
    if (s == NULL) {
        return;
    }

	// convert each character to lowercase using tolower function
    for (i = 0; s[i] != '\0'; ++i) {
        s[i] = (char)tolower((unsigned char)s[i]);
    }
}

/**
 * @brief Compares two strings without considering letter case.
 * @details This function checks whether two strings are equal
 * even if their uppercase and lowercase letters differ.
 * @author Oluwaloni Ayeni
 * @param a First string.
 * @param b Second string.
 * @return int Returns 1 if equal, otherwise 0.
 * @date 2026-04-13
 */
int strings_equal_ignore_case(const char* a, const char* b) {
    size_t i = 0;

	//check if either string is inavalid before processing
    if (a == NULL || b == NULL) {
        return 0;
    }

    // compare each character one by one.
    while (a[i] != '\0' && b[i] != '\0') {
        if (tolower((unsigned char)a[i]) != tolower((unsigned char)b[i])) {
            return 0;
        }
        i++;
    }

    // return true if both string end together.
    return a[i] == '\0' && b[i] == '\0';
}

/**
 * @brief Converts a string into a double value.
 * @details This function strictly parses a string to a double
 * and returns failure if invalid characters are found.
 * @author Oluwaloni Ayeni
 * @param text Input string to parse.
 * @param out Pointer to store the converted double value.
 * @return int Returns 1 if conversion is successful, otherwise 0.
 * @date 2026-04-13
 */
int parse_double_strict(const char* text, double* out) {
    char* endPtr;
    double value;

	// validate input pointers before processing
    if (text == NULL || out == NULL) {
        return 0;
    }

	// convert string to double using strtod, which sets endPtr to the first invalid character
    value = strtod(text, &endPtr);
    if (endPtr == text) {
        return 0;
    }

	// make sure the remaining characters are only spaces until the end of the string
    while (*endPtr != '\0') {
        if (!isspace((unsigned char)*endPtr)) {
            return 0;
        }
        endPtr++;
    }

    *out = value;
    return 1;
}
/**
 * @brief Safely copies one string into another.
 * @details This function copies a source string into a destination
 * string while preventing buffer overflow.
 * @author Oluwaloni Ayeni
 * @param dest Destination string.
 * @param destSize Size of the destination buffer.
 * @param src Source string.
 * @return void
 * @date 2026-04-13
 */
void safe_strcpy(char* dest, size_t destSize, const char* src) {

    //check if destination is valid.
    if (dest == NULL || destSize == 0) {
        return;
    }

	// if source is NULL, make destination an empty string and return.
    if (src == NULL) {
        dest[0] = '\0';
        return;
    }

	// copy source safely and add null terminator at the end of the destination buffer.
    strncpy(dest, src, destSize - 1);
    dest[destSize - 1] = '\0';
}
