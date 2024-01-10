#include "shell.h"

/**
 * from_terminal - mode from terminal
 * @info: info parameter structure
 * Return: 1 if successful, else 0
 */

int from_terminal(info_s *info)
{
return (isatty(STDIN_FILENO) && info->fd_read <= 2);
}

/**
 * _isalpha - alphabetic character checker
 * @c: character
 * Return: 1 if character is alphabetic else 0 if not
 */

int _isalpha(int c)
{
if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
return (1);
else
return (0);
}

/**
 * _atoi - changes string to an integer
 * @s: string
 * Return: 0 when sucessful else converted integer
 */

int _atoi(char *s)
{
int y, sign = 1, flag = 0, output;
unsigned int result = 0;

for (y = 0; s[y] != '\0' && flag != 2; y++)
{
if (s[y] == '-')
sign *= -1;
if (s[y] >= '0' && s[y] <= '9')
{
flag = 1;
result *= 10;
result += (s[y] - '0');
}
else if (flag == 1)
flag = 2;
}
if (sign == -1)
output = -result;
else
output = result;
return (output);
}
