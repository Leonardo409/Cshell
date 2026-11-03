#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "shell.h"
#include "parser.h"

#include "builtins.h"


#define _RL_BUFSIZE 1024

char *_read_line(void)
{
    int bufsize = _RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    while (1) {
        c = getchar();

        if (c == EOF) {
            free(buffer);
            exit(EXIT_SUCCESS);
        } else if (c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }

        position++;
    }
}


int _build(char **args)
{

    pid_t pid = fork();
    int i = 1;

    if(pid == -1){
        perror("fork");
        return 1;
    }

    if (pid == 0){
        
        if(execvp(args[0], &args[0]) != 0){
            perror("execvp");  
        }
    }

    waitpid(pid, NULL, 0);

    return 1;
    
}

int _execute(char **args)
{
    int i;

    if (args[0] == NULL) {
        return 1;
    }

    for (i = 0; i < _num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }   

    _build(args);
}

void _loop(void)
{
    char *line;
    char **args;
    int status;

    do {
        printf("> ");

        line = _read_line();
        args = _split_line(line);
        status = _execute(args);

        free(line);
        free(args);

    } while (status);
}