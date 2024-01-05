#include "shell.h"

/**
 * handle_exit - shell exit
 * @info: info parameter structure
 * Return: exit with previous status
 * (0) if info.argv[0] != "exit"
 */

int handle_exit(info_s *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = err_num(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			puts_err(info->argv[1]);
			putchar_err('\n');
			return (1);
		}
		info->error_code = err_num(info->argv[1]);
		return (-2);
	}
	info->error_code = -1;
	return (-2);
}
/**
 * handle_cd - current directory process changer
 * @info: info parameter structure
 * Return: 0
 */

int handle_cd(info_s *info)
{
char *s, *dir, buffer[1024];
int chdir_ret;

s = getcwd(buffer, 1024);
if (!s)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!info->argv[1])
{
dir = _getenv(info, "HOME=");
if (!dir)
chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (_strcmp(info->argv[1], "-") == 0)
{
if (!_getenv(info, "OLDPWD="))
{
_puts(s);
_putchar('\n');
return (1);
}
_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(info->argv[1]);

if (chdir_ret == -1)
{
print_error(info, "can't cd to ");
puts_err(info->argv[1]), putchar_err('\n');
}
else
{
_setenv(info, "OLDPWD", _getenv(info, "PWD="));
_setenv(info, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
 * handle_help - help message guide
 * @info: info parameter structure
 * Return: 0
 */

int handle_help(info_s *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);

	return (0);
}

/**
 * handle_history - history list with line numbers
 * @info: info parameter structure
 * Return: Always 0
 */

int handle_history(info_s *info)
{
	print_list(info->history);

	return (0);
}
