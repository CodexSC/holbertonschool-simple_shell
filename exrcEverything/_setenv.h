#ifndef SETENV_H
#define SETENV_H

extern char **environ;

int _setenv(const char *name, const char *value, int overwrite);

#endif
