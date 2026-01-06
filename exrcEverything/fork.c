#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/**
 * run_command - fork and execute a command
 *
 * Return: 0 on success
 */
int run_command(void)
{
	pid_t pid;
	int status;
	char *argv[] = {"/bin/echo", "Hello from HolbertonShell - HSH!", NULL};

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return (1);
	}

	if (pid == 0)
	{
		execve(argv[0], argv, environ);
		perror("execve");
		return (1);
	}

	wait(&status);

	return (0);
}

/**
 * main - entry point
 *
 * Return: Always 0
 */
int main(void)
{
	run_command();

	return (0);
}
