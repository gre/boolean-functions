#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "file.h"

FILE* file_fopenOutput(char* path) {
  FILE* f = fopen(path, "r");
  char response;
  if(f) {
    fclose(f);
    printf("Override %s ? (Y/n) : ", path);
    scanf("%c", &response);
    if(response!='Y')
      return 0;
  }
  return fopen(path, "w");
}