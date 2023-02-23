/*
 * File: environ.c
 * Auth: Haile Baranto
 *       Dayo Farayola
 */

#include "main.h"

char **copy_enviroment(void);
void free_enviroment(void);
char **get_enviroment(const char *var);

/**
 * copy_enviroment - Creates a copy of program  environment.
 *
 * Return: If an error occurs - NULL.
 *         otherwise - a double pointer to the new enviroment.
 */
char **copy_enviroment(void)
{
	char **new_enviroment;
	size_t size;
	int count;

	size = 0;
	while (environ[size])
	{
		size++;
	}
	/*Assign new enviroment on the heap*/
	new_enviroment = malloc((size + 1) * sizeof(char *));
	if (!new_enviroment)
		return (NULL);
	count = 0;
	while (environ[count])
	{
		new_enviroment[count] = malloc(str_len(environ[count]) + 1);

		if (!new_enviroment[count])
		{
			for (count--; count >= 0; count--)
				free(new_enviroment[count]);
			free(new_enviroment);
			return (NULL);
		}
		str_cpy(new_enviroment[count], environ[count]);
		count++;
	}
	new_enviroment[count] = NULL;

	return (new_enviroment);
}
/**
 * free_enviroment - Frees the environment's copy.
 */
void free_enviroment(void)
{
	int index;

	index = 0;
	while (environ[index])
	{
		free(environ[index]);
		index++;
	}
	free(environ);
}

/**
 * get_enviroment - Gets an environmental variable from the PATH.
 * @env_variable: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **get_enviroment(const char *env_variable)
{
	int index, length;

	length = str_len(env_variable);
	index = 0;
	while (environ[index])
	{
		if (str_ncmp(env_variable, environ[index], length) == 0)
			return (&environ[index]);
		index++;
	}
	return (NULL);
}
