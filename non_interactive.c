#include "main.h"

/**
 * Jag_non_interactive - entry point to non interactive mode
 * @argc: number of arguments
 * @argv: array of string
 * @env: to get enviroment
 * @pipe: its take 1 but with non interactive mode we hange it to 0
 * Return: alwayd int
*/
void Jag_non_interactive(int argc, char *argv[], char *env[], int *pipe)
{
	int bytes, err_count = 1, no_exc = 1, status = 0;
	const char *del = " ";
	size_t n_buffer = 0;
	char *buffer = NULL, command[50], *args[20], *only_command;

	*pipe = 0;
	while ((bytes = getline(&buffer, &n_buffer, stdin)) != -1)
	{
		no_exc = 1;
		Jag_trim_buffer(buffer);
		Jag_comments(&buffer, &no_exc);
		if (Jag__strcmp(buffer, "exit") == 0)
		{
			free(buffer);
			if (status == 512)
				Jag_shell_exit(status);
			exit(0);

		}
		if (Jag__strcmp(buffer, "env") == 0)
			Jag__env_non(&no_exc);
		only_command = Jag_take_only_cmd(&buffer, &no_exc, argc, argv, &err_count);
		if (*buffer && no_exc)
		{
			Jag_tok_buf(buffer, args, del, command, env);
			if (access(command, X_OK) == 0)
				Jag__fork(argc, argv, buffer, args, only_command, &status);
			else
				fprintf(stderr, "%s: %d: %s: not found\n",
						argv[argc - 1], err_count++, only_command), fflush(stdout);
		}
		free(only_command);
	}
	free(buffer);
}

