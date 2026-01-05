#include <stdio.h>
#include "path.h"

/**
 * main - entry point
 *
 * Return: Always 0
 */
int main(void)
{
	path_t *path_list = build_path_list();

	if (path_list == NULL)
	{
	    printf("Error building PATH list\n");
	    return (1);
	}

	print_path_list(path_list);
	free_path_list(path_list);

	return (0);
}
