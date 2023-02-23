/*
 * File: string_funcs1.c
 * Auth: Haile Baranto
 *       Dayo Farayola
 */
#include "main.h"
/**
 * str_len - Returns the length of a string.
 * @s: A pointer to the characters string.
 * Return: The str_len() function returns the number of bytes
 * in the string pointed by s excluding NULL terminating char.
 */
int str_len(const char *s)
{
	int len;
	len = 0;
	if (!s)
		return (len);
	for (len = 0; s[len] != '\0'; len++)
		;
	return (len);
}
/**
 * str_cpy -  The  str_cpy()  function  copies the string
 * pointed to by src, including the terminating null byte ('\0'),
 * to the buffer pointed to by dest
 * @dest: Pointer to the destination of copied string.
 * @src: Pointer to the src(string to be copied).
 * Return: Pointer to dest.
 */
char *str_cpy(char *dest, const char *src)
{
	size_t count;
	count = 0;
	while (src[count] != '\0')
	{
		dest[count] = src[count];
		count++;
	}
	dest[count] = '\0';
	return (dest);
}
/**
 * str_ncat - Concantenates two strings where n number
 *            of bytes are copied from source.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 * @n: n bytes to copy from src.
 * Return: Pointer to destination string.
 * Description: If n bytes are copied from src the size of
 * dest should be at least len(dest) + n + 1.
 */
char *str_ncat(char *dest, const char *src, size_t n)
{
	size_t dest_length;
	size_t count;
	count = 0;
	dest_length = str_len(dest);
	for (count = 0 ; count < n && src[count] != '\0' ; count++)
		dest[dest_length + count] = src[count];
	dest[dest_length + count] = '\0';
	return (dest);
}
/**
 * str_cat - Concantenates two strings.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 * Return: Pointer to destination string.
 */
char *str_cat(char *dest, const char *src)
{
	size_t count;
	int len;
	count = 0;
	len = str_len(dest);
	while (src[count] != '\0')
	{
		dest[len] = src[count];
		len++;
		count++;
	}
	dest[len] = '\0';
	return (dest);
}
