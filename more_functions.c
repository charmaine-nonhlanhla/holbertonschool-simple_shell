#include "shell.h"

/**
 * freearv - frees the array of pointers arv
 * @arv: array of pointers
 */
void freearv(char **arv)
{
	int i;

	for (i = 0; arv[i]; i++)
		free(arv[i]);
	free(arv);
}

/**
 * setfree - function set free when the child is not created
 * @buffer: buffer created by getline
 * @commands: array of the commands
 * Return: void
 */
void setfree(char *buffer, char **commands)
{
	if (commands == NULL)
		free_parent(buffer, commands);
	else if (_strcmp("exit", commands[0]))
		get_out(buffer, commands);
	else
		free_parent(buffer, commands);
}

/**
 * free_parent - free the buffer and commands
 * @buffer: buffer in getline
 * @commands: double pointer that will store commands inserted
 * Return: nothing
 */
void free_parent(char *buffer, char **commands)
{
	free(buffer);
	freearv(commands);
}
