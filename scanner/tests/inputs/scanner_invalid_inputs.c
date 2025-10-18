#include "../../token.h"
#include <stdlib.h>

typedef struct {
    const char* name;      // názov testu
    const char* source;    // vstupný zdroj
    int expected_count;    // počet očakávaných tokenov
} LexerFailingTest;

// --- TEST Simple assignment --- 
char *failing_test1_name = "Invalid id name";
char *failing_test1_input = "var 7xyz = y + 10\n";
int failing_test1_expected_count = 7;
// ------------
