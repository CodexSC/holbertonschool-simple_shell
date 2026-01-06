#include "shell.h"

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
		{
			puts("");
			break;
		}

		line[strcspn(line, "\n")] = '\0';

		if (strcmp(line, "exit") == 0)
			break;

		if (*line == '\0')
			continue;

		argv[0] = line;
		argv[1] = NULL;

		pid = fork();
		if (pid == 0)
		{
			execve(line, argv, environ);
			perror("Error");
			exit(1);
		}
		wait(NULL);
	}

	free(line);
	return (0);
}
