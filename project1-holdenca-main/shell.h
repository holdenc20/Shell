#define _SHELL_H

typedef struct {
  char **tokens;
  char *input_file;
  char *output_file;
  int pipe_read;
  int pipe_write;
} Command;

//removes bad chars from tokens
char **remove_chars(char **tokens);

//calls the tokenize executable and parses the output
char **call_tokenize(char *input);

//removes all of the WORD_TOKENs right after input or output redirection
char **cmd_tokens_without_io(char **tokens, int start, int end);

//executes a command
int execute_command(Command command);

//parses tokens into a list of executable commands
Command *parse_tokens(char **tokens);

//changes the current directory to a given directory
int cd(char **args);

//executes all of the commands in a given file
int source(char **args);

//executes the previous command
int prev(char **args);

//displays build-in function tool tips
int help();

//frees memory of a given list of tokens
void free_tokens(char **tokens);
