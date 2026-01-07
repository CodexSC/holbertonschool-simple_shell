#include "shell.h"
#include <unistd.h>
#include <stdio.h>

/**
 * execute_cmd - executes a command using fork and execve
 * @line: the command to execute
 * @argv0: the program name (argv[0])
 * @line_num: the line number
 *
 * Return: void
 */
void execute_cmd(char *line, char *argv0, int line_num)
{
	pid_t pid;
	char *argv[2];

	argv[0] = line;
	argv[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		execve(line, argv, environ);
		fprintf(stderr, "%s: %d: %s: not found\n", argv0, line_num, line);
		exit(127);
	}
	else
	{
		wait(NULL);
	}
}

/**
 * main - entry point for the simple shell
 * Description: Creates an infinite loop that displays a prompt, reads user
 * commands, and executes them using fork and execve. Handles EOF (Ctrl+D)
 * and exit command gracefully. Only shows prompt in interactive mode.
 *
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	char *line = NULL;
	size_t len = 0;
	int is_interactive = isatty(STDIN_FILENO);
	int line_num = 1;

	(void)argc;

	while (1)
	{
		if (is_interactive)
			printf("$ ");
		fflush(stdout);

		if (getline(&line, &len, stdin) == -1)
		{
			if (is_interactive)
				printf("\n");
			break;
		}

		line[strcspn(line, "\n")] = '\0';

		if (strcmp(line, "exit") == 0)
			break;

		if (*line == '\0')
		{
			line_num++;
			continue;
		}

		execute_cmd(line, argv[0], line_num);
		line_num++;
	}

	free(line);
	return (0);
}
