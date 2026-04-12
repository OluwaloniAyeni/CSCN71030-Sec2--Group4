#include "common.h"
#include "item.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void trim_newline(char* s) {
    size_t len;

    if (s == NULL) {
        return;
    }

    len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[len - 1] = '\0';
        len--;
    }
}

void trim_spaces(char* s) {
    size_t start = 0;
    size_t end;
    size_t i;

    if (s == NULL || s[0] == '\0') {
        return;
    }

    while (s[start] != '\0' && isspace((unsigned char)s[start])) {
        start++;
    }

    end = strlen(s);
    while (end > start && isspace((unsigned char)s[end - 1])) {
        end--;
    }

    if (start > 0) {
        for (i = 0; i + start < end; ++i) {
            s[i] = s[i + start];
        }
        s[i] = '\0';
    }

    s[end - start] = '\0';
}

void to_lowercase(char* s) {
    size_t i;

    if (s == NULL) {
        return;
    }

    for (i = 0; s[i] != '\0'; ++i) {
        s[i] = (char)tolower((unsigned char)s[i]);
    }
}

int strings_equal_ignore_case(const char* a, const char* b) {
    size_t i = 0;

    if (a == NULL || b == NULL) {
        return 0;
    }

    while (a[i] != '\0' && b[i] != '\0') {
        if (tolower((unsigned char)a[i]) != tolower((unsigned char)b[i])) {
            return 0;
        }
        i++;
    }

    return a[i] == '\0' && b[i] == '\0';
}

int parse_double_strict(const char* text, double* out) {
    char* endPtr;
    double value;

    if (text == NULL || out == NULL) {
        return 0;
    }

    value = strtod(text, &endPtr);
    if (endPtr == text) {
        return 0;
    }

    while (*endPtr != '\0') {
        if (!isspace((unsigned char)*endPtr)) {
            return 0;
        }
        endPtr++;
    }

    *out = value;
    return 1;
}

void safe_strcpy(char* dest, size_t destSize, const char* src) {
    if (dest == NULL || destSize == 0) {
        return;
    }

    if (src == NULL) {
        dest[0] = '\0';
        return;
    }

    strncpy(dest, src, destSize - 1);
    dest[destSize - 1] = '\0';
}
