#ifndef MAIN_H
#define MAIN_H

extern char **environ;
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <stddef.h>

char *Jag__strcpy(char *destin, const char *source);
void Jag_trim_buffer(char *buffer);
int main(int argc, char *argv[], char *env[]);
size_t Jag__strlen(const char *str);
void Jag__print(const char *str);
char *Jag__strdup(const char *str);
void Jag__fork(int argc, char *argv[], char *buf,
		char **ave, char *only, int *status);
int Jag__strcmp(const char *string1, const char *string2);
void Jag_tok_buf(char *buf, char *args[], const char *del,
							char *str, char *env[]);
char *Jag_full_path(char *env[], char cmd[]);
void Jag__printf(const char *format, ...);
void Jag_tostring(int num);
char *Jag_path_check(char path[]);
void Jag__env(void);
void Jag_non_interactive(int argc, char *argv[],
		char *env[], int *pipe);
char *Jag_take_only_cmd(char **buffer, int *no_exc,
		int argc, char *argv[], int *n_err);
ssize_t _getline(char **line, size_t *n, FILE *stream);
void Jag_ls_check(char *ave[], char *buf, char *only);
void Jag_change_dir(char *buffer, char *cmd, int argc, char *argv[], int *n_err);
void Jag_comments(char **buf, int *no_exc);
void Jag_tok(char **buf, const char **del, char **token,
		char **str, char *args[]);
void Jag_handle_input_command(char **buffer, size_t *n_buffer,
		int *no_exc, char **only_command, int status,
		int argc, char *argv[], int *n_err);
void Jag_handle_sigint(int sig_num);
char *Jag_name_prg(int argc, char *argv[]);
void Jag_shell_exit(int status);
void Jag__env_non(int *no_exc);

#endif

