#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

#define SHELL_TOK_BUFSIZE 64
#define SHELL_TOK_DELIM " \t\r\n\a"

char **_split_line(char *line)
{
    int bufsize = SHELL_TOK_BUFSIZE;
    int position = 0;

    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) {
        fprintf(stderr, "SHELL: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, SHELL_TOK_DELIM);

    while (token != NULL) {
        tokens[position] = token;
        position++;

        token = strtok(NULL, SHELL_TOK_DELIM);
    }

    tokens[position] = NULL;

    return tokens;
}