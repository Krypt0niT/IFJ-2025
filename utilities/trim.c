#include <string.h>
#include <ctype.h>

char *trim(char *s)
{
    if (s == NULL) {
        return NULL;
    }

    char *src = s;
    char *dst = s;

    while (*src != '\0') {
        if (!isspace((unsigned char)*src)) {
            *dst++ = *src;
        }
        src++;
    }

    *dst = '\0';

    return s;
}
