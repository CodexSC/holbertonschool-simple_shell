#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

char **split_line(char *line);
char **_add_token(char **tokens, char *token, int position, int *bufsize);
char *search_path(char *cmd);
int execute_cmd(char **argv, char *argv0, int line_num);
int builtin_env(char **argv, char *argv0, int line_num);
int handle_builtin(char **argv, char *argv0, int line_num);
char *_getenv(const char *name);

#endif
