#include "stdio.h"
#include "utils.h"

int main(int argc, char *argv[]) {
  int cmdline_result = handleCommandLine(argc, argv);
  if (cmdline_result == OPTION_HELP) {
    return 0;
  }

  
  return 0;
}