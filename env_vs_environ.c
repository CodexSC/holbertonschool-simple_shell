#include <stdio.h>

extern char **environ;

/**
 * main - compares the address of env (3rd param) and environ (global var)
 * @ac: argument count
 * @av: argument vector
 * @env: environment variables (3rd parameter)
 *
 * Return: Always 0
 */
int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	printf("Address of env: %p\n", (void *)env);
	printf("Address of environ: %p\n", (void *)environ);

	if (env == environ)
		printf("They are the same\n");
	else
		printf("They are different\n");

	return (0);
}
