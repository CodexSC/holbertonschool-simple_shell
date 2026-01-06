#include "shell.h"

/**
 * main - entry point for the simple shell
 * Description: Creates an infinite loop that displays a prompt, reads user
 * commands, and executes them using fork and execve. Handles EOF (Ctrl+D)
 * and exit command gracefully.
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	pid_t pid;
	char *argv[2];

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		if (getline(&line, &len, stdin) == -1)
			break;

		line[strcspn(line, "\n")] = '\0';

		if (strcmp(line, "exit") == 0)
			break;

		if (*line == '\0')
			continue;

		argv[0] = line;
		argv[1] = NULL;

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
	}
	if (pid == 0)
	{
		execve(line, argv, environ);
		perror("Error");
		exit(127);
	}
	else
	{
		wait(NULL);
	}
}

	free(line);
	return (0);
}
