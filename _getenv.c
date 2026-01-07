#include "shell.h"

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