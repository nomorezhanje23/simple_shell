#include "shell.h"

/**
 * _strcpy - string copy
 * @dest: destination
 * @src: src
 * Return: destination pointer
 */
char *_strcpy(char *dest, char *src)
{
int i = 0;

if (dest == src || src == 0)
return (dest);
while (src[i])
{
dest[i] = src[i];
i++;
}
dest[i] = 0;
return (dest);
}

/**
 * _strdup - string duplicator
 * @str: string
 * Return: duplicated string pointer
 */
char *_strdup(const char *str)
{
int length = 0;
char *ret;

if (str == NULL)
return (NULL);
while (*str++)
length++;
ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return (NULL);
for (length++; length--;)
ret[length] = *--str;
return (ret);
}

/**
 * _puts - prints an input string
 * @str: string
 * Return: Nothing
 */

void _puts(char *str)
{
int i = 0;

if (!str)
return;
while (str[i] != '\0')
{
_putchar(str[i]);
i++;
}
}

/**
 * _putchar - writes the char to stdout
 * @c: char to print
 * Return: On success 1 and on error -1
 */
int _putchar(char c)
{
static int i;
static char buf[BUFFER_SIZE_WRITE];

if (c == NEG_ONE || i >= BUFFER_SIZE_WRITE)
{
write(1, buf, i);
i = 0;
}
if (c != NEG_ONE)
buf[i++] = c;
return (1);
}
