#include "shell.h"

/**
 * _getenv - value of environment variable
 * @info: info parameter structure
 * @name: name of environment variable
 * Return: value of environment variable
 */

char *_getenv(info_s *info, const char *name)
{
char *p;
list_s *node = info->env;

while (node)
{
p = starts_with(node->str, name);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}

/**
 * check_setenv - environment variable checker
 * @info: info parameter structure
 * Return: 0 on success, otherwise 1
 */

int check_setenv(info_s *info)
{
if (info->argc != 3)
{
puts_err("Number of arguements is incorrect\n");
return (1);
}

if (_setenv(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}

/**
 * check_unsetenv - unsets an environment variable
 * @info: info parameter structure
 * Return: Always 0
 */
int check_unsetenv(info_s *info)
{
int x;

if (info->argc == 1)
{
puts_err("Arguements are too few\n");
return (1);
}
for (x = 1; x <= info->argc; x++)
_unsetenv(info, info->argv[x]);

return (0);
}

/**
 * gather_env - fills the env linked list
 * @info: info parameter structure
 * Return: Always 0
 */
int gather_env(info_s *info)
{
list_s *node = NULL;
size_t i;

for (i = 0; environ[i]; i++)
add_node_end(&node, environ[i], 0);
info->env = node;
return (0);
}

/**
 * _printenv - displays the current environment
 * @info: info parameter structure
 * Return: Always 0
 */
int _printenv(info_s *info)
{
print_list_str(info->env);
return (0);
}
