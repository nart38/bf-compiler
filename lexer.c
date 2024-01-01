#include <stdio.h>
#include <stdlib.h>

// typedef struct {
//   unsigned int len;
//   unsigned char text[];
// } code;
//
typedef enum {
  INCREASE,
  DECREASE,
  PTR_NEXT,
  PTR_PREV,
  STD_IN,
  STD_OUT,
  LOOP_START,
  LOOP_END
} token_kind;

typedef struct {
  token_kind kind;
  unsigned int position;
  unsigned int jmp_position;
} token;

char *parser(char *file_dir) {
  FILE *fptr = fopen(file_dir, "r");
  if (fptr == NULL) {
    puts("ERROR: Could not read the file!!!");
    return NULL;
  }

  int current_len = 4096;
  int index = 0;
  char *code_buffer = calloc(current_len, sizeof(char));
  if (code_buffer == NULL) {
    puts("ERROR: allocating array failed!!!");
    return NULL;
  }

  for (int current_ch = fgetc(fptr); current_ch != EOF;
       current_ch = fgetc(fptr)) {
    if (index >= current_len - 1) {
      code_buffer = reallocarray(code_buffer, current_len + 4096, sizeof(char));
      if (code_buffer == NULL) {
        puts("ERROR: re-allocating array failed!!!");
        return NULL;
      }
    }
    switch (current_ch) {
    case 43 || 44 || 45 || 46 || 74 || 76 || 91 || 93:
      code_buffer[index] = current_ch;
      index++;
      break;
    }
  }

  // code_buffer = reallocarray(code_buffer, index + 1, sizeof(char));
  // if (code_buffer == NULL) {
  //   puts("ERROR: re-allocating array failed!!!");
  //   return NULL;
  // }
  // code_buffer[index] = 0;

  fclose(fptr);
  return code_buffer;
}
