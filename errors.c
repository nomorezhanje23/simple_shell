#include "shell.h"
/**
 * err_num - changes a string to an int
 * @s: string to be changed (converted)
 * Return: 0 when no numbers in string,
 * changed integer else -1
 *
 */
int err_num(char *s)
{
int i = 0;
unsigned long int result = 0;

if (*s == '+')
s++;
for (i = 0; s[i] != '\0'; i++)
{
if (s[i] >= '0' && s[i] <= '9')
{
result *= 10;
result += (s[i] - '0');
if (result > INT_MAX)
return (-1);
}
else
return (-1);
}
return (result);
}
/**
 * print_error - displays error message
 * @info: info parameter sructure
 * @estr: error string
 * Return: 0 when no numbers in string,
 * changed integer else -1
 */
void print_error(info_s *info, char *estr)
{
puts_err(info->prog_name);
puts_err(": ");
print_dec(info->lines, STDERR_FILENO);
puts_err(": ");
puts_err(info->argv[0]);
puts_err(": ");
puts_err(estr);
}
/**
 * print_dec - displays a decimal (integer) number (base 10)
 * @input: input
 * @fd: file descriptor
 * Return: total of characters printed
 */
int print_dec(int input, int fd)
{
int (*__putchar)(char) = _putchar;
int i, count = 0;
unsigned int _abs_, current;

if (fd == STDERR_FILENO)
__putchar = putchar_err;
if (input < 0)
{
_abs_ = -input;
__putchar('-');
count++;
}
else
_abs_ = input;
current = _abs_;
for (i = 1000000000; i > 1; i /= 10)
{

if (_abs_ / i)
{
__putchar('0' + current / i);
count++;
}
current %= i;
}
__putchar('0' + current);
count++;
return (count);
}
/**
 * change_base - change function (a clone)
 * @num: the number
 * @base: the base
 * @flags: flags arguments
 * Return: string
 */
char *change_base(long int num, int base, int flags)
{
char sign = 0;
char *ptr;
unsigned long n = num;

static char *array;
static char buffer[50];

if (!(flags & BAS_CHANGE_UNSIG) && num < 0)
{
n = -num;
sign = '-';
}
array = flags & BAS_CHANGE_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';
do {
*--ptr = array[n % base];
n /= base;
} while (n != 0);
if (sign)
*--ptr = sign;
return (ptr);
}

/**
 * handle_comments -  replaces 1st instance of '#' with '\0'
 * @buf: buffer address to be modified
 * Return: 0;
 */

void handle_comments(char *buf)
{
int i;

for (i = 0; buf[i] != '\0'; i++)
if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
{
buf[i] = '\0';
break;
}
}
