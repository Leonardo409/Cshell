#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>


#include "builtins.h"


char *builtin_str[] = {
    "cd",
    "help",
    "drop",
    "mkdir",
    "open",
    "ld"
};

int (*builtin_func[])(char **) = {
    &_cd,
    &_help,
    &_drop,
    &_mkdir,
    &_createFile,
    &_list_directory
};

int _num_builtins(void)
{
    return sizeof(builtin_str) / sizeof(builtin_str[0]);
}

//list directory
int _list_directory(char **args){
    DIR *dir = opendir(".");

    if ( dir == NULL){
        perror("opendir");
        return 1;
    }

    struct dirent *files;

    while ((files = readdir(dir)) != NULL){
        printf("%s  ", files->d_name);
    }
    printf("\n");

    closedir(dir);

    return 1;

}


//create file
int _createFile(char **args){
    int fd = openat(AT_FDCWD, args[1], O_RDONLY | O_CREAT);
    

    if (fd == -1) {
        perror("openat");
        return 1;
    }

    close(fd);

    return 1;
}

//change directory
int _cd(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("cd");
        }
    }

    return 1;
}


//create directory
int _mkdir(char **args)
{
    if (args[1] == NULL && args[2] == NULL) {
        fprintf(stderr, "folder name and permits expected \n");
    } else {
        if (mkdir(args[1], args[2]) != 0) {
            perror("mkdir");
        }
    }

    return 1;
}


//help
int _help(char **args)
{
    int i;

    for (i = 0; i < _num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");

    return 1;
}

//exit
int _drop(char **args)
{
    return 0;
}