#include <stdio.h>
#include <string.h>

extern char **environ;

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

		/* Check if the current env var starts with "name=" */
		if (strncmp(env_var, name, name_len) == 0 && env_var[name_len] == '=')
		{
			/* Return the pointer to the value (after the '=') */
			return (env_var + name_len + 1);
		}
	}

	return (NULL);
}

/**
 * main - tests the _getenv function
 *
 * Return: Always 0
 */
int main(void)
{
	char *path;
	char *home;
	char *nonexistent;

	path = _getenv("PATH");
	home = _getenv("HOME");
	nonexistent = _getenv("NONEXISTENT_VAR");

	printf("PATH: %s\n", path ? path : "(not found)");
	printf("HOME: %s\n", home ? home : "(not found)");
	printf("NONEXISTENT_VAR: %s\n", nonexistent ? nonexistent : "(not found)");

	return (0);
}
