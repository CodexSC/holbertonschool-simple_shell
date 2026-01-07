#include "shell.h"

/**
 * execute_cmd - executes a command using fork and execve
 * @argv: argument vector
 * @argv0: program name
 * @line_num: line number
 *
 * Return: exit status of command or 127 if not found
 */
int execute_cmd(char **argv, char *argv0, int line_num)
{
	pid_t pid;
	char *result;
	int is_full_path;
	int status;

	if (!argv || !argv[0])
		return (0);

	is_full_path = (strchr(argv[0], '/') != NULL);
	result = is_full_path ? argv[0] : search_path(argv[0]);

	if (!result || access(result, X_OK) != 0)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", argv0, line_num, argv[0]);
		if (!is_full_path && result)
			free(result);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		if (!is_full_path)
			free(result);
		return (1);
	}
	if (pid == 0)
	{
		execve(result, argv, environ);
		fprintf(stderr, "%s: %d: %s: not found\n", argv0, line_num, argv[0]);
		exit(127);
	}
	else
	{
		wait(&status);
		if (!is_full_path)
			free(result);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (status);
	}
}
