
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "tokenizer.h"
char *bufferizeFile(FILE *input_file) {
  if (!input_file)
    return NULL;
  fseek(input_file, 0, SEEK_END);
  long size = ftell(input_file);
  fseek(input_file, 0, SEEK_SET);

  char *buffer = malloc(size + 1);
  fread(buffer, 1, size, input_file);
  buffer[size] = '\0';

  return buffer;
}

TokenizerContext *initTokenizerCtxt(TokenizerContext *ctxt,
                                    char *input_buffer) {
  if (!ctxt)
    return NULL;
  ctxt->line = 0;
  ctxt->column = 0;
  ctxt->start_idx = 0;
  ctxt->curr_idx = 0;
  ctxt->input_buffer = input_buffer;

  return ctxt;
}

char peek(TokenizerContext *ctxt) { return ctxt->input_buffer[ctxt->curr_idx]; }

char advance(TokenizerContext *ctxt) {
  char ch = peek(ctxt);
  ctxt->curr_idx++;
  return ch;
}

char lookahead(TokenizerContext *ctxt) {
  return ctxt->input_buffer[ctxt->curr_idx + 1];
}

int tokenizeFile(FILE *input_file) {
  if (!input_file)
    return -1;
  TokenizerContext context;
  TokenizerContext *ctxt = &context;
  initTokenizerCtxt(ctxt, bufferizeFile(input_file));

  while (peek(ctxt) != '\0') {
    ctxt->start_idx = ctxt->curr_idx;
    char curr_char = advance(ctxt);
    if (isalpha(curr_char)) {
      while (isalpha(peek(ctxt))) {
        advance(ctxt);
      }

      long tok_len = ctxt->curr_idx - ctxt->start_idx;

      printf("Found token '%.*s' with length %ld\n", (int)tok_len,
             ctxt->input_buffer + ctxt->start_idx, tok_len);
    }
    if (isspace(curr_char)) {
      if (curr_char == '\n') {
        ctxt->line++;
        ctxt->column = 0;
      } else {
        ctxt->column++;
      }
    }
  }
  return 0;
}