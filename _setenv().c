#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

/**
 * _setenv - changes or adds an environment variable
 * @name: environment variable name
 * @value: environment variable value
 * @overwrite: if 0, don't overwrite existing variable; if non-zero, overwrite
 *
 * Return: 0 on success, -1 on error
 */
int _setenv(const char *name, const char *value, int overwrite)
{
    int i, name_len;
    char *new_var;

    if (name == NULL || value == NULL)
        return (-1);

    name_len = strlen(name);

    /* Find if the variable already exists */
    for (i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
        {
            /* Variable exists */
            if (overwrite == 0)
                return (0); /* Don't overwrite */

            /* Allocate new memory for the new variable */
            new_var = malloc(name_len + strlen(value) + 2);
            if (new_var == NULL)
                return (-1);

            sprintf(new_var, "%s=%s", name, value);
            environ[i] = new_var;
            return (0);
        }
    }

    /* Variable doesn't exist, need to add it */
    /* Count total environment variables */
    for (i = 0; environ[i] != NULL; i++)
        ;

    /* Allocate new environ array (one more for new var, one for NULL) */
    char **new_environ = malloc(sizeof(char *) * (i + 2));
    if (new_environ == NULL)
        return (-1);

    /* Copy existing environment variables */
    for (int j = 0; j < i; j++)
        new_environ[j] = environ[j];

    /* Create and add new variable */
    new_var = malloc(name_len + strlen(value) + 2);
    if (new_var == NULL)
    {
        free(new_environ);
        return (-1);
    }

    sprintf(new_var, "%s=%s", name, value);
    new_environ[i] = new_var;
    new_environ[i + 1] = NULL;

    environ = new_environ;
    return (0);
}

/**
 * main - test _setenv
 *
 * Return: Always 0
 */
int main(void)
{
    char *value;

    printf("Setting MY_VAR=hello\n");
    _setenv("MY_VAR", "hello", 1);

    value = getenv("MY_VAR");
    printf("MY_VAR=%s\n", value ? value : "(not found)");

    printf("\nTrying to set MY_VAR=world with overwrite=0\n");
    _setenv("MY_VAR", "world", 0);
    value = getenv("MY_VAR");
    printf("MY_VAR=%s\n", value ? value : "(not found)");

    printf("\nSetting MY_VAR=world with overwrite=1\n");
    _setenv("MY_VAR", "world", 1);
    value = getenv("MY_VAR");
    printf("MY_VAR=%s\n", value ? value : "(not found)");

    return (0);
}
