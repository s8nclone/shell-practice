/*
 * File: str_funcs2.c
 * Auth: Haile Baranto
 *       Dayo Farayola
 */
#include "main.h"

char *str_chr(char *s, char c);
int str_spn(char *s, char *accept);
int str_cmp(char *s1, char *s2);
int str_ncmp(const char *s1, const char *s2, size_t n);
/**
 * str_chr - Finds a character in a string if it exists.
 * @s: The string to be searched for charachter existence.
 * @c: The character to be located.
 * Return: If c is found - a pointer to the first occurence.
 *         If c is not found - NULL.
 */
char *str_chr(char *s, char c)
{
	int index;
	while (s[index] != '\0')
	{
		if (s[index] == c)
			return (s + index);
		index++;
	}
	return (NULL);
}
/**
 * str_spn - Gets the length of a prefix substring.
 * @s: The string to be searched.
 * @accept: The prefix to be measured.
 * Return: The str_spn() function returns the number of bytes
 * in the initial segment of s which consist only of bytes from accept
 */
int str_spn(char *s, char *accept)
{
	int byte_number;
	int index;

	byte_number = 0;
	while (*s)
	{
		for (index = 0; accept[index]; index++)
		{
			if (*s == accept[index])
			{
				byte_number++;
				break;
			}
		}
		s++;
	}
	return (byte_number);
}
/**
 * str_cmp - Compares two strings.
 * @s1: The first string to be compared.
 * @s2: The second string to be compared.
 * Return:  0: if strings are equal
 *          Positive: if if the first non-matching character
 *          in str1 is greater (in ASCII) than that of str2
 *          Negative: if the first non-matching character in
 *              str1 is greater (in ASCII) than that of str2
 */
int str_cmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return (*s1 - *s2);
	return (0);
}
/**
 * str_ncmp - Compare two strings.
 * @s1: Pointer to a first string.
 * @s2: Pointer to a second string.
 * @n: The first n bytes of the strings to compare.
 * Return:  0: if the first n bytes of s1 match with s2
 *          Positive: if if the first non-matching character
 *          in str1 is greater (in ASCII) than that of str2
 *          Negative: if the first non-matching character in
 *              str1 is greater (in ASCII) than that of str2
 */
int str_ncmp(const char *s1, const char *s2, size_t n)
{
	size_t count;
	for (count = 0; s1[count] && s2[count] && count < n; count++)
	{
		if (s1[count] != s2[count])
			return (s1[count] - s2[count]);
	}
	if (count == n)
		return (0);
	else
		return (-1);
}
