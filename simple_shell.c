#include "shell.h"

/**
 * trim_spaces - remove leading and trailing spaces/tabs
 * @line: input string
 *
 * Return: pointer to trimmed string
 */
char *trim_spaces(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;

	if (*line == '\0')
		return (line);

	while (line[strlen(line) - 1] == ' ' ||
	       line[strlen(line) - 1] == '\t')
		line[strlen(line) - 1] = '\0';

	return (line);
}

/**
 * execute_cmd - fork and execute command
 * @cmd: command to execute
 * @argv0: program name
 * @line_num: line number
 */
void execute_cmd(char *cmd, char *argv0, int line_num)
{
	pid_t pid;
	char *argv[2];

	argv[0] = cmd;
	argv[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		execve(cmd, argv, environ);

		fprintf(stderr, "%s: %d: %s: not found\n",
		        argv0, line_num, cmd);
		exit(127);
	}
	else
	{
		wait(NULL);
	}
}

/**
 * main - simple shell
 */
int main(int argc, char *argv[])
{
	char *line = NULL;
	size_t len = 0;
	int line_num = 1;
	int interactive = isatty(STDIN_FILENO);
	char *cmd;

	(void)argc;

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		if (getline(&line, &len, stdin) == -1)
		{
			if (interactive)
				printf("\n");
			break;
		}

		line[strcspn(line, "\n")] = '\0';

		cmd = trim_spaces(line);

		if (strcmp(cmd, "exit") == 0)
			break;

		if (*cmd == '\0')
		{
			line_num++;
			continue;
		}

		execute_cmd(cmd, argv[0], line_num);
		line_num++;
	}

	free(line);
	return (0);
}
