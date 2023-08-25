#include "shell.h"

/**
 * _eputs - Prints input string,
 * @str: String to print,
 *
 * Return: Nothing.
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - Write char c to the stderr,
 * @c: the char to be printed,
 *
 * Return: On Successful 1.
 * On error, -1 is returned, if an error is set to be appropriate.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - Writes the char c to a given fd,
 * @c: the char to be printed,
 * @fd: the file descriptor to be writen to
 *
 * Return: On Successful 1.
 * On error, -1 is returned back, and error is set to appropriate.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfd - Prints an input str,
 * @str: The str to be print to,
 * @fd: The file descriptor to be written to
 *
 * Return: The num of characters to put.
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
