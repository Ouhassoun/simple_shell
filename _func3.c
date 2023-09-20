#include "main.h"

/**
 * Jag_take_only_cmd - Extract the first command from a string
 * @buffer: Input string containing one or more commands
 * @no_exc: Number of commands
 * @n_err: Number of commands
 * @argc: num of args
 * @argv: vector agrs
 * Return: Pointer to the first command
 */
char *Jag_take_only_cmd(char **buffer, int *no_exc, int argc,
		char *argv[], int *n_err)
{
	int i = 0;
	char str_cmd[50], *cmd;

	if (Jag__strlen(*buffer) >= 50)
	{
		perror("command to long\n");
		free(*buffer), exit(1);
	}
	while ((*buffer)[i])
	{
		if ((*buffer)[i] == ' ')
			break;
		str_cmd[i] = (*buffer)[i];
		i++;
	}
	str_cmd[i] = '\0';
	cmd = malloc(Jag__strlen(str_cmd) + 1);
	if (!cmd)
	{
		perror("fail to allocate");
		exit(1);
	}
	Jag_strcpy(cmd, str_cmd);
	if (Jag__strcmp(cmd, "cd") == 0)
	{
		*no_exc = 0;
		change_dir(*buffer, cmd, argc, argv, n_err);
	}
	return (cmd);
}

/**
 * Jag_ls_check - Check if the command is 'ls' and validate directories
 * @ave: Array of command-line arguments
 * @buf: Buffer for storing command-line input
 * @only: The name of the command
 */
void Jag_ls_check(char *ave[], char *buf, char *only)
{
	const char *dir_path = NULL;
	DIR *dir;
	int index = 1;

	if (Jag__strcmp(only, "ls") == 0 || Jag__strcmp(ave[0], "/usr/bin/ls") == 0 ||
		Jag__strcmp(ave[0], "/bin/ls") == 0)
{
	while (ave[index])
	{
		if (ave[index][0] != '-')
		{
			dir_path = ave[index];
			dir = opendir(dir_path);
			if (!dir)
			{
				fprintf(stderr, "%s: cannot access '%s': No such file or directory\n",
				only, dir_path);
				if (ave[index + 1] == NULL)
					free(buf), free(only), exit(2);
			}
			if (dir)
				closedir(dir);
		}
		index++;
	}
}
}

/**
 * Jag_shell_exit - exit program
 *@status: status num to exit
*/

void Jag_shell_exit(int status)
{
	if (status == 512)
		exit(status / 256);
	exit(0);
}

