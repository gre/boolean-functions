#ifndef _UTILS_H
#define _UTILS_H
/**
* Utils module
*/

/**
* Trim a string (remove extra spaces around words)
* @return the trimed string
*/
extern char* str_trim(char *s);
extern void str_tolower(char* str);
extern int util_letterInWord(char letter, char* word);
extern int util_indexOfLetter(char letter, char* word);

extern char* str_strips(char *s, char *cs);

#endif
