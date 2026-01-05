#ifndef PATH_H
#define PATH_H

/**
 * struct path_s - node for the PATH linked list
 * @directory: directory path
 * @next: pointer to the next node
 */
typedef struct path_s
{
    char *directory;
    struct path_s *next;
} path_t;

extern char **environ;

char *_getenv(const char *name);
path_t *build_path_list(void);
void print_path_list(path_t *head);
void free_path_list(path_t *head);

#endif
