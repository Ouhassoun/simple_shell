#include "main.h"

/**
* Jag__fork - Forks a child process and executes a command in it
* @argc: The argument count
* @argv: The argument vector
* @buf: The command buffer
* @ave: The argument vector for execve
* @only: The command to execute
* @status: status to exit
*/
void Jag__fork(int argc, char *argv[], char *buf, char *ave[],
		char *only, int *status)
{
	signed int pid;

	(void)argv;
	(void)argc;
	pid = fork();
	if (pid == -1)
	{
		perror("Failed to fork");
		free(buf);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		/*ls_check(ave, buf, only);*/
		execve(ave[0], ave, NULL);
		perror("execve fail");
		free(buf);
		free(only);
		exit(1);
	}
	else
	{
		wait(status);
	}
}

