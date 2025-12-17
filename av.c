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
