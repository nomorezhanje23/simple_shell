#include "shell.h"
/**
 * _listlen - length of list
 * @h: first node pointer
 * Return: list size
 */
size_t _listlen(const list_s *h)
{
size_t i = 0;

while (h)
{
h = h->next;
i++;
}
return (i);
}

/**
 * list_to_vector - returns the list->str
 * @head: first node pointer
 * Return: string array
 */

char **list_to_vector(list_s *head)
{
list_s *node = head;
size_t i = _listlen(head), j;
char **strs;
char *str;

if (!head || !i)
return (NULL);
strs = malloc(sizeof(char *) * (i + 1));

if (!strs)
return (NULL);
for (i = 0; node; node = node->next, i++)
{
str = malloc(_strlen(node->str) + 1);
if (!str)
{
for (j = 0; j < i; j++)
free(strs[j]);
free(strs);
return (NULL);
}
str = _strcpy(str, node->str);
strs[i] = str;
}
strs[i] = NULL;
return (strs);
}

/**
 * print_list - display element list
 * @h: first node pointer
 * Return: list size
 */

size_t print_list(const list_s *h)
{
size_t i = 0;

while (h)
{
_puts(change_base(h->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
i++;
}
return (i);
}

/**
 * node_str_start - start string prefix node
 * @node: list head pointer
 * @prefix: the string
 * @c: next character
 * Return: node match or null
 */

list_s *node_str_start(list_s *node, char *prefix, char c)
{
char *p = NULL;

while (node)
{
p = starts_with(node->str, prefix);
if (p && ((c == -1) || (*p == c)))
return (node);
node = node->next;
}
return (NULL);
}

/**
 * get_node_index - finds the index node
 * @head: list head pointer
 * @node: node pointer
 * Return: index of node or -1
 */

ssize_t get_node_index(list_s *head, list_s *node)
{
size_t i = 0;

while (head)
{
if (head == node)
return (i);
head = head->next;
i++;
}
return (-1);
}
