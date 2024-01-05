#include "shell.h"

/**
 * unset_alias -  alias unset to a string
 * @info: info parameter structure
 * @str: string
 * Return: 0 always on success, 1 otherwise
 */
int unset_alias(info_s *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
ret = delete_node_at_index(&(info->alias),
get_node_index(info->alias, node_str_start(info->alias, str, -1)));
*p = c;
return (ret);
}

/**
 * set_alias - alias sets to a string
 * @info: info parameter structure
 * @str: string
 * Return: Always 0 always on success, 1 otherwise
 */
int set_alias(info_s *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - alias prints string
 * @node: node alias
 * Return: 0 always on success, 1 otherwise
 */
int print_alias(list_s *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * handle_alias - alias builtin mimics
 * @info: inof parameter structure
 * Return: 0 always
 */
int handle_alias(info_s *info)
{
	int i = 0;
	char *p = NULL;
	list_s *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_str_start(info->alias, info->argv[i], '='));
	}
	return (0);
}

/**
 * change_alias -  aliases replaced in tokenized string
 * @info: info parameter structure
 * Return: 1 when replaced, 0 otherwise
 */
int change_alias(info_s *info)
{
	int i;
	list_s *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_str_start(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}

	return (1);
}
