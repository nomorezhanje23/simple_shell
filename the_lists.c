#include "shell.h"

/**
 * add_node_start - node is added to start list
 * @head: head node address
 * @str: field string
 * @num: history node that was used
 * Return: list size
 */
list_s *add_node_start(list_s **head, const char *str, int num)
{
list_s *new_head;

if (!head)
return (NULL);
new_head = malloc(sizeof(list_s));
if (!new_head)
return (NULL);
_memset((void *)new_head, 0, sizeof(list_s));
new_head->num = num;
if (str)
{
new_head->str = _strdup(str);
if (!new_head->str)
{
free(new_head);
return (NULL);
}
}
new_head->next = *head;
*head = new_head;
return (new_head);
}

/**
 * add_node_end - node is added at the end of list
 * @head: head node address
 * @str: string
 * @num: index node
 * Return: list sixe
 */
list_s *add_node_end(list_s **head, const char *str, int num)
{
list_s *new_node, *node;

if (!head)
return (NULL);

node = *head;
new_node = malloc(sizeof(list_s));
if (!new_node)
return (NULL);
_memset((void *)new_node, 0, sizeof(list_s));
new_node->num = num;
if (str)
{
new_node->str = _strdup(str);
if (!new_node->str)
{
free(new_node);
return (NULL);
}
}
if (node)
{
while (node->next)
node = node->next;
node->next = new_node;
}
else
*head = new_node;
return (new_node);
}

/**
 * print_list_str -string from a list to be printed
 * @h: first node pointer
 * Return: list size
 */
size_t print_list_str(const list_s *h)
{
size_t i = 0;

while (h)
{
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
i++;
}
return (i);
}

/**
 * delete_node_at_index - node deleter at given index
 * @head: first node address
 * @index: node index to be delete
 * Return: 1 when successful, 0 otherwise
 */
int delete_node_at_index(list_s **head, unsigned int index)
{
list_s *node, *prev_node;
unsigned int i = 0;

if (!head || !*head)
return (0);

if (!index)
{
node = *head;
*head = (*head)->next;
free(node->str);
free(node);
return (1);
}
node = *head;
while (node)
{
if (i == index)
{
prev_node->next = node->next;
free(node->str);
free(node);
return (1);
}
i++;
prev_node = node;
node = node->next;
}
return (0);
}

/**
 * free_list - nodes to be freed
 * @head_ptr: head pointer address
 * Return: void
 */
void free_list(list_s **head_ptr)
{
list_s *node, *next_node, *head;

if (!head_ptr || !*head_ptr)
return;
head = *head_ptr;
node = head;
while (node)
{
next_node = node->next;
free(node->str);
free(node);
node = next_node;
}
*head_ptr = NULL;
}
