#include "shell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * split_line - splits a line into tokens
 * @line: the line to split
 *
 * Return: array of tokens or NULL
 */
char **split_line(char *line)
{
	int bufsize = 64;
	int position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;
	char *copy;

	if (!tokens)
	{
		perror("malloc");
		return (NULL);
	}

	copy = malloc(strlen(line) + 1);
	if (!copy)
	{
		perror("malloc");
		free(tokens);
		return (NULL);
	}
	strcpy(copy, line);

	token = strtok(copy, " \t");
	while (token != NULL)
	{
		tokens[position] = malloc(strlen(token) + 1);
		if (!tokens[position])
		{
			perror("malloc");
			free(copy);
			return (NULL);
		}
		strcpy(tokens[position], token);
		position++;

		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("realloc");
				free(copy);
				return (NULL);
			}
		}

		token = strtok(NULL, " \t");
	}
	tokens[position] = NULL;
	free(copy);

	return (tokens);
}

/**
 * execute_cmd - executes a command using fork and execve
 * @argv: argument vector
 * @argv0: program name
 * @line_num: line number
 *
 * Return: void
 */
void execute_cmd(char **argv, char *argv0, int line_num)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		execve(argv[0], argv, environ);
		fprintf(stderr, "%s: %d: %s: not found\n", argv0, line_num, argv[0]);
		exit(127);
	}
	else
	{
		wait(NULL);
	}
}

/**
 * main - entry point for the simple shell
 * @argc: argument count
 * @argv: argument vector
 *
 * Description: Simple shell that reads commands and executes them
 *
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	char *line = NULL;
	size_t len = 0;
	int is_interactive = isatty(STDIN_FILENO);
	int line_num = 1;
	char **args;

	(void)argc;

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

		if (strcmp(line, "exit") == 0)
			break;

		if (*line == '\0')
		{
			line_num++;
			continue;
		}

		args = split_line(line);
		if (args && args[0])
			execute_cmd(args, argv[0], line_num);

		if (args)
		{
			int i = 0;
			while (args[i])
			{
				free(args[i]);
				i++;
			}
			free(args);
		}

		line_num++;
	}

	free(line);
	return (0);
}
