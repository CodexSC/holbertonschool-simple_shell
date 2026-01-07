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
char *search_path(char *cmd);
void execute_cmd(char **argv, char *argv0, int line_num);

#endif
