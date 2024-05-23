#define _CRT_SECURE_NO_WARNINGS

#include "funcs.h"

int check_str(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i])) {
            throw -1;
        }
    }
    return 1;
}

long check_int(char *input) {
    long result;
    char *endptr;

    result = strtol(input, &endptr, 10);

    if (*endptr != '\0') {
        throw -1;
    }
    return result;
}

long check_spec(char *input) {
    long result;
    char *endptr;

    result = strtol(input, &endptr, 10);

    if (*endptr != '\0') {
        throw -1;
    } else if (result < 1 || result > 3) {
        throw "Нет такой специальности\n\n";
    }

    return result;
}

long check_qual(char *input) {
    long result;
    char *endptr;

    result = strtol(input, &endptr, 10);

    if (*endptr != '\0') {
        throw -1;
    } else if (result < 0 || result > 2) {
        throw "Нет такой квалификации\n\n";
    }

    return result;
}
