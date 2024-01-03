#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_code_buff(char *file_dir) {
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
    if (current_ch == 43 || current_ch == 44 || current_ch == 45 ||
        current_ch == 46 || current_ch == 60 || current_ch == 62 ||
        current_ch == 91 || current_ch == 93) {
      code_buffer[index] = current_ch;
      index++;
    }
  }

  code_buffer = reallocarray(code_buffer, index + 1, sizeof(char));
  if (code_buffer == NULL) {
    puts("ERROR: re-allocating array failed!!!");
    return NULL;
  }
  code_buffer[index] = 0;

  fclose(fptr);
  return code_buffer;
}

token create_token(token_kind kind, unsigned int pos) {
  token t;
  t.kind = kind;
  t.position = pos;
  t.jmp_position = 0;
  return t;
}

token *calculate_jump_pos(token *token_buffer, unsigned int buffer_len) {
  int pair_counter = 0;
  for (int i = 0; i < buffer_len; ++i) {
    if (token_buffer[i].kind == LOOP_START) {
      pair_counter = 1;
      for (int j = i + 1; j < buffer_len; ++j) {
        if (token_buffer[j].kind == LOOP_START) {
          pair_counter++;
          continue;
        } else if (token_buffer[j].kind == LOOP_END) {
          pair_counter--;
        }
        if (pair_counter == 0) {
          token_buffer[i].jmp_position = j;
          token_buffer[j].jmp_position = i;
          break;
        }
        if ((j == (buffer_len - 1) && pair_counter > 0) || (pair_counter < 0)) {
          puts("ERROR: There is an upaired '[' or ']'");
          return NULL;
        }
      }
    }
  }
  return token_buffer;
}

token *create_token_buff(char *code_buffer) {
  unsigned int code_len = strlen(code_buffer);
  unsigned int token_size = sizeof(token);
  int index;
  token *token_buffer = calloc(code_len, sizeof(token));
  if (token_buffer == NULL) {
    return NULL;
  }

  for (index = 0; index < code_len; index++) {
    switch (code_buffer[index]) {
    case 43:
      token_buffer[index] = create_token(INCREASE, index);
      break;
    case 45:
      token_buffer[index] = create_token(DECREASE, index);
      break;
    case 44:
      token_buffer[index] = create_token(STD_IN, index);
      break;
    case 46:
      token_buffer[index] = create_token(STD_OUT, index);
      break;
    case 60:
      token_buffer[index] = create_token(PTR_PREV, index);
      break;
    case 62:
      token_buffer[index] = create_token(PTR_NEXT, index);
      break;
    case 91:
      token_buffer[index] = create_token(LOOP_START, index);
      break;
    case 93:
      token_buffer[index] = create_token(LOOP_END, index);
      break;
    }
  }
  token_buffer = calculate_jump_pos(token_buffer, code_len);
  return token_buffer;
}
