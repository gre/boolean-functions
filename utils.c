#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#include "utils.h"

extern void str_tolower(char* str) {
  while(*str) {
    *str = tolower(*str);
    str ++;
  }
}

extern char* str_trim(char *s) {
    char* newString;
    while(isspace(*s)) s++;
    newString = malloc(sizeof(*s) * (strlen(s) + 1));
    strcpy(newString, s);
    char* last;
    for (last = newString+strlen(newString)-1; (last >= newString) && isspace(*last); --last);
    last[1] = '\0';
    return newString;
}
