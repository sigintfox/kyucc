
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
  ctxt->column++;
  return ch;
}

char lookahead(TokenizerContext *ctxt) {
  return ctxt->input_buffer[ctxt->curr_idx + 1];
}

Token newToken(TokenizerContext *ctxt, TokenType type) {
  Token result;
  result.token_length = ctxt->curr_idx - ctxt->start_idx;
  result.token_line = ctxt->line;
  result.token_text = ctxt->input_buffer + ctxt->start_idx;
  result.token_type = type;
  return result;
}

Token lexToken(TokenizerContext *ctxt) {
  while (peek(ctxt) != '\0') {
    ctxt->start_idx = ctxt->curr_idx;
    char curr_char = advance(ctxt);

    if (isspace(curr_char)) {
      if (curr_char == '\n') {
        ctxt->line++;
        ctxt->column = 0;
      }
      continue;
    }
    if (isalpha(curr_char) || curr_char == '_') {
      while (isalnum(peek(ctxt)) || peek(ctxt) == '_') {
        advance(ctxt);
      }
      return newToken(ctxt, TOK_IDENTIFIER);
    }
    if (isdigit(curr_char)) {
      while (isdigit(peek(ctxt))) {
        advance(ctxt);
      }
      if (peek(ctxt) == '.') {
        advance(ctxt);
        while (isdigit(peek(ctxt))) {
          advance(ctxt);
        }
        return newToken(ctxt, TOK_FLOAT);
      }
      return newToken(ctxt, TOK_INTEGER);
    }
    return newToken(ctxt, TOK_UNKNOWN);
  }
  return newToken(ctxt, TOK_EOF);
}

TokenizationResult tokenizeFile(FILE *input_file) {
  TokenizationResult result;
  result.success = TOK_SUCCESS;
  if (!input_file) {
    result.success = TOK_FAILURE;
    return result;
  }

  TokenizerContext context;
  TokenizerContext *ctxt = &context;
  initTokenizerCtxt(ctxt, bufferizeFile(input_file));

  Token candidate;
  while ((candidate = lexToken(ctxt)).token_type != TOK_EOF) {
    printf("Found token '%.*s' of length '%d'\n", candidate.token_length,
           candidate.token_text, candidate.token_length);
  }

  return result;
}