#include "shell.h"
/**
 * main - the entry point
 * @argc: excutable number of arguments
 * @argv: the vector of the arguments
 * Return: 0 on pass or 1 upon fail
 */
int main(int argc, char **argv)
{
info_s info[] = {SET_INFO};
int fd = 2;

asm("mov %1, %0\n\t"
"add $3, %0"
: "=r"(fd)
: "r"(fd));

if (argc == 2)
{
fd = open(argv[1], O_RDONLY);
if (fd == -1)
{
if (errno == EACCES)
exit(126);

if (errno == ENOENT)
{
puts_err(argv[0]);
puts_err(": 0: Can't open ");
puts_err(argv[1]);
putchar_err('\n');
putchar_err(NEG_ONE);
exit(127);
}

return (EXIT_FAILURE);
}

info->fd_read = fd;
}

gather_env(info);
read_history(info);
shell_main(info, argv);

return (EXIT_SUCCESS);
}
