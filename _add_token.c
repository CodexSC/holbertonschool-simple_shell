#include "shell.h"

/**
 * _add_token - adds a token to the tokens array with reallocation if needed
 * @tokens: array of tokens
 * @token: token to add
 * @position: current position in array
 * @bufsize: pointer to buffer size
 *
 * Return: pointer to tokens array or NULL on failure
 */
char **_add_token(char **tokens, char *token, int position, int *bufsize)
{
	tokens[position] = malloc(strlen(token) + 1);
	if (!tokens[position])
	{
		perror("malloc");
		return (NULL);
	}
	strcpy(tokens[position], token);

	if (position + 1 >= *bufsize)
	{
		*bufsize += 64;
		tokens = realloc(tokens, *bufsize * sizeof(char *));
		if (!tokens)
		{
			perror("realloc");
			return (NULL);
		}
	}

	return (tokens);
}
