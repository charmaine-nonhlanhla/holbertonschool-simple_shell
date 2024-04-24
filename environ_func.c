#include "shell.h"

/**
 * find_num - Function to find the total number of directories
 * @path: path string
 * Return: number of directories in the path
 */
unsigned int find_num(char *path)
{
	unsigned int i = 0, flag = 0, find_num = 0;

	while (path[i])
	{
		if (path[i] != ':')
			flag = 1;

		if ((flag && path[i + 1] == ':') || (flag && path[i + 1] == '\0'))
		{
			find_num++;
			flag = 0;
		}
		i++;
	}

	return (find_num);
}

/**
 * store_e_variables - Function that creates a double pointer array,
 * where stores each path directory as a pointer
 * @fir_com: first command inserted in the prompt
 * @environ: environment variables
 * Return: environment
 */
char **store_e_variables(char *first_com, char **environ)
{
	char **directories, *path_env, *directory;
	unsigned int length, i = 0;
	int dir_length, command_length;

	path_env = _getenv("PATH", environ);
	length = find_num(path_env);
	directories = malloc(sizeof(char *) * (length + 1));
	if (directories == NULL)
		return (NULL);

	directory = strtok(path_env, ":");

	while (directory != NULL)
	{
		dir_length = _strlen(directory);
		command_length = _strlen(first_com);
		directories[i] = malloc(sizeof(char *) * (dir_length + command_length + 2));
		if (directories[i] == NULL)
		{
			freearv(directories);
			return (NULL);
		}
		_strncpcommand(directories[i], directory, first_com, dir_length, command_length);
		i++;
		directory = strtok(NULL, ":");
	}

	directories[i] = NULL;

	return (directories);
}

/**
 * _getenv - Function to get the environment variable
 * @name: name of the environment variable
 * @environ: environment variables
 * Return: the value associated with the variable
 */
char *_getenv(const char *name, char **environ)
{
	char *env_value, *cp_name;
	unsigned int i = 0, length;

	length = _strlen_const(name);

	cp_name = malloc(sizeof(char) * (length + 1));
	if (cp_name == NULL)
		return (NULL);

	_strncpyconst(cp_name, name, length);

	env_value = strtok(environ[i], "=");
	while (environ[i])
	{
		if (_strcmp(env_value, cp_name))
			{																																										env_value = strtok(NULL, "\n");
			free(cp_name);
			return (env_value);
		}
		i++;
		env_value = strtok(environ[i], "=");
	}
	free(cp_name);
	return (NULL);
}

/**
 * _strncpcommand - Function that copies the path and appends a / and command
 * @dest: destination to save
 * @src: source
 * @command: command to append
 * @n: length of destination
 * @c: length of command
 * Return: address of dest
 */
char *_strncpcommand(char *dest, char *src, char *command, int n, int c)
{
	int i, j;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	
	dest[i] = '/';
	i++;

	for (j = 0; j < c && command[j] != '\0'; j++, i++)
		dest[i] = command[j];
	dest[i] = '\0';
	return (dest);
}

/**
 * print_env - Function to print all environment variables
 * @environ: environment variables for the user
 * Return: Nothing(void)
 */
void print_env(char **environ)
{
	unsigned int i = 0, length;

	while (environ[i])
	{
		length = _strlen(environ[i]);
		write(STDOUT_FILENO, environ[i], length);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
