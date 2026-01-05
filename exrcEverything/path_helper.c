#include <string.h>
#include <stdlib.h>
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
