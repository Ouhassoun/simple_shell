#include "main.h"

/**
 * Jag_full_path - Get the full path of a command in the environment
 * @env: Array of strings containing environment variables
 * @cmd: String containing the command to search for in the environment
 *
 * Return: Pointer to the full path
 */
char *Jag_full_path(char *env[], char cmd[])
{
	char full_path[1024], *path_returned = NULL, *rslt;
	int i, j, index = 0, cmd_i = 0;

	for (i = 0; env[i]; i++)
	{
		j = 0;
		if (env[i][j] == 'P' && env[i][j + 2] == 'T' && env[i][j + 4] == '=')
		{
			j += 5;
			while (env[i][j])
			{
				full_path[index] = env[i][j];
				if (env[i][j + 1] == ':')
				{
					index++;
					full_path[index++] = '/';
					while (cmd[cmd_i])
					full_path[index++] = cmd[cmd_i++];
					cmd_i = 0;
					index--;
				}
				j++;
				index++;
			}
			full_path[index++] = '/';
			while (cmd[cmd_i])
				full_path[index++] = cmd[cmd_i++];
			full_path[index] = '\0';
		}
	}
	path_returned = path_check(full_path);
	rslt = malloc(_strlen(path_returned) + 1);
	if (!rslt)
	{
		perror("fail to allocate");
		exit(1);
	}
	_strcpy(rslt, path_returned);
	return (rslt);
}

/**
 * Jag_path_check - Check if a file exists in the specified paths
 * @path: String containing multiple paths separated by colons
 *
 * Return: Pointer to the first path
 */
char *Jag_path_check(char path[])
{
	char *token, *path_ex, *short_path, final_path[256];
	int i = 0;
	const char *delim = ":";

	token = strtok(path, delim);
	while (token)
	{
		path_ex = token;
		if (access(path_ex, F_OK) != -1)
		{
			while (path_ex[i] != '\0')
			{
				final_path[i] = path_ex[i];
				i++;
			}
			final_path[i] = '\0';
			/*path_ex  = final_path;*/
			_strcpy(path_ex, final_path);
			return (path_ex);
		}
		token = strtok(NULL, delim);
	}
	short_path = path_ex;
	return (short_path);
	}

