

enum Flag { FLAG_HELP = 0b00000001 };
enum OptionResult { OPTION_HELP, ASSUMED_PATH };

int handleCommandLine(int argc, char *argv[]);
int processCmdlineOption(char *option);