#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <print_path.h>

/**
 * _getenv - gets the value of an environment variable
 * @name: the name of the environment variable
 *
 * Return: a pointer to the value of the environment variable,
 *         or NULL if the variable doesn't exist
 */
char *_getenv(const char *name)
{
	int i, name_len;
	char *env_var;

	if (name == NULL)
		return (NULL);

	name_len = strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		env_var = environ[i];

		if (strncmp(env_var, name, name_len) == 0 && env_var[name_len] == '=')
			return (env_var + name_len + 1);
	}

	return (NULL);
}

/**
 * print_path - prints each directory in PATH, one per line
 *
 * Return: void
 */
void print_path(void)
{
	char *path, *path_copy, *directory;
	char *saveptr;

	path = _getenv("PATH");
	if (path == NULL)
	{
		printf("PATH not found\n");
		return;
	}

	/* Make a copy of PATH since strtok modifies the string */
	path_copy = malloc(strlen(path) + 1);
	if (path_copy == NULL)
		return;

	strcpy(path_copy, path);

	/* strtok with ':' as delimiter to split directories */
	directory = strtok_r(path_copy, ":", &saveptr);
	while (directory != NULL)
	{
		printf("%s\n", directory);
		directory = strtok_r(NULL, ":", &saveptr);
	}

	free(path_copy);
}

/**
 * main - entry point
 *
 * Return: Always 0
 */
int main(void)
{
	print_path();
	return (0);
}
