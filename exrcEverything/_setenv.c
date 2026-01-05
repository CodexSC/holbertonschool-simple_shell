#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "_setenv.h"

/**
 * update_existing - updates an existing environment variable
 * @name: variable name
 * @value: new value
 * @name_len: length of name
 * @index: index of variable in environ
 *
 * Return: 0 on success, -1 on error
 */
int update_existing(const char *name, const char *value,
	int name_len, int index)
{
	char *new_var;

	new_var = malloc(name_len + strlen(value) + 2);
	if (new_var == NULL)
		return (-1);

	sprintf(new_var, "%s=%s", name, value);
	environ[index] = new_var;
	return (0);
}

/**
 * add_new_var - adds a new environment variable
 * @name: variable name
 * @value: variable value
 * @name_len: length of name
 * @env_count: number of existing variables
 *
 * Return: 0 on success, -1 on error
 */
int add_new_var(const char *name, const char *value,
	int name_len, int env_count)
{
	char **new_environ;
	char *new_var;
	int j;

	new_environ = malloc(sizeof(char *) * (env_count + 2));
	if (new_environ == NULL)
		return (-1);

	for (j = 0; j < env_count; j++)
		new_environ[j] = environ[j];

	new_var = malloc(name_len + strlen(value) + 2);
	if (new_var == NULL)
	{
		free(new_environ);
		return (-1);
	}

	sprintf(new_var, "%s=%s", name, value);
	new_environ[env_count] = new_var;
	new_environ[env_count + 1] = NULL;

	environ = new_environ;
	return (0);
}

/**
 * _setenv - changes or adds an environment variable
 * @name: environment variable name
 * @value: environment variable value
 * @overwrite: if 0, don't overwrite; if non-zero, overwrite
 *
 * Return: 0 on success, -1 on error
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	int i, name_len;

	if (name == NULL || value == NULL)
		return (-1);

	name_len = strlen(name);

	/* Find if the variable already exists */
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, name_len) == 0 &&
			environ[i][name_len] == '=')
		{
			if (overwrite == 0)
				return (0);
			return (update_existing(name, value, name_len, i));
		}
	}

	return (add_new_var(name, value, name_len, i));
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
