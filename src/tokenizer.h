#include <stdio.h>

typedef enum {
  TOK_IDENTIFIER,
  TOK_INTEGER,
  TOK_FLOAT,
  TOK_EOF,
  TOK_UNKNOWN,
} TokenType;

typedef enum { TOK_FAILURE = 0, TOK_SUCCESS = 1 } TokenizeSuccess;

typedef struct {
  char *token_text;
  int token_length;
  int token_line;
  TokenType token_type;
} Token;

typedef struct {
  int line;
  int column;
  long start_idx;
  long curr_idx;
  char *input_buffer;
} TokenizerContext;

typedef struct {
  TokenizeSuccess success;
  Token *tokens[];
} TokenizationResult;

TokenizationResult tokenizeFile(FILE *file);
char *bufferizeFile(FILE *file);
TokenizerContext *initTokenizerCtxt(TokenizerContext *ctxt, char *input_buffer);
Token newToken(TokenizerContext *ctxt, TokenType type);
Token lexToken(TokenizerContext *ctxt);
char advance(TokenizerContext *ctxt);
char peek(TokenizerContext *ctxt);
char lookahead(TokenizerContext *ctxt);