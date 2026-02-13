#include <stdio.h>

enum TokenType {
  TOK_IDENTIFIER,
  TOK_UNKNOWN,
};

enum TokenizeSuccess { TOK_FAILURE = 0, TOK_SUCCESS = 1 };

typedef struct {
  char *token_text;
  int token_line;
  enum TokenType token_type;
} Token;

typedef struct {
  int line;
  int column;
  long start_idx;
  long curr_idx;
  char *input_buffer;
} TokenizerContext;

typedef struct {
  enum TokenizeSuccess success;
  Token *tokens[];
} TokenizationResult;

int tokenizeFile(FILE *file);
char *bufferizeFile(FILE *file);
TokenizerContext *initTokenizerCtxt(TokenizerContext *ctxt, char *input_buffer);
Token *createToken(TokenizerContext *ctxt);
char advance(TokenizerContext *ctxt);
char peek(TokenizerContext *ctxt);
char lookahead(TokenizerContext *ctxt);