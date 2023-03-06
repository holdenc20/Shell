#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include "tokenize.h"

//creates a list of tokens for a given input string
char **tokenize(char *input) {
  char **tokens = malloc((1 + MAX_INPUT) * sizeof(char*));
  int i = 0;
  int j = 0;

  for(i = 0; i < strlen(input); i++) {
    if(' ' == input[i]) {
      continue;
    }
    if (input[i] == '(' || input[i] == ')' || input[i] == '<' || input[i] == '>' || input[i] == ';' || input[i] == '|') {
      tokens[j] = malloc(sizeof(char) * 2);
      tokens[j][0] = input[i];
      tokens[j][1] = '\0';
      j++;
      continue;
    }
    if (input[i] == '"') {
      int k = 0;
      char *value = malloc(sizeof(char));
      i++;
      while (input[i] != '"' && i < strlen(input)) {
        value = realloc(value, sizeof(char) * (k + 2));
        value[k] = input[i];
        k++;
        i++;
      }
      value = realloc(value, sizeof(char) * (k + 1));
      value[k] = '\0';
      tokens[j] = malloc(sizeof(char) * (k + 1));
      tokens[j] = value;
      j++;
      continue;
    }
    int k = 0;
    char *value = malloc(sizeof(char));
    while (input[i] != ' ' && input[i] != ';' && input[i] != ')' && input[i] != '(' && input[i] != '<' && input[i] != '>' && i < strlen(input)) {
      value = realloc(value, sizeof(char) * (k + 2));
      value[k] = input[i];
      k++;
      i++;
    }
    value = realloc(value, sizeof(char) * (k + 1));
  //  value[k] = '\0';
    tokens[j] = malloc(sizeof(char) * (k + 1));
    tokens[j] = value;
    j++;
    i--;
  }
  tokens[j] = NULL;
  return tokens;
}

//demo driver for tokenizer
int main(int argc, char **argv) {
  char input[MAX_INPUT];
  fgets(input, 255, stdin);

  char **tokens = tokenize(input);

  for (int i = 0; tokens[i] != NULL; i++) {
    printf("%s\n", tokens[i]);
  }

  return 0;
}
