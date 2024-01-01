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
    puts("Only expect 1 argument as file directory.");
    return 1;
  }

  char *code = create_code_buff(file_dir);
  if (code == NULL)
    return 1;
  for (int i = 0; i < strlen(code); i++) {
    putchar(code[i]);
  }
  puts("");
}
