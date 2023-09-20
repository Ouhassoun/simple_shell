#include "main.h"
/**
 * jag_path_exec - executes a command in the path
 * @jag_command: full path to the command
 * @jag_vars: pointer to struct of variables
 *
 * Return: 0 on success, 1 otherwise.
 */
int jag_path_exec(char *jag_command, vars_t *jag_vars)
{
	pid_t jag_child_pid;

	if (access(jag_command, X_OK) == 0)
	{
		jag_child_pid = fork();
		if (jag_child_pid == -1)
			print_error(jag_vars, NULL);
		if (jag_child_pid == 0)
		{
			if (execve(jag_command, jag_vars->av, jag_vars->env) == -1)
				print_error(jag_vars, NULL);
		}
		else
		{
			wait(&jag_vars->status);
			if (WIFEXITED(jag_vars->status))
				jag_vars->status = WEXITSTATUS(jag_vars->status);
			else if (WIFSIGNALED(jag_vars->status) && WTERMSIG(jag_vars->status) == SIGINT)
				jag_vars->status = 130;
			return (0);
		}
		jag_vars->status = 127;
		return (1);
	}
	else
	{
		print_error(jag_vars, ": Permission denied\n");
		jag_vars->status = 126;
	}
	return (0);
}

/**
 * jag_find_path - finds the PATH variable
 * @env: array of environment variables
 *
 * Return: pointer to the node that contains the PATH, or NULL on failure
 */
char *jag_find_path(char **env)
{
	char *path = "PATH=";
	unsigned int i, j;

	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; j < 5; j++)
			if (path[j] != env[i][j])
				break;
		if (j == 5)
			break;
	}
	return (env[i]);
}
/**
 * jag_check_for_path - checks if the command is in the PATH
 * @vars: variables
 *
 * Return: void
 */
void jag_check_for_path(vars_t *vars)
{
	char *path, *path_dup = NULL, *check = NULL;
	unsigned int i = 0, r = 0;
	char **path_tokens;
	struct stat buf;

	if (check_for_dir(vars->av[0]))
		r = execute_cwd_cmd(vars);
	else
	{
		path = find_path(vars->env);
		if (path != NULL)
		{
			path_dup = _strdup(path + 5);
			path_tokens = tokenize(path_dup, ":");
			for (i = 0; path_tokens && path_tokens[i]; i++, free(check))
			{
				check = _strcat(path_tokens[i], vars->av[0]);
				if (stat(check, &buf) == 0)
				{
					r = path_exec(check, vars);
					free(check);
					break;
				}
			}
			free(path_dup);
			if (path_tokens == NULL)
			{
				vars->status = 127;
				custom_exit(vars);
			}
		}
		if (path == NULL || path_tokens[i] == NULL)
		{
			print_error(vars, ": Not found\n");
			vars->status = 127;
		}
		free(path_tokens);
	}
	if (r == 1)
		custom_exit(vars);
}
/**
 * jag_execute_cwd_cmd - executes the command in the current working directory
 * @vars: pointer to struct of variables
 *
 * Return: 0 on success, 1 on failure
 */
int jag_execute_cwd_cmd(vars_t *vars)
{
	pid_t child_pid;
	struct stat buf;

	if (stat(vars->av[0], &buf) == 0)
	{
		if (access(vars->av[0], X_OK) == 0)
		{
			child_pid = fork();
			if (child_pid == -1)
				print_error(vars, NULL);
			if (child_pid == 0)
			{
				if (execve(vars->av[0], vars->av, vars->env) == -1)
					print_error(vars, NULL);
			}
			else
			{
				wait(&vars->status);
				if (WIFEXITED(vars->status))
					vars->status = WEXITSTATUS(vars->status);
				else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
					vars->status = 130;
				return (0);
			}
			vars->status = 127;
			return (1);
		}
		else
		{
			print_error(vars, ": Permission denied\n");
			vars->status = 126;
		}
		return (0);
	}
	print_error(vars, ": Not found\n");
	vars->status = 127;
	return (0);
}
/**
 * jag_check_for_dir - checks if the command is a part of a path
 * @str: command
 *
 * Return: 1 on success, 0 on failure
 */
int jag_check_for_dir(char *str)
{
	unsigned int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == '/')
			return (1);
	}
	return (0);
}
