#include "stdio.h"
#include "tokenizer.h"
#include "utils.h"

int main(int argc, char *argv[]) {
  int cmdline_result = handleCommandLine(argc, argv);
  if (cmdline_result == OPTION_HELP) {
    return 0;
  }

  char *filename = argv[1];

  FILE *input = fopen(filename, "r");
  tokenizeFile(input);
  return 0;
}