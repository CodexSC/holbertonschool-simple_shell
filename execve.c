#include <stdio.h>
#include <unistd.h>

/**
 * Example 1: Basic execve with environment
 * Notice: "After execve" NEVER prints because execve replaces the process
 */
void example1(void)
{
	char *argv[] = {"/bin/echo", "Welcome to Execve!", NULL};
	char *envp[] = {"MYVAR=123", NULL};

	if (execve(argv[0], argv, envp) == -1)
	{
		perror("execve");
	}
	printf("After execve\n");
}

/**
 * main - demonstrates execve
 * Uncomment the example you want to run
 *
 * Return: Always 0.
 */
int main(void)
{
	example1();
	return (0);
}
