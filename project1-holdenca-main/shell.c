#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "tokenize.h"
#include "shell.h"

char *prev_line = NULL;

int main(int argc, char **argv) {

  printf("Welcome to mini-shell.\n");

  char *input = malloc(MAX_INPUT * sizeof(char));

  while(1) {
    printf("shell $ ");
    if(fgets(input, MAX_INPUT, stdin) == NULL) {
      printf("Bye bye.\n");
      exit(0);
    }
    input[strcspn(input, "\n")] = 0;

    char **tokens = call_tokenize(input);
    //getting a lot of issues with random characters - so we will just remove them
    tokens = remove_chars(tokens);

    Command *commands = parse_tokens(tokens);

    for(int i = 0; commands[i].tokens != NULL; i++){
      //printf("%d:%s\n", i, commands[i].tokens[0]);
      if(commands[i].tokens[0] != NULL && strcmp(commands[i].tokens[0], "exit") == 0) {
//        printf("Bye bye.\n");
  //      return 0;
      } else if(commands[i].tokens[0] != NULL && strcmp(commands[i].tokens[0], "cd") == 0) {
        cd(commands[i].tokens);
      } else if(commands[i].tokens[0] != NULL && strcmp(commands[i].tokens[0], "prev") == 0) {
        prev(commands[i].tokens);
      } else if(commands[i].tokens[0] != NULL && strcmp(commands[i].tokens[0], "source") == 0) {
        source(commands[i].tokens);
      } else {
        execute_command(commands[i]);
      }
    }
    if(prev_line != NULL) {
      free(prev_line);
    }
    prev_line = malloc(strlen(input) + 1);
    strcpy(prev_line, input);

    for(int i = 0; tokens[i] != NULL; i++) {
      free(tokens[i]);
    }
    free(tokens);
  }
  free(input);
  free(prev_line);
  return 0;
}

//removes random characters in the tokens
char **remove_chars(char **tokens) {
  for(int i = 0; tokens[i] != NULL; i++){
    char *token = tokens[i];
    for(int j = 0; tokens[i][j] != '\0'; j++) {
      if(token[j] < 0 || token[j] == 127) {
        for(int k = i; tokens[k] != NULL; k++) {
          tokens[k] = tokens[k+1];
        }
        i--;
        break;
      }
    }
  }
  return tokens;
}

//calls tokenize executable
char **call_tokenize(char *input){
  int ip[2];
  int op[2];
  pipe(ip);
  pipe(op);

  pid_t pid = fork();

  if(pid == 0) {
    dup2(ip[0], STDIN_FILENO);
    dup2(op[1], STDOUT_FILENO);
    close(ip[1]);
    close(op[0]);
    execlp("./tokenize", "tokenize", NULL);
  } else {
    close(ip[0]);
    close(op[1]);
    char *in = input;
    write(ip[1], in, strlen(in));
    close(ip[1]);

    char **output = NULL;
    int output_count = 0;
    char buf[MAX_INPUT];
    int bytes_read = 0;
    while((bytes_read = read(op[0], buf, MAX_INPUT)) > 0) {
      char *token = strtok(buf, "\n");
      while(token != NULL) {
        output_count++;
        output = realloc(output, (output_count + 1) * sizeof(char*));
        output[output_count - 1] = malloc(strlen(token) + 1);
        strcpy(output[output_count - 1], token);
        token = strtok(NULL, "\n");
      }
    }
    output[output_count] = realloc(output, (output_count + 1) * sizeof(char*));
    output[output_count] = NULL;

    int status;
    waitpid(pid, &status, 0);
    close(op[0]);
    return output;
  }
  return NULL;
}

//executes a given command
int execute_command(Command command) {
  pid_t pid;
  int status;

  if((pid = fork()) == -1) {
    perror("fork");
    return -1;
  } else if(pid == 0) {
    //child process

    //input
    if(command.input_file != NULL) {
      int fd = open(command.input_file, O_RDONLY);
      if(fd == -1) {
        perror("open");
        return -1;
      }
      if(dup2(fd, STDIN_FILENO) == -1) {
        perror("dup");
        return -1;
      }
      close(fd);
    }

    //output
    if(command.output_file != NULL) {
      int fd = open(command.output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
      if(fd == -1) {
        perror("open");
        return -1;
      }
      if(dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup");
        return -1;
      }
      close(fd);
    }

    //input pipe
    if(command.pipe_read != -1) {
      if(dup2(command.pipe_read, STDIN_FILENO) == -1) {
        perror("dup2");
        return -1;
      }
      close(command.pipe_read);
    }

    //output pipe
    if(command.pipe_write != -1) {
      if(dup2(command.pipe_write, STDOUT_FILENO) == -1) {
        perror("dup2");
        return -1;
      }
      close(command.pipe_write);
    }

    //built in commands
    if(execvp(command.tokens[0], command.tokens) == -1) {
      fprintf(stderr, "%s: command not found\n", command.tokens[0]);
      return -1;
    }
  } else {
    //parent process

    //close pipes
    if(command.pipe_read != -1) {
      close(command.pipe_read);
    }

    if(command.pipe_write != -1) {
      close(command.pipe_write);
    }

    //wait for child
    if(waitpid(pid, &status, 0) == -1) {
      perror("waitpid");
      return -1;
    }
  }
}

Command* parse_tokens(char **tokens) {
  Command *commands = malloc(sizeof(Command));
  int num_cmds = 0;
  int cmd_start = 0;
  int pipe_read = -1;
  int pipe_write = -1;
  char *input_file = NULL;
  char *output_file = NULL;

  int i;
  for(i = 0; tokens[i] != NULL; i++) {
    if(tokens[i][0] == '|') {
      int cmd_len = i - cmd_start;
      commands[num_cmds].tokens = cmd_tokens_without_io(tokens, cmd_start, i);
      commands[num_cmds].tokens[cmd_len] = NULL;
      commands[num_cmds].input_file = input_file;
      commands[num_cmds].output_file = output_file;
      commands[num_cmds].pipe_read = pipe_read;

      int pipefd[2];
      if(pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);//
      }

      commands[num_cmds].pipe_write = pipefd[1];
      pipe_read = pipefd[0];
      num_cmds++;
      commands = realloc(commands, sizeof(Command) * (num_cmds + 1));
      cmd_start = i + 1;
      input_file = NULL;
      output_file = NULL;
    }

    if(tokens[i][0] == '<'){
      input_file = tokens[i+1];
      i++;
    }

    if(tokens[i][0] == '>') {
      output_file = tokens[i+1];
      i++;
    }

    if(tokens[i][0] == ';') {
      int cmd_len = i - cmd_start;
      commands[num_cmds].tokens = cmd_tokens_without_io(tokens, cmd_start, i);
      commands[num_cmds].tokens[cmd_len] = NULL;
      commands[num_cmds].input_file = input_file;
      commands[num_cmds].output_file = output_file;
      commands[num_cmds].pipe_read = pipe_read;
      commands[num_cmds].pipe_write = pipe_write;
      num_cmds++;
      cmd_start = i + 1;
      commands = realloc(commands, sizeof(Command) * (num_cmds + 1));
      input_file = NULL;
      output_file = NULL;
      pipe_read = -1;
      pipe_write = -1;
    }
  }

  //the last command
  int cmd_len = i - cmd_start;
  commands[num_cmds].tokens = cmd_tokens_without_io(tokens, cmd_start, i);
  commands[num_cmds].tokens[cmd_len] = NULL;
  commands[num_cmds].input_file = input_file;
  commands[num_cmds].output_file = output_file;
  commands[num_cmds].pipe_read = pipe_read;
  commands[num_cmds].pipe_write = pipe_write;
  num_cmds++;
  commands = realloc(commands, sizeof(Command) * (num_cmds + 1));

  //NULL command at end
  commands[num_cmds].tokens = malloc(sizeof(char *));
  commands[num_cmds].tokens[0] = NULL;
  commands[num_cmds].input_file = NULL;
  commands[num_cmds].output_file = NULL;
  commands[num_cmds].pipe_read = -1;
  commands[num_cmds].pipe_write = -1;

  return commands;
}

//removes the inputs and output < > and file locations
char **cmd_tokens_without_io(char **tokens, int start, int end) {
  int cmd_len = end - start;
  char **cmd_tokens = malloc(sizeof(char *) * (cmd_len + 2));
  int cmd_token_index = 0;
  for(int j = start; j < end; j++) {
    if(tokens[j][0] == '<' || tokens[j][0] == '>') {
      j++;
    //  if(cmd_token_index > 0) {
      //  free(cmd_tokens[cmd_token_index - 1]);
        //cmd_token_index--;
      //}
    } else{
      cmd_tokens[cmd_token_index] = malloc(sizeof(char) * (strlen(tokens[j]) + 1));
      strcpy(cmd_tokens[cmd_token_index], tokens[j]);
      cmd_token_index++;
    }
  }
  cmd_tokens[cmd_token_index] = NULL;
  return remove_chars(cmd_tokens);
   // return cmd_tokens;
}

//changes the directory
int cd(char **args) {
  if(args[1] == NULL) {
    fprintf(stderr, "Expected argument to cd\n");
  } else {
    if(chdir(args[1]) != 0) {
      perror("cd");
    }
  }
  return 1;
}

//reads from a given text file and executes each of the lines as a command
int source(char **args) {
  if(args[1] == NULL) {
    fprintf(stderr, "source: expected argument to source\n");
  } else {
    int fd = open(args[1], O_RDONLY);

    if(fd == -1) {
      perror("source: failed to open file");
      return 1;
    } else {
      char buffer[MAX_INPUT];
      char nextChar[1];
      ssize_t bytes_read;
      int length = 0;
      while((bytes_read = read(fd, nextChar, 1)) > 0) {
        if(nextChar[0] == '\n'){
          buffer[length] = '\0';
          char **tokens = call_tokenize(buffer);
          Command *commands = parse_tokens(tokens);
          for(int i = 0; commands[i].tokens != NULL; i++){
            execute_command(commands[i]);
          }
          length = 0;
        }
        else {
          buffer[length] = nextChar[0];
          length++;
        }
      }
      close(fd);
    }
  }
  return 1;
}

//executes the previous command entered
int prev(char **args) {
  if(prev_line == NULL) {
    fprintf(stderr, "prev: no previous command line\n");
  } else {
    printf("%s\n", prev_line);
    char **tokens = call_tokenize(prev_line);

    Command *commands = parse_tokens(tokens);
    for(int i = 0; commands[i].tokens != NULL; i++) {
      execute_command(commands[i]);
    }
  }
  return 1;
}

int help() {
  printf("The following built-in commands are available:\n");
  printf("cd <directory>: change the current directory to the specified directory\n");
  printf("source <filename>: execute commands from the specified file\n");
  printf("prev: execute the previous command\n");
  printf("help: display this help message\n");
  return 1;
}

//frees tokens from memory
void free_tokens(char **tokens) {
  for(int i = 0; tokens[i] != NULL; i++) {
    free(tokens[i]);
  }
  free(tokens);
}
