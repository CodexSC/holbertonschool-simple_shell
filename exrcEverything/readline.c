#include <stdio.h>
#include <stdlib.h>
/**
 * main - prints prompt, reads line, and prints it
 *
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	/* print prompt */
	printf("$ ");
	fflush(stdout); /* ensure prompt is displayed before reading */

	/* read line from stdin */
	nread = getline(&line, &len, stdin);

	/* check for EOF or error */
	if (nread == -1)
	{
		/* EOF reached (Ctrl+D) or error occurred */
		free(line);
		printf("\n");
		return (0);
	}

	/* print the line that was entered */
	printf("%s", line);

	/* free allocated memory */
	free(line);
	return (0);
}
