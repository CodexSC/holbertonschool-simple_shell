#include "shell.h"

/**
 * main - represents the base of the simple shell
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	pid_t pid;

	while (1)
	{
		printf("$>");
		fflush(stdout);
		/* if CTRL+D pressed OR exit written, program exits */
		if (getline(&line, &len, stdin) == -1)
			break;
		if (strcmp(line, "exit\n") == 0)
			break;
		/* change the last character of 'line' (\n) by the terminator '\0' */
		line[strcspn(line, "\n")] = '\0';
		/* if ENTER pressed but line empty, restart loop */
		if (*line == '\0')
			continue;
		/* creates a child process, if a parent exists then it becomes the child */
		pid = fork();
		if (pid == 0)
		{
			char *argv[] = {line, NULL};

			/* launch the executable found in the specified PATH with the specified environnement */
			execve(line, argv, environ);
			perror("Error");
			exit(1);
		}
		else
		{
			wait(NULL);
		}
	}
	free(line);
	return (0);
}
