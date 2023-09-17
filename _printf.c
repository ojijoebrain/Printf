#include "main.h"

void _buffer(char buffer[], int *buff_ind);

/**
 * _printf - the Printf function
 * @format: specified format like %s %c etc.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int i;
	int printed = 0;
	int printed_chars = 0;
	int flags;
	int width;
	int precision;
	int size;
	int buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				_buffer(buffer, &buff_ind);
			/* write(1, &format[i], 1);*/
			printed_chars++;
		}
		else
		{
			_buffer(buffer, &buff_ind);
			flags = _flags(format, &i);
			width = _width(format, &i, list);
			precision = _precision(format, &i, list);
			size = _size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * _buffer - checks if the buffer exist and prints its content
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void _buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}

