#include "main.h"

/**
 * Jag__env - Print environment variables
 */
void Jag__env(void)
{
	char **env_ptr = environ;

	while (*env_ptr)
	{
		Jag__printf("%s\n", *env_ptr);
		env_ptr++;
	}
}

