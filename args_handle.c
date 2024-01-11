#include "shell.h"

/**
 * is_executable - finds out if command is executable
 * @info: parameter info structure
 * @path: file path
 * Return: 1 when true, 0 if false
 */
bool is_executable(info_s *info, char *path)
{
struct stat st;

(void)info;
if (!path || stat(path, &st))
return (0);

if (st.st_mode & S_IFREG)
{
return (true);
}
return (false);
}

/**
 * dup_chars - character duplicator
 * @pathstr: PATH of the string
 * @start: the start index
 * @stop: the stop index
 * Return: new buffer pointer address
 */
char *dup_chars(char *pathstr, int start, int stop)
{
static char buf[1024];
int i = 0, k = 0;

for (k = 0, i = start; i < stop; i++)
if (pathstr[i] != ':')
buf[k++] = pathstr[i];
buf[k] = 0;
return (buf);
}

/**
 * check_file_in_path - looks for command in PATH str
 * @info: parameter info structure
 * @pathstr: string path
 * @cmd: command to look
 * Return: all the  path of command when found or NULL
 */
char *check_file_in_path(info_s *info, char *pathstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;

if (!pathstr)
return (NULL);
if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (is_executable(info, cmd))
return (cmd);
}
while (1)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = dup_chars(pathstr, curr_pos, i);
if (!*path)
_strcat(path, cmd);
else
{
_strcat(path, "/");
_strcat(path, cmd);
}
if (is_executable(info, path))
return (path);
if (!pathstr[i])
break;
curr_pos = i;
}
i++;
}
return (NULL);
}
