#pragma once

#include <stddef.h>

void trim_newline(char* s);
void trim_spaces(char* s);
void toLowercase(char* s);
int strings_equal_ignore_case(const char* a, const char* b);
int parse_double_strict(const char* text, double* out);
void safe_strcpy(char* dest, size_t destSize, const char* src);
