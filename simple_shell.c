#include "shell.h"
#include <unistd.h>
#include <stdio.h>

/**
 * execute_cmd - executes a command using fork and execve
 * @line: the command to execute
 *
 * Return: void
 */
void execute_cmd(char *line)
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
		perror(line);
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
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	int is_interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (is_interactive)
			printf("($) ");
		fflush(stdout);

		if (getline(&line, &len, stdin) == -1)
		{
			if (is_interactive)
				printf("\n");
			break;
		}

		line[strcspn(line, "\n")] = '\0';

		int start = 0;
		int end = strlen(line) - 1;

		while (start <= end && (line[start] == ' ' || line[start] == '\t'))
			start++;

		while (end >= start && (line[end] == ' ' || line[end] == '\t'))
			end--;

		if (start > end)
		{
			continue;
		}

		int i = 0;
		while (start <= end)
		{
			line[i] = line[start];
			i++;
			start++;
		}
		line[i] = '\0';

		if (strcmp(line, "exit") == 0)
			break;

		if (*line == '\0')
			continue;

		execute_cmd(line);
	}

	free(line);
	return (0);
}
