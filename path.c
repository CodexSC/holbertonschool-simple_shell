#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "path.h"

/**
 * _getenv - gets the value of an environment variable
 * @name: the name of the environment variable
 *
 * Return: pointer to the value or NULL
 */
char *_getenv(const char *name)
{
 int i, name_len;
 char *env_var;

 if (name == NULL)
	 return (NULL);

 name_len = strlen(name);

 for (i = 0; environ[i] != NULL; i++)
 {
	 env_var = environ[i];

	 if (strncmp(env_var, name, name_len) == 0 && env_var[name_len] == '=')
		 return (env_var + name_len + 1);
 }

 return (NULL);
}

/**
 * add_node - adds a new node to the linked list
 * @head: pointer to the head of the list
 * @directory: directory to add
 *
 * Return: pointer to the new head, or NULL on failure
 */
path_t *add_node(path_t *head, char *directory)
{
 path_t *new_node, *current;

 new_node = malloc(sizeof(path_t));
 if (new_node == NULL)
	 return (NULL);

 new_node->directory = malloc(strlen(directory) + 1);
 if (new_node->directory == NULL)
 {
	 free(new_node);
	 return (NULL);
 }

 strcpy(new_node->directory, directory);
 new_node->next = NULL;

 if (head == NULL)
	 return (new_node);

 current = head;
 while (current->next != NULL)
	 current = current->next;
 current->next = new_node;

 return (head);
}

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
