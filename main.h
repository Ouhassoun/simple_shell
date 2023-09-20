#ifndef _MAIN_H_
#define _MAIN_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <signal.h>


/**
 * struct jag_variables - variables
 * @jag_av: command line arguments
 * @jag_buffer: buffer of command
 * @jag_env: environment variables
 * @jag_count: count of commands entered
 * @jag_argv: arguments at opening of shell
 * @jag_status: exit status
 * @jag_commands: double pointer to commands
 */

typedef struct jag_variables
{
	char **jag_av;
	char **jag_argv;
	char *jag_buffer;
	char **jag_commands;
	char **jag_env;
	size_t jag_count;
	int jag_status;
} vars_t;


/**
 * struct jag_builtins - struct for the builtin functions
 * @jag_name: name of builtin command
 * @jag_f: function for corresponding builtin
 */
typedef struct jag_builtins
{
	char *jag_name;
	void (*jag_f)(vars_t *);
} builtins_t;


/* Environment variable */
char **jag_create_env(char **env);
void jag_free_env(char **env);

/* Utility functions */
ssize_t jag_puts(char *str);
char *jag_strdup(char *strtodup);
int jag_strcmpr(char *strcmp1, char *strcmp2);
char *jag_strcat(char *strc1, char *strc2);
unsigned int jag_strlen(char *str);

/* Tokenization */
char **jag_tokenize(char *buf, char *delimiter);
char **jag_realloc(char **ptr, size_t *size);
char *jag_strtok(char *str, const char *delim);

/* Path Handler */
void jag_check_for_path(vars_t *vars);
char *jag_find_path(char **env);
int jag_path_exec(char *command, vars_t *vars);
int jag_execute_cwd_cmd(vars_t *vars);
int jag_check_for_dir(char *str);

/* Environment handlers */
void (*check_for_builtins(vars_t *vars))(vars_t *vars);
void jag_custom_exit(vars_t *vars);
void jag_env(vars_t *vars);
void jag_setenv(vars_t *vars);
void jag_unsetenv(vars_t *vars);

/* File Finder */
void jag_add_key(vars_t *vars);
char **jag_find_key(char **env, char *key);
char *jag_add_value(char *key, char *value);
int jag_atoi(char *str);

/* Error Handling */
void jag_print_error(vars_t *vars, char *msg);
void jag_puts2(char *str);
char *jag_uitoa(unsigned int count);


#endif

