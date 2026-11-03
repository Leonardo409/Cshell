#ifndef BUILTINS_H
#define BUILTINS_H

extern char *builtin_str[];

extern int (*builtin_func[])(char **);

int _num_builtins(void);

int _cd(char **args);
int _help(char **args);
int _drop(char **args);
int _mkdir(char **args);
int _createFile(char **args);
int _list_directory(char **args);

#endif