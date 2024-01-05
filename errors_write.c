#include "shell.h"
/**
 * puts_err - dispaly input string
 * @str: string
 * Return: Nothing
 */
void puts_err(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		putchar_err(str[i]);
		i++;
	}
}
/**
 * putchar_err - character written to stderr
 * @c: character
 * Return: 1 on success, else -1 on failure
 */
int putchar_err(char c)
{
	static int i;
	static char buf[BUFFER_SIZE_WRITE];

	if (c == NEG_ONE || i >= BUFFER_SIZE_WRITE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != NEG_ONE)
		buf[i++] = c;
	return (1);
}
/**
 * write_char - character written
 * @c: character
 * @fd: filedescriptor
 * Return: 1 on success, -1 on failure
 */
int write_char(char c, int fd)
{
	static int i;
	static char buf[BUFFER_SIZE_WRITE];

	if (c == NEG_ONE || i >= BUFFER_SIZE_WRITE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != NEG_ONE)
		buf[i++] = c;
	return (1);
}
/**
 * write_chars - display input string
 * @str: string
 * @fd: filedescriptor
 * Return: number of characters
 */
int write_chars(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += write_char(*str++, fd);
	}
	return (i);
}
