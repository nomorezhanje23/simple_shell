#include "shell.h"
/**
 * words_count - number of words in a string
 * @str: string
 * @separators: separate delemeters
 * @arr: word length array pointer
 * Return: the number of words
 */
int words_count(char *str, char *separators, unsigned int *arr)
{
unsigned int c, d, word_len = 1;
unsigned int word_count = 0;
char *str_copy = str;
bool start = false, delimiter;

if (!str)
return (0);
while (!start)
for (d = 0; separators[d]; d++)
{
if (*str_copy == separators[d])
str_copy++;
else
start = true;
		}
if (!*(str_copy + 1))
{
arr[0] = 1;
return (1);
}
for (c = 1; str_copy[c]; c++)
{
delimiter = is_delimiter(str_copy[c], separators);
if (delimiter && !(is_delimiter(str_copy[c - 1], separators)))
{
arr[word_count] = word_len;
word_count++;
}
if ((!str_copy[c + 1]) && !delimiter)
{
word_len++;
arr[word_count] = word_len;
word_count++;
break;
}
if (!delimiter)
word_len++;
else
word_len = 0;
}
return (word_count);
}
