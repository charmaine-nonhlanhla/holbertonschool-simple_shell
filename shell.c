#include "shell.h"

/**
 * prompt - displays prompt
 *
 * Return: void
 */
void prompt(void)
{
	char *str = "$ ";

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, str, 2);
}

/**
 * read_input - gets and parses a line from the prompt
 * @str: line to parse
 *
 * Return: Array of tokens to be executed
 */
char **read_input(char *str)
{
	char *token, **holder;
	unsigned int length;
	int i = 0;

	str[_strlen(str) - 1] = '\0';
	length = command_length(str);
	if (length == 0)
		return (NULL);
	holder = malloc((sizeof(char *) * (length + 1)));
	if (holder == NULL)
		return (NULL);
	token = strtok(str, " ");
	while (token != NULL)
	{
		holder[i] = malloc(_strlen(token) + 1);
		if (holder[i] == NULL)
		{
			freearv(holder);
			return (NULL);
		}
		strncpy(holder[i], token, _strlen(token) + 1);
		token = strtok(NULL, " ");
		i++;
	}
	holder[i] = NULL;
	return (holder);
}

/**
* execute - Function to verify and execute every command
*@commands: command get
*@buffer: command in getline
*@env: enviroment variable
*@argv: argument counter
*@count: number of times that executed
*Return: Nothing(void)
*/

void execute(char **commands, char *buffer, char **env, char **argv, int count)
{
	struct stat fileStat;

	if (commands == NULL)
		null_command(buffer);
	else if (_strcmp("exit", commands[0]))
		get_out(buffer, commands);
	else if (_strcmp("env", commands[0]))
		env_end(buffer, commands, env);
	else if (stat(commands[0], &fileStat) == 0)
		execve(commands[0], commands, NULL);
	else
		_path(commands, buffer, env, argv, count);
}

/**
 * signal_handle - handles signals and writes the prompt
 * @sign: signal to handle
 * Return: void
 */
void signal_handle(int sign)
{
	(void)sign;
	write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 * main - entry point
 * @argc: argument count
 * @argv: array of arguments
 * @env: pointer to the list of env variables
 *
 * Return: 0 on success or 1 if error
 */
int main(int __attribute__((unused)) argc, char **argv, char **env)
{
	size_t len = 0;
	ssize_t chars;
	pid_t pid;
	char **tokens, *line = NULL;
	int i = 0, status;

	(void)argc;
	prompt();
	for (; (chars = getline(&line, &len, stdin)); )
	{
		signal(SIGINT, signal_handle); 
		if (chars == EOF)
			end_file(line);
		i++;
		tokens = read_input(line);
		pid = fork();
		if (pid == -1)
			fork_fail();
		if (pid == 0)
			execute(tokens, line, env, argv, i);
		else
		{
			wait(&status);
			setfree(line, tokens);
		}
		len = 0, line = NULL;
		prompt();
	}
	if (chars == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
