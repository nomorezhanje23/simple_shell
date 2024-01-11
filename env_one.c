#include "shell.h"

/**
 * get_environ - environment variables string array
 * @info: info parameter structure
 * Return: environment variables strings array
 */

char **get_environ(info_s *info)
{
if (!info->environ || info->env_changed)
{
info->environ = list_to_vector(info->env);
info->env_changed = 0;
}
return (info->environ);
}

/**
 * _setenv - environment variable updater
 * @info: info parameter structure
 * @var: variable envronment to add or update
 * @value: The value of the environment variable value
 * Return: 0 on success, else 1.
 */

int _setenv(info_s *info, char *var, char *value)
{
char *buf = NULL;
list_s *node;
char *p;

if (!var || !value)
return (1);

buf = malloc(_strlen(var) + _strlen(value) + 2);
if (!buf)
return (1);

_strcpy(buf, var);
_strcat(buf, "=");
_strcat(buf, value);

node = info->env;
while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{

free(node->str);
node->str = buf;
info->env_changed = 1;
return (0);
}

node = node->next;
}

add_node_end(&(info->env), buf, 0);
free(buf);
info->env_changed = 1;
return (0);
}

/**
 * _unsetenv - environment variable is removed
 * @info: info parameter structure
 * @var: environment variable to be removed
 * Return: 1 on success, otherwise 0
 */
int _unsetenv(info_s *info, char *var)
{
list_s *node = info->env;
size_t index = 0;
char *p;

if (!node || !var)
return (0);

while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
info->env_changed = delete_node_at_index(&(info->env), index);

index = 0;
node = info->env;
continue;
}

node = node->next;
index++;
}

return (info->env_changed);
}
