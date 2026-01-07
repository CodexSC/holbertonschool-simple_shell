#include "shell.h"
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	char *line = NULL;
	size_t len = 0;
	pid_t pid;
	int interactive;

	(void)argc;
	(void)argv;

	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			printf("$ ");
		fflush(stdout);

		if (getline(&line, &len, stdin) == -1)
		{
			if (interactive)
				printf("\n");
			break;
		}

		line[strcspn(line, "\n")] = '\0';

		if (*line == '\0')
			continue;

		if (strcmp(line, "exit") == 0)
			break;

		pid = fork();
		if (pid == 0)
		{
			char *args[] = {line, NULL};

			execve(line, args, environ);
			perror(argv[0]);
			exit(127);
		}
		else
			wait(NULL);
	}

	free(line);
	return (0);
}
