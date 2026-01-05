#include <stdio.h>

extern char **environ;

/**
 * main - prints the environment using the global variable environ
 *
 * Return: Always 0
 */
int main(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}

	return (0);
}
