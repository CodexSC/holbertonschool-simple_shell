#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * count_tokens - counts the number of tokens in a string
 * @str: the string to tokenize
 *
 * Return: number of tokens
 */
int count_tokens(char *str)
{
	char *token;
	int count = 0;

	token = strtok(str, " \t\n");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " \t\n");
	}
	return (count);
}

/**
 * fill_array - fills array with tokens from string
 * @av: array to fill
 * @str: string to tokenize
 *
 * Return: 0 on success, -1 on failure
 */
int fill_array(char **av, char *str)
{
	char *token;
	int i = 0;

	token = strtok(str, " \t\n");
	while (token != NULL)
	{
		av[i] = strdup(token);
		if (av[i] == NULL)
		{
			while (i > 0)
				free(av[--i]);
			return (-1);
		}
		i++;
		token = strtok(NULL, " \t\n");
	}
	av[i] = NULL;
	return (0);
}

/**
 * split_string - splits a string into words
 * @str: the string to split
 *
 * Return: array of strings (words), NULL-terminated, or NULL on failure
 */
char **split_string(char *str)
{
	char **av = NULL;
	char *str_copy;
	int count;

	if (str == NULL)
		return (NULL);

	str_copy = strdup(str);
	if (str_copy == NULL)
		return (NULL);

	count = count_tokens(str_copy);
	free(str_copy);

	av = malloc(sizeof(char *) * (count + 1));
	if (av == NULL)
		return (NULL);

	str_copy = strdup(str);
	if (str_copy == NULL)
	{
		free(av);
		return (NULL);
	}

	if (fill_array(av, str_copy) == -1)
	{
		free(av);
		free(str_copy);
		return (NULL);
	}

	free(str_copy);
	return (av);
}

/**
 * free_array - frees a NULL-terminated array of strings
 * @av: the array to free
 */
void free_array(char **av)
{
	int i = 0;

	if (av == NULL)
		return;

	while (av[i] != NULL)
	{
		free(av[i]);
		i++;
	}
	free(av);
}

/**
 * main - test the split_string function
 *
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **av;
	int i;

	printf("$ ");
	fflush(stdout);

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		printf("\n");
		return (0);
	}

	av = split_string(line);
	if (av != NULL)
	{
		i = 0;
		while (av[i] != NULL)
		{
			printf("av[%d]: %s\n", i, av[i]);
			i++;
		}
		free_array(av);
	}

	free(line);
	return (0);
}
