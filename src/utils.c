#include "utils.h"
#include "stdio.h"
#include "string.h"

static int REQUIRED_ARGS_NUM = 2;

int handleCommandLine(int argc, char *argv[]) {
  if (argc != REQUIRED_ARGS_NUM) {
    printf("The compiler only accepts %d argument.\nUse kyucc -h to display "
           "help.\n",
           REQUIRED_ARGS_NUM - 1);
    return 0;
  }
  int process_result = processCmdlineOption(argv[1]);
  if (process_result == OPTION_HELP) {
    printf("Usage: kyucc /path/to/input/file.c\n");
  }
  return process_result;
}

int processCmdlineOption(char *option) {
  if (!strcmp(option, "-h") || !strcmp(option, "--help")) {
    return OPTION_HELP;
  }
  return ASSUMED_PATH;
}