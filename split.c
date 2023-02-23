/*
 * File: split.c
 * Auth: Haile Baranto
 *       Dayo Farayola
 */

#include "main.h"

int token_length(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **str_tok(char *line, char *delim);

/**
 * str_tok - Tokenizes a string.
 * @line: The string.
 * @delim: The delimiter character to tokenize the string by.
 *
 * Return: A pointer to an array containing the tokenized words.
 */
char **str_tok(char *line, char *delim)
{
	char **pointer;
	int i = 0, tokens, t, letters, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	pointer = malloc(sizeof(char *) * (tokens + 2));
	if (!pointer)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[i] == *delim)
			i++;

		letters = token_length(line + i, delim);

		pointer[t] = malloc(sizeof(char) * (letters + 1));
		if (!pointer[t])
		{
			for (i -= 1; i >= 0; i--)
				free(pointer[i]);
			free(pointer);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			pointer[t][l] = line[i];
			i++;
		}

		pointer[t][l] = '\0';
	}
	pointer[t] = NULL;
	pointer[t + 1] = NULL;

	return (pointer);
}
/**
 * token_length - Locates the delimiter index marking the end
 *             of the first token contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The delimiter index marking the end of
 *         the intitial token pointed to be str.
 */
int token_length(char *str, char *delim)
{
	int index = 0, length = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		length++;
		index++;
	}

	return (length);
}

/**
 * count_tokens - Counts the number of delimited
 *                words contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The number of words contained within str.
 */
int count_tokens(char *str, char *delim)
{
	int i, tokens = 0, length = 0;

	for (i = 0; *(str + i); i++)
		length++;

	for (i = 0; i < length; i++)
	{
		if (*(str + i) != *delim)
		{
			tokens++;
			i += token_length(str + i, delim);
		}
	}

	return (tokens);
}
