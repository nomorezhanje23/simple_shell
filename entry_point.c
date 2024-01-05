#include "shell.h"
/**
 * shell_main - the heart of the program
 * @info: the pointer with info of the shell
 * @av: string array with args
 * Return: last status of executed command
 */

int shell_main(info_s *info, char **av)
{
	ssize_t read_result = 0;
	int builtin_return_value = 0;

	while (read_result != -1 && builtin_return_value != -2)
	{
		clear_info(info);

		if (from_terminal(info))
			_puts("$ ");

		putchar_err(NEG_ONE);
		read_result = get_input(info);


		if (read_result != -1)
		{
			set_info(info, av);
			builtin_return_value = handle_builtin(info);

			if (builtin_return_value == -1)
				check_command(info);
		}

		else if (from_terminal(info))
			_putchar('\n');

		free_info(info, 0);
	}

	create_history(info);

	free_info(info, 1);
	if (!from_terminal(info) && info->status)
		exit(info->status);

	if (builtin_return_value == -2)
	{
		if (info->error_code == -1)
			exit(info->status);
		exit(info->error_code);
	}

	return (builtin_return_value);
}

/**
 * handle_builtin - locates the builtin command
 * @info: a parameter that returns info struct
 * Return: -1 when builtin is not found,
 * 0 when builtin executed successfully,
 * 1 when builtin found but not successful,
 * 2 when builtin signals exit()
 */

int handle_builtin(info_s *info)
{
	int i, builtin_return_value = -1;

	builtin_commands builtints[] = {
		{"cd", handle_cd},
		{"env", _printenv},
		{"exit", handle_exit},
		{"help", handle_help},
		{"alias", handle_alias},
		{"setenv", check_setenv},
		{"history", handle_history},
		{"unsetenv", check_unsetenv},
		{NULL, NULL}};

	for (i = 0; builtints[i].type; i++)
		if (_strcmp(info->argv[0], builtints[i].type) == 0)
		{
			info->lines++;
			builtin_return_value = builtints[i].func(info);
			break;
		}
	return (builtin_return_value);
}

/**
 * check_command - checks if the command is available in the existu=ing files
 * @info: a parameter that return info struct
 * Return: void
 */

void check_command(info_s *info)
{
	char *path = NULL;
	int i, word_count;

	info->path = info->argv[0];
	if (info->lc_flag == 1)
	{
		info->lines++;
		info->lc_flag = 0;
	}

	for (i = 0, word_count = 0; info->arg[i]; i++)
		if (!is_delimiter(info->arg[i], " \t\n"))
			word_count++;

	if (!word_count)
		return;


	path = check_file_in_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		create_process(info);
	}
	else
	{
		if ((from_terminal(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && is_executable(info, info->argv[0]))
			create_process(info);

		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * create_process - starts new process to run the command
 * @info: a parameter that return info struct
 * @info->argv array. this shares environment with the parent process
 * Return: void
 */

void create_process(info_s *info)
{
	pid_t cpid;

	cpid = fork();
	if (cpid == -1)
	{

		perror("Error:");
		return;
	}

	if (cpid == 0)
	{

		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}

	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);

			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
