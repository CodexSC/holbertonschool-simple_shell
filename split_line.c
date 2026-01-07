#include "shell.h"

/**
 * split_line - splits a line into tokens
 * @line: the line to split
 *
 * Return: array of tokens or NULL
 */
char **split_line(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *)), *token, *copy;

	if (!tokens)
	{
		perror("malloc");
		return (NULL);
	} copy = malloc(strlen(line) + 1);
	if (!copy)
	{
		perror("malloc");
		free(tokens);
		return (NULL);
	} strcpy(copy, line);
	token = strtok(copy, " \t");
	while (token != NULL)
	{
		tokens[position] = malloc(strlen(token) + 1);
		if (!tokens[position])
		{
			perror("malloc");
			free(copy);
			return (NULL);
		} strcpy(tokens[position], token);
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
		} token = strtok(NULL, " \t");
	} tokens[position] = NULL;
	free(copy);
	return (tokens);
}
