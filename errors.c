#include "shell.h"

/**
 * fork_fail - function that will handle for fail
 * return: nothing
 */
void fork_fail(void)
{
	perror("Error: ");
	exit(EXIT_FAILURE);
}

/**
 * build_message - a function to write and error message
 * @av: argument vector
 * @first_com: first command to print if not found
 * @count: the number of times executed
 * return: nothing
 */
void build_message(char **av, char *first_com, int count)
{
	int num = 1, cp, mult = 1;

	write(STDERR_FILENO, av[0], _strlen(av[0]));
	write(STDERR_FILENO, ":", 2);
	cp = count;

	while (cp >= 10)
	{
		cp /= 10;
		mult *= 10;
		num++;
	}

	while (num > 1)
	{
		if ((count / mult) < 10)
			_puterror((count / mult + '0'));
		else
			_puterror((count / mult) % 10 + '0');
		--num;
		mult /= 10;
	}

	_puterror(count % 10 + '0');
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, first_com, _strlen(first_com));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
* _puterror - Prints a char
*@c: character to write
*Return: int to print
*/

int _puterror(char c)
{
	return (write(STDERR_FILENO, &c, 1));
}

/**
* end_file - function to control the interrupt signal
*@buffer: buffer array created by new line
*Return: Nothing(void)
*/

void end_file(char *buffer)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	free(buffer);
	exit(0);
}
