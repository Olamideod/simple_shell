#include "shell.h"}

/**
 * _puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */

void _puts(char *str)
{
	int indi = 0;

	if (!str)
		return;
	while (str[indi] != '\0')
	{
		_putchar(str[index]);
		indi++;
	}

}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char c)
{
	static int buffer_index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
	{
		write(1, buffer, buffer_index);
		buffer_index = 0;
	}
	if (c != BUF_FLUSH)
		buffer[buffer_index++] = c;
	return (1);
}
