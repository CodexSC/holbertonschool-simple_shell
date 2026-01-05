#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "path.h"

/**
 * build_path_list - builds a linked list of PATH directories
 *
 * Return: pointer to the head of the linked list, or NULL on failure
 */
path_t *build_path_list(void)
{
 char *path, *path_copy, *directory;
 char *saveptr;
 path_t *head = NULL;

 path = _getenv("PATH");
 if (path == NULL)
	 return (NULL);

 path_copy = malloc(strlen(path) + 1);
 if (path_copy == NULL)
	 return (NULL);

 strcpy(path_copy, path);

 directory = strtok_r(path_copy, ":", &saveptr);
 while (directory != NULL)
 {
	 head = add_node(head, directory);
	 if (head == NULL)
	 {
		 free(path_copy);
		 return (NULL);
	 }
	 directory = strtok_r(NULL, ":", &saveptr);
 }

 free(path_copy);
 return (head);
}

/**
 * print_path_list - prints the PATH linked list
 * @head: pointer to the head of the linked list
 *
 * Return: void
 */
void print_path_list(path_t *head)
{
 path_t *current = head;

 while (current != NULL)
 {
	 printf("%s\n", current->directory);
	 current = current->next;
 }
}

/**
 * free_path_list - frees the PATH linked list
 * @head: pointer to the head of the linked list
 *
 * Return: void
 */
void free_path_list(path_t *head)
{
 path_t *current = head, *next;

 while (current != NULL)
 {
	 next = current->next;
	 free(current->directory);
	 free(current);
	 current = next;
 }
}
