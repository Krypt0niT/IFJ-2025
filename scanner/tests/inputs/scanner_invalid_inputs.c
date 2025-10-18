#include "../../token.h"
#include <stdlib.h>

typedef struct {
    const char* name;      // názov testu
    const char* source;    // vstupný zdroj
    int expected_count;    // počet očakávaných tokenov
} LexerFailingTest;