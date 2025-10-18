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

LexerFailingTest failing_test9 = {
    "Invalid num format hex starts with 00",
    "00.1x00\n",
    2
};

LexerFailingTest failing_test10 = {
    "Invalid num format exp starts with 00",
    "00.1e8\n",
    2
};

LexerFailingTest failing_test11 = {
    "Invalid num format exp has 2 periods",
    "0.1.2e8\n",
    2
};

LexerFailingTest failing_test12 = {
    "Invalid num format exp starts with period",
    ".12e8\n",
    2
};

LexerFailingTest failing_test13 = {
    "Invalid num format hex longer than 2 characters after x",
    "0x158\n",
    2
};

LexerFailingTest failing_test14 = {
    "Invalid num format int is 00",
    "00\n",
    2
};

LexerFailingTest failing_test15 = {
    "No string literal ending 1",
    "\"asdasd\n",
    2
};

LexerFailingTest failing_test16 = {
    "No string literal ending 2",
    "asdasd\"\n",
    2
};

LexerFailingTest failing_test17 = {
    "Input is longer than integer limit",
    "5646854684684864431213213\n",
    2
};

LexerFailingTest failing_test18 = {
    "Input low int limit",
    "-2147483647\n",
    2
};

LexerFailingTest failing_test19 = {
    "Input max int limit",
    "2147483647\n",
    2
};

LexerFailingTest failing_test20 = {
    "Input exceeds int +",
    "2147483648\n",
    2
};

LexerFailingTest failing_test21 = {
    "Input exceeds int -",
    "-2147483648\n",
    2
};

LexerFailingTest failing_test22 = {
    "Input exceeds int exp",
    "2.147483648e9\n",  // 2147483648, presahuje INT32_MAX
    2
};

LexerFailingTest failing_test23 = {
    "Input below INT32_MIN exp",
    "-2.147483649e9\n",  // -2147483649, menšie než INT32_MIN
    2
};
