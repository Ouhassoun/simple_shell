#include "main.h"

/**
 * Jag__env_non - Print environment variables
 * @no_exc: num to handle continue to fork
 */
void Jag__env_non(int *no_exc)
{
	char **env_ptr = environ;
	*no_exc = 0;
	while (*env_ptr)
	{
		Jag__printf("%s\n", *env_ptr);
		env_ptr++;
	}
}

