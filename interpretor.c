#include "lexer.c"
#include <stdio.h>
int main() {
  char *file_dir = "aşsjdfhkşasjdhf.bf";
  char *code = parser(file_dir);
  if (code == NULL)
    puts("bro wtf");
  printf("%s\n", code);
}
