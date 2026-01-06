#include "shell.h"

/**
 * execute_cmd - executes a single command using fork and execve
 * @line: the command to execute
 *
 * Return: void
 */
void execute_cmd(char *line)
{
	pid_t pid;
	char *argv[] = {line, NULL};

	pid = fork();
	if (pid == 0)
	{
		/* Child process: launch file with specified environment */
		execve(line, argv, environ);
		perror("Error");
		exit(1);
	}
	else
	{
		/* Parent process: wait for child to finish */
		wait(NULL);
	}
}

/**
 * main - represents the base of the simple shell
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		/* if CTRL+D pressed, program exits */
		if (getline(&line, &len, stdin) == -1)
			break;

		/* change the last character of 'line' (\n) by the terminator '\0' */
		line[strcspn(line, "\n")] = '\0';

		/* if 'exit' entered', program exits */
		if (strcmp(line, "exit") == 0)
			break;

		/* if ENTER pressed but line empty, restart loop */
		if (*line == '\0')
			continue;

		/* execute the command */
		execute_cmd(line);
	}
	free(line);
	return (0);
}
