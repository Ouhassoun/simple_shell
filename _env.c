#include "main.h"

/**
 * Jag__env - Print environment variables
 */
void Jag__env(void)
{
	char **env_ptr = environ;

	while (*env_ptr)
	{
		_printf("%s\n", *env_ptr);
		env_ptr++;
	}
}
