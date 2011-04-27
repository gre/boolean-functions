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

extern int util_indexOfLetter(char letter, char* word) {
  int i = 0;
  while(word[i]) {
    if(word[i] == letter)
      return i;
    ++ i;
  }
  return -1;
}
extern int util_letterInWord(char letter, char* word) {
  return util_indexOfLetter(letter, word)!=-1;
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

extern char* str_strips(char *s, char *cs) {
	char *r;
	int i = -1, j = 0;
	r = calloc(strlen(s)+1, sizeof(char));
	while (s[++i]) {
		if (index(cs, s[i]) != NULL) continue;
		r[j++] = s[i];
	}
	r[j] = '\0';
	return r;	
}
