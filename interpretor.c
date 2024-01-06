#include "lexer.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char *file_dir;
  switch (argc) {
  case 2:
    file_dir = argv[1];
    break;
  default:
    puts("Interpretor was expecting only 1 argument as file directory.");
    return 1;
  }

  char *code = create_code_buff(file_dir);
  if (code == NULL)
    return 1;
  token *token_buff = create_token_buff(code);
  if (token_buff == NULL)
    return 1;

  // Begin evaluateing token_buff
  char mem_array[30000] = {0};
  unsigned int mem_ptr = 0;
  int code_len = strlen(code);
  int i;

  for (i = 0; i < code_len; i++) {
    switch (token_buff[i].kind) {
    case INCREASE:
      mem_array[mem_ptr]++;
      break;
    case DECREASE:
      mem_array[mem_ptr]--;
      break;
    case PTR_NEXT:
      mem_ptr++;
      break;
    case PTR_PREV:
      mem_ptr--;
      break;
    case STD_IN:
      mem_array[mem_ptr] = getchar();
      break;
    case STD_OUT:
      putchar(mem_array[mem_ptr]);
      break;
    case LOOP_START:
      // Not sure but there is not much to do with LOOP_START
      i = token_buff[i].jmp_position - 1;
      break;
    case LOOP_END:
      if (mem_array[mem_ptr != 0]) {
        i = token_buff[i].jmp_position;
      }
      break;
    }
  }
  return 0;
}
