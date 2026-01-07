#include "shell.h"

/**
 * main - entry point for the simple shell
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	char *line = NULL, **args;
	size_t len = 0;
	int is_interactive = isatty(STDIN_FILENO), line_num = 1, i;

	(void)argc;
	while (1)
	{
		if (is_interactive)
			printf("($) ");
		fflush(stdout);
		if (getline(&line, &len, stdin) == -1)
			if (is_interactive)
				printf("\n");
			break;
		line[strcspn(line, "\n")] = '\0';
		if (*line == '\0')
			line_num++;
			continue;
		args = split_line(line);
		if (args && args[0])
		{
			if (strcmp(args[0], "exit") == 0)
			{
				i = 0;
				while (args[i])
					free(args[i++]);
				free(args);
				break;
			}
			execute_cmd(args, argv[0], line_num);
		}
		if (args)
		{
			i = 0;
			while (args[i])
				free(args[i++]);
			free(args);
		} line_num++;
	} free(line);
	return (0);
}
