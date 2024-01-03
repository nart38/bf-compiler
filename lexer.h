#ifndef LEXER_H
#define LEXER_H

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

char *create_code_buff(char *file_dir);
token create_token(token_kind kind, unsigned int pos);
token *calculate_jump_pos(token *token_buffer, unsigned int buffer_len);
token *create_token_buff(char *code_buffer);
#endif
