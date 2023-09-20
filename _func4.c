#include "main.h"

/**
 * Jag_change_dir - Changes the current working directory
 * @buffer: The input command buffer
 * @cmd: The command name
 * @argc: num of args
 * @argv: args vector
 * @n_err: num of status
*/
void Jag_change_dir(char *buffer, char *cmd, int argc,
			char *argv[], int *n_err)
{
	char *token, *back = NULL, *now = NULL;

	now = getenv("PWD");
	back = getenv("OLDPWD");
	token = strtok(buffer, " ");
	token = strtok(NULL, " ");
	if (token == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
			perror("cd"), free(buffer), free(cmd), exit(1);
		setenv("OLDPWD", now, 1);
	}
	else if (Jag__strcmp(token, "-") == 0)
	{
		if (back == NULL)
			write(2, "cd: OLDPWD not set\n", Jag__strlen("cd: OLDPWD not set\n"));
		if (chdir(back) != 0)
			perror("cd"), free(buffer), free(cmd), exit(1);
		setenv("OLDPWD", now, 1);
		Jag__printf("%s\n", back);
	}
	else
	{
	if (chdir(token) != 0)
	{
		fprintf(stderr, "%s: %d: cd: can't cd to %s\n",
				argv[argc - 1], *n_err++, token);
	}
	setenv("OLDPWD", now, 1);
	}
}

/**
 * Jag_comments - Processes comments in a string
 * @buf: Pointer to the string buffer
 * @no_exc: Pointer to an integer indicating whether an exception occurred
 */
void Jag_comments(char **buf, int *no_exc)
{
	char *test;
	int i = 0;

	test = *buf;
	while (test[i])
	{
		if (test[0] == '#')
		{
			*no_exc = 0;
			break;
		}
		else if (test[i] == '#' && test[i - 1] == ' ')
		{
			*(*buf + i) = '\0';
			break;
		}
		i++;
	}
}

/**
 * Jag_tok - Tokenizes a string
 * @buf: Pointer to the string buffer
 * @del: Pointer to the delimiter string
 * @token: Pointer to the token string
 * @str: Pointer to the output string
 * @args: Array of arguments
 */
void Jag_tok(char **buf, const char **del, char **token,
			char **str, char *args[])
{
	int index;

	(*token) = strtok((*buf), (*del));
	index = 0;
	while ((*token))
	{
		args[index] = (*token);
		(*token) = strtok(NULL, (*del));
		index++;
	}
	args[index] = NULL;
	index = 0;
	while (args[0][index] != '\0')
	{
		(*str)[index] = args[0][index];
		index++;
	}
	(*str)[index] = '\0';
}

/**
 * Jag_handle_input_command - Handles the input command
 * @buffer: Pointer to the input command buffer
 * @n_buffer: Pointer to the size of the input command buffer
 * @no_exc: Pointer to an integer indicating whether
 * an exception occurred
 * @only_command: Pointer to the variable storing the only command
 * @status: Array of environment variables
 * @argc: num of args
 * @argv: args vector
 * @n_err: num for status
*/
void Jag_handle_input_command(char **buffer, size_t *n_buffer, int *no_exc,
		char **only_command, int status, int argc, char *argv[], int *n_err)
{
	int bytes;

	(void)status;
	bytes = getline(buffer, n_buffer, stdin);
	if (bytes == -1)
		free(*buffer), exit(1);
	if ((*buffer)[bytes - 1] == '\n')
		(*buffer)[bytes - 1] = '\0';
	Jag_trim_buffer(*buffer);
	Jag_comments(buffer, no_exc);
	if (Jag__strcmp(*buffer, "exit") == 0)
		free(*buffer), exit(0);
	if (Jag__strcmp(*buffer, "env") == 0)
	{
		*no_exc = 0;
		Jag__env();
	}
	*only_command = Jag_take_only_cmd(buffer, no_exc, argc, argv, n_err);
}

/**
 * Jag_handle_sigint - Handles the SIGINT signal
 *
 * @sig_num: The signal number
 */
void Jag_handle_sigint(int sig_num)
{
	exit(sig_num);
}

