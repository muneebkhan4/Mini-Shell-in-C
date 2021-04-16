#define LINE_LEN 80
#define MAX_ARGS 64
#define MAX_ARG_LEN 16
#define MAX_PATHS 9
#define MAX_PATH_LEN 96
#define WHITESPACE " .,\t\n"

#ifndef NULL
#define NULL ...
#endif

int read_command(char cmd[], char* para[]);

void print_prompt();					// print prompt on screen

void parsePath(char *dirs[]); 

char* lookupPath(char **argv, char **dir); 

struct command_t
{
  char name[30];
  int argc;
  char *argv[MAX_ARGS];

  
};
