#include "shell.h"

/**
 * search_path - searches for command in PATH
 * @cmd: command name
 *
 * Return: allocated path string or NULL
 */
char *search_path(char *cmd)
{
	char *path_env;
	char *path_copy;
	char *dir;
	char full_path[1024];
	char *result;

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = malloc(strlen(path_env) + 1);
	if (!path_copy)
		return (NULL);

	strcpy(path_copy, path_env);
	dir = strtok(path_copy, ":");
	result = NULL;

	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
		if (access(full_path, X_OK) == 0)
		{
			result = malloc(strlen(full_path) + 1);
			if (result)
				strcpy(result, full_path);
			break;
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (result);
}
