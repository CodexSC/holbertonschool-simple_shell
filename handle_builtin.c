#include "shell.h"

/**
 * handle_builtin - checks and executes built-in commands
 * @argv: argument vector
 * @argv0: program name
 * @line_num: line number
 *
 * Return: status code if built-in, -1 if not a built-in
 */
int handle_builtin(char **argv, char *argv0, int line_num)
{
	if (!argv || !argv[0])
		return (-1);

	if (strcmp(argv[0], "env") == 0)
		return (builtin_env(argv, argv0, line_num));

	return (-1);
}
