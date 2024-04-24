#ifndef SHELL
#define SHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

void prompt(void);
char **read_input(char *str);
void execute(char **commands, char *buffer, char **env,
		char **argv, int count);
void freearv(char **arv);
void setfree(char *buffer, char **commands);
char *_strncpy(char *dest, char *src, int n);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
int _putchar(char c);
void free_parent(char *buffer, char **commands);
char *_getenv(const char *name, char **env);
unsigned int _strlen_const(const char *str);
char *_strncpyconst(char *dest, const char *src, int n);
void get_out(char *buffer, char **commands);
void env_get(char *buffer, char **commands, char **env);
unsigned int command_length(char *string);
void null_command(char *buffer);
void env_end(char *buffer, char **commands, char **env);
void _path(char **commands, char *buffer, char **environ, char **argv, int count);
void signal_handle(int sign);
int main(int __attribute__((unused)) argc, char **argv, char **env);
void end_file(char *buffer);
void fork_fail(void);
void build_message(char **av, char *first_com, int count);
int _puterror(char c);
unsigned int find_num(char *path);
char **store_e_variables(char *fir_com, char **environ);
char *_getenv(const char *name, char **environ);
char *_strncpcommand(char *dest, char *src, char *command, int n, int c);
void print_env(char **environ);
#endif
