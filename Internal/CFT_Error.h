#pragma once
#include <stdio.h>
#include <stdlib.h>

#define Err_Alloc(ptr) \
    if (ptr == NULL) \
    { \
        printf("ERROR: '%s' could not be allocated.", #ptr); \
        char final_Str[100]; \
        fgets(final_Str, 100, stdin); \
        exit(EXIT_FAILURE); \
    }

    