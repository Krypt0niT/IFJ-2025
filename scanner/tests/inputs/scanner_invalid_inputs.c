#include "../../token.h"
#include <stdlib.h>

typedef struct {
    const char* name;      // názov testu
    const char* source;    // vstupný zdroj
    int expected_count;    // počet očakávaných tokenov
} LexerFailingTest;

LexerFailingTest failing_test1 = {
    "Invalid id name",
    "7xyz\n",
    2
};

LexerFailingTest failing_test2 = {
    "Invalid num format float",
    "00.1\n",
    2
};

LexerFailingTest failing_test3 = {
    "Invalid num format float",
    "0.0.1\n",
    2
};

LexerFailingTest failing_test4 = {
    "Invalid num format hex",
    "0x7p\n",
    2
};

LexerFailingTest failing_test5 = {
    "Invalid num format exp both signes",
    "1E+-7p\n",
    2
};

LexerFailingTest failing_test6 = {
    "Invalid num format exp no sign",
    "1E7p\n",
    2
};

LexerFailingTest failing_test7 = {
    "Invalid num format exp same sign",
    "1E--7p\n",
    2
};

LexerFailingTest failing_test8 = {
    "Invalid num format hex starts with non 0",
    "1x00\n",
    2
};
