#include "main.h"

/**
 * jag_create_env - create the shell environment that gets passed to main
 * @jag_env: environment passed to main
 *
 * Return: pointer to new environment
 */

char **jag_create_env(char **jag_env)
{
	char **jag_newenv = NULL;
	size_t i;

	for (i = 0; jag_env[i] != NULL; i++)
		;
	jag_newenv = malloc(sizeof(char *) * (i + 1));
	if (jag_newenv == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}
	for (i = 0; jag_env[i] != NULL; i++)
		jag_newenv[i] = _strdup(env[i]);
	jag_newenv[i] = NULL;
	return (jag_newenv);
}

/**
 * jag_free_env - free shell environment
 * @env: shell environment
 *
 * Return: void
 */

void jag_free_env(char **jag_env)
{
	unsigned int i;

	for (i = 0; jag_env[i] != NULL; i++)
		free(jag_env[i]);
	free(jag_env);
}

