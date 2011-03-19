#ifndef _FILE_H
#define _FILE_H

#include "globals.h"

/**
 * return 0 if fopen failed OR if user don't want to override existing file
 */
FILE* file_fopenOutput(char* path);

#endif
