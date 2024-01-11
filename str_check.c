#include "shell.h"
/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: parameter with struct info
 * @buf:  buffer
 * @p: buffer position address
 * Return: 1 when chain delimeter if not 0
 */
bool is_chain(info_s *info, char *buf, size_t *p)
{
size_t j = *p;

if (buf[j] == '|' && buf[j + 1] == '|')
{
buf[j] = 0;
j++;
info->sep_buff_kind = OR_FLAG;
}
else if (buf[j] == '&' && buf[j + 1] == '&')
{
buf[j] = 0;
j++;
info->sep_buff_kind = AND_FLAG;
}
else if (buf[j] == ';')
{
buf[j] = 0;
info->sep_buff_kind = CHAIN_FLAG;
}
else
return (false);
*p = j;
return (true);
}

/**
 * check_chain - last status checks
 * @info: parameter with struct info
 * @buf:  buffer
 * @p: buffer current position
 * @i: buffer starting position
 * @len: buffer length
 * Return: Void
 */
void check_chain(info_s *info, char *buf, size_t *p, size_t i, size_t len)
{
size_t j = *p;

if (info->sep_buff_kind == AND_FLAG)
{
if (info->status)
{
buf[i] = 0;
j = len;
}
}
if (info->sep_buff_kind == OR_FLAG)
{
if (!info->status)
{
buf[i] = 0;
j = len;
}
}
*p = j;
}

/**
 * change_v - variables replaced from tokenized string
 * @info: parameter with structure info
 * Return: 1 when replaced, 0 if not
 */
int change_v(info_s *info)
{
int i = 0;
list_s *node;

for (i = 0; info->argv[i]; i++)
{
if (info->argv[i][0] != '$' || !info->argv[i][1])
continue;
if (!_strcmp(info->argv[i], "$?"))
{
change_string(&(info->argv[i]),

_strdup(change_base(info->status, 10, 0)));

continue;
}
if (!_strcmp(info->argv[i], "$$"))
{
change_string(&(info->argv[i]),

_strdup(change_base(getpid(), 10, 0)));

continue;
}
node = node_str_start(info->env, &info->argv[i][1], '=');
if (node)
{
change_string(&(info->argv[i]),

_strdup(_strchr(node->str, '=') + 1));

continue;
}
change_string(&info->argv[i], _strdup(""));
}
return (0);
}
/**
 * change_string - changes a string
 * @old: old string address
 * @new: address for a new string
 * Return: 1 when replaced, 0 if not
 */
int change_string(char **old, char *new)
{
free(*old);
*old = new;

return (1);
}
