#include "shell.h"
/**
 * clear_info - clears  info_s struct
 * @info: info para structure
 */
void clear_info(info_s *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
/**
 * set_info - sets info_s struct
 * @info: info para structure
 * @av: vector args
 */
void set_info(info_s *info, char **av)
{
	int i = 0;

	info->prog_name = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
		change_alias(info);
		change_v(info);
	}
}
/**
 * free_info - info_s structure to be freed
 * @info: info parameter structure
 * @all: true when  all fields are freed
 */
void free_info(info_s *info, int all)
{
	free_vector(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->sep_buff)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		free_vector(info->environ);
		info->environ = NULL;
		bfree((void **)info->sep_buff);
		if (info->fd_read > 2)
			close(info->fd_read);
		_putchar(NEG_ONE);
	}
}
