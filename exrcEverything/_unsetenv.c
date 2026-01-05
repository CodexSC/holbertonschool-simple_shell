#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

/**
 * _unsetenv - deletes an environment variable
 * @name: the name of the environment variable to delete
 *
 * Return: 0 on success, -1 on error
 */
int _unsetenv(const char *name)
{
	int i, j, name_len;

	if (name == NULL || name[0] == '\0')
		return (-1);

	name_len = strlen(name);

	/* Find the variable and remove it */
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
		{
			/* Found it, shift all subsequent variables down */
			for (j = i; environ[j] != NULL; j++)
				environ[j] = environ[j + 1];

			return (0);
		}
	}

	/* Variable not found - unsetenv returns 0 even if variable doesn't exist */
	return (0);
}

/**
 * main - test _unsetenv
 *
 * Return: Always 0
 */
int main(void)
{
	char *value;

	printf("Before unset:\n");
	value = getenv("PATH");
	printf("PATH=%s\n", value ? value : "(not found)");

	printf("\nDeleting PATH\n");
	_unsetenv("PATH");

	value = getenv("PATH");
	printf("PATH=%s\n", value ? value : "(not found)");

	printf("\nTrying to delete non-existent variable\n");
	_unsetenv("NONEXISTENT");
	printf("No error\n");

	return (0);
}
