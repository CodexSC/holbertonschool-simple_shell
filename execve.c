#include <stdio.h>
/**
 * main - prints all arguments without using ac
 * @ac: argument count (unused)
 * @av: argument vector (NULL-terminated array)
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
    int i = 0;
    (void)ac; /* explicitly mark ac as unused */
    /* iterate through av until we hit NULL */
    while (av[i] != NULL)
    {
        printf("%s\n", av[i]);
        i++;
    }
    return (0);
}
10:30

Perfect! Now I can see the issue. The problem is that lines 12, 14, 17-21, and 23 are using spaces instead of tabs for indentation. Let me create the corrected version:
av.c (Fixed Indentation)
Code
What I Fixed:

All the indentation inside the main() function now uses tabs instead of spaces. The lines that were flagged (12, 14, 17-21, 23) now have proper tab indentation.
Key Changes:

    Line 12 (int i = 0;) - now uses tab
    Line 14 ((void)ac;) - now uses tab
    Lines 17-21 (the while loop and its contents) - now use tabs
    Line 23 (return (0);) - now uses tab

This should now pass the checkpatch.pl style checker without any errors or warnings! The code will work exactly the same way, but follows the Linux kernel coding style properly.

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
10:30

I can see this code has inconsistent indentation - mixing spaces and tabs. Let me fix it to use proper tab indentation throughout:
prompt.c (Fixed Indentation)
Code
What I Fixed:

    All indentation now uses tabs - Every line inside functions uses tabs (not spaces)
    Consistent formatting - All code blocks are properly indented with tabs
    Added blank lines for better readability between logical sections

Key Changes:

    Variable declarations (lines 10-12) - now use tabs
    All code inside main() - uses tabs consistently
    Code inside the if block - uses tabs for proper nesting
    Comments are aligned with their corresponding code

This should now pass the style checker without any warnings or errors! The code functionality remains exactly the same.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * split_string - splits a string into words
 * @str: the string to split
 *
 * Return: array of strings (words), NULL-terminated, or NULL on failure
 */
char **split_string(char *str)
{
char **av = NULL;
char *token;
char *str_copy;
int count = 0, i = 0;
if (str == NULL)
return (NULL);
    /* create a copy since strtok modifies the string */
str_copy = strdup(str);
if (str_copy == NULL)
return (NULL);
    /* first pass: count tokens */
token = strtok(str_copy, " \t\n");
while (token != NULL)
    {
count++;
token = strtok(NULL, " \t\n");
    }
    /* allocate array (+1 for NULL terminator) */
av = malloc(sizeof(char *) * (count + 1));
if (av == NULL)
    {
free(str_copy);
return (NULL);
    }
    /* second pass: copy tokens (need fresh copy) */
free(str_copy);
str_copy = strdup(str);
if (str_copy == NULL)
    {
free(av);
return (NULL);
    }
token = strtok(str_copy, " \t\n");
while (token != NULL)
    {
av[i] = strdup(token);
if (av[i] == NULL)
        {
            /* free previously allocated strings */
while (i > 0)
free(av[--i]);
free(av);
free(str_copy);
return (NULL);
        }
i++;
token = strtok(NULL, " \t\n");
    }
av[i] = NULL; /* NULL-terminate the array */
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
    /* split the line into words */
av = split_string(line);
if (av != NULL)
    {
        /* print each word */
i = 0;
while (av[i] != NULL)
        {
printf("av[%d]: %s\n", i, av[i]);
i++;
        }
        /* free the array */
free_array(av);
    }
free(line);
return (0);
}
10:31

This code has extensive indentation issues. Let me fix all the spacing to use proper tabs:
split_string.c (Fixed Indentation)
Code
What I Fixed:

All indentation now uses tabs consistently throughout the entire file:

    Variable declarations - All use tabs
    Function bodies - All code inside functions uses proper tab indentation
    Nested blocks - if statements, while loops use tabs for each nesting level
    Single-statement blocks - Even single statements after if use tabs
    Comments - Aligned with their corresponding code using tabs

Key Improvements:

    Consistent nesting: Each level of nesting adds one tab
    Blank lines: Added for readability between logical sections
    No spaces for indentation: Everything uses tabs as required by the style checker

This should now pass the Linux kernel style checker (checkpatch.pl) without any errors or warnings! The functionality remains identical to your original code.

========== ./split_string.c ==========
./split_string.c:52: WARNING: More than 40 lines in a function
./split_string.c:53: WARNING: More than 40 lines in a function
./split_string.c:54: WARNING: More than 40 lines in a function
./split_string.c:55: WARNING: More than 40 lines in a function
./split_string.c:56: WARNING: More than 40 lines in a function
./split_string.c:57: WARNING: More than 40 lines in a function
./split_string.c:58: WARNING: More than 40 lines in a function
./split_string.c:59: WARNING: More than 40 lines in a function
./split_string.c:60: WARNING: More than 40 lines in a function
./split_string.c:61: WARNING: More than 40 lines in a function
./split_string.c:62: WARNING: More than 40 lines in a function
./split_string.c:63: WARNING: More than 40 lines in a function
./split_string.c:64: WARNING: More than 40 lines in a function
./split_string.c:65: WARNING: More than 40 lines in a function
./split_string.c:66: WARNING: More than 40 lines in a function
./split_string.c:67: WARNING: More than 40 lines in a function
./split_string.c:68: WARNING: More than 40 lines in a function
./split_string.c:69: WARNING: More than 40 lines in a function
total: 0 errors, 18 warnings, 132 lines checked
split_string
free_array
main
codexsc@Marak
10:32

Good news - the indentation is now fixed! The warnings you're seeing are about the split_string function being too long (more than 40 lines), which is a Linux kernel coding style guideline.

Let me refactor the code to break split_string into smaller helper functions:
split_string.c (Fixed Indentation)
Code ∙ Version 2
What I Changed:

I broke the large split_string function into three smaller functions:

    count_tokens() - Counts how many tokens are in the string (20 lines)
    fill_array() - Fills the array with the actual tokens (26 lines)
    split_string() - Main function that orchestrates the splitting (37 lines)

Each function is now under 40 lines, which should eliminate all those warnings!
Benefits:

    ✅ Passes the 40-line function limit
    ✅ Better code organization and readability
    ✅ Each function has a single, clear responsibility
    ✅ Still uses proper tab indentation throughout

This refactored version should pass the style checker without warnings!

#include <stdio.h>
#include <unistd.h>
/**
 * Example 1: Basic execve with environment
 * Notice: "After execve" NEVER prints because execve replaces the process
 */
void example1(void)
{
char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
extern char **environ; /* the current environment */
printf("Before execve\n");
if (execve(argv[0], argv, environ) == -1)
    {
perror("Error");
    }
printf("After execve\n"); /* This will NEVER execute on success */
}
/**
 * Example 2: execve with custom environment
 */
void example2(void)
{
char *argv[] = {"/usr/bin/env", NULL};
char *envp[] = {"HOME=/tmp", "USER=myuser", "PATH=/bin:/usr/bin", NULL};
printf("Executing with custom environment:\n");
if (execve(argv[0], argv, envp) == -1)
    {
perror("Error");
    }
}
/**
 * Example 3: execve only returns on error
 */
void example3(void)
{
char *argv[] = {"/bin/nonexistent", NULL};
extern char **environ;
printf("Trying to execute non-existent program...\n");
if (execve(argv[0], argv, environ) == -1)
    {
perror("Error");
printf("This prints because execve FAILED\n");
    }
}
/**
 * Exercise: Simple command executor
 * This function takes a command and its arguments and executes it
 */
void execute_command(char **argv)
{
extern char **environ;
if (argv == NULL || argv[0] == NULL)
    {
fprintf(stderr, "No command provided\n");
return;
    }
printf("Executing: %s\n", argv[0]);
if (execve(argv[0], argv, environ) == -1)
    {
perror("execve");
    }
}
/**
 * main - demonstrates execve
 * Uncomment the example you want to run
 *
 * Return: Always 0.
 */
int main(void)
{
    /* Uncomment ONE of these to test */
    /* example1(); */
    /* example2(); */
    /* example3(); */
    /* Test execute_command */
char *cmd[] = {"/bin/echo", "Hello", "World", NULL};
execute_command(cmd);
return (0);
}
10:33

Let me fix the indentation in this code to use proper tabs:
execve_examples.c (Fixed Indentation)
Code
What I Fixed:

All indentation now uses tabs consistently:

    ✅ All variable declarations use tabs
    ✅ All function bodies use proper tab indentation
    ✅ All if blocks and their con


Claude is AI and can make mistakes. Please double-check responses.
#include <stdio.h>
#include <unistd.h>
/**
 * Example 1: Basic execve with environment
 * Notice: "After execve" NEVER prints because execve replaces the process
 */
void example1(void)
{
	char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
	extern char **environ; /* the current environment */

	printf("Before execve\n");
	if (execve(argv[0], argv, environ) == -1)
	{
		perror("Error");
	}
	printf("After execve\n"); /* This will NEVER execute on success */
}

/**
 * Example 2: execve with custom environment
 */
void example2(void)
{
	char *argv[] = {"/usr/bin/env", NULL};
	char *envp[] = {"HOME=/tmp", "USER=myuser", "PATH=/bin:/usr/bin", NULL};

	printf("Executing with custom environment:\n");
	if (execve(argv[0], argv, envp) == -1)
	{
		perror("Error");
	}
}

/**
 * Example 3: execve only returns on error
 */
void example3(void)
{
	char *argv[] = {"/bin/nonexistent", NULL};
	extern char **environ;

	printf("Trying to execute non-existent program...\n");
	if (execve(argv[0], argv, environ) == -1)
	{
		perror("Error");
		printf("This prints because execve FAILED\n");
	}
}

/**
 * Exercise: Simple command executor
 * This function takes a command and its arguments and executes it
 */
void execute_command(char **argv)
{
	extern char **environ;

	if (argv == NULL || argv[0] == NULL)
	{
		fprintf(stderr, "No command provided\n");
		return;
	}

	printf("Executing: %s\n", argv[0]);
	if (execve(argv[0], argv, environ) == -1)
	{
		perror("execve");
	}
}

/**
 * main - demonstrates execve
 * Uncomment the example you want to run
 *
 * Return: Always 0.
 */
int main(void)
{
	/* Uncomment ONE of these to test */
	/* example1(); */
	/* example2(); */
	/* example3(); */

	/* Test execute_command */
	char *cmd[] = {"/bin/echo", "Hello", "World", NULL};

	execute_command(cmd);
	return (0);
}
