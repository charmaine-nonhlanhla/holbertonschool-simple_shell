#include "shell.h"

/** command_length - find the number of commands in a string
 * @string: string that will have the commands
 * return: number of commands
 */
unsigned int command_length(char *string)
{
	unsigned int i = 0, command = 0, flag = 0;

	while (string[i] != '\0')
	{
		if (string[i] != ' ')
			flag = 1;
		if ((flag && string[i + 1] == ' ')
				|| (flag && string[i + 1] == '\0'))
		{
			++command;
			flag = 0;
		}
		i++;
	}
	return (command);
}
