#include "shell.h"

/**
 * builtin_env - prints the current environment
 * @argv: argument vector (unused)
 * @argv0: program name (unused)
 * @line_num: line number (unused)
 *
 * Return: 0 on success
 */
int builtin_env(char **argv, char *argv0, int line_num)
{
	int i = 0;

	(void)argv;
	(void)argv0;
	(void)line_num;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}

	return (0);
}
