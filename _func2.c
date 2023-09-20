#include "main.h"

/**
* Jag__strcpy - Prints a string to stdout
* @destin: buffer to set
* @source: buffer to get from
* Return: char pointer if success or NULL
*/
char *Jag__strcpy(char *destin, const char *source)
{
	char *ptr;

	if (!destin)
		return (NULL);

	ptr = destin;
	while (*source != '\0')
	{
		*destin = *source;
		destin++;
		source++;
	}

	*destin = '\0';
	return (ptr);
}

/**
 * Jag__tokenize - Splits a string into tokens.
 * @buf: The input string to tokenize.
 * @args: The array to store the tokens.
 * @del: The delimiter to use for tokenization.
 * @str: The string to store the first token separately.
 * @env: The array of environment variables.
*/
void Jag_tok_buf(char *buf, char *args[],
							const char *del, char *str, char *env[])
{
	int i = 0, j = 0;
	char *token, *find_path = NULL, get_cmd[50], new_buf[512];

	if (buf[i] != '/' && buf[i] != '.')
	{
		while (buf[i])
		{
			if (buf[i] == ' ')
				break;
			get_cmd[i] = buf[i];
			i++;
		}
		get_cmd[i] = '\0';
		find_path = full_path(env, get_cmd);
		while (find_path[j] != '\0')
		{
			new_buf[j] = find_path[j];
			j++;
		}
		while (buf[i])
			new_buf[j++] = buf[i++];
		new_buf[j] = '\0';
		Jag__strcpy(buf, new_buf), free(find_path);
	}
	else if (buf[i] == '.' && buf[i + 1] == '/')
	{
		j = 0;
		i += 2;
		if (getcwd(new_buf, sizeof(new_buf)) == NULL)
			perror("getcwd"), exit(EXIT_FAILURE);
		while (new_buf[j])
			j++;
		new_buf[j++] = '/';
		while (buf[i])
			new_buf[j++] = buf[i++];
		new_buf[j] = '\0';
		Jag__strcpy(buf, new_buf);
	}
	tok(&buf, &del, &token, &str, args);
}

/**
*Jag__strdup - Duplicates a string
*@str: The string to duplicate
*Return: The pointer to the duplicated string, or NULL if it fails
*/
char *Jag__strdup(const char *str)
{
	size_t len = 0;
	const char *s = str;
	char *c, *copy;

	while (*s++)
	len++;

	copy = malloc((len + 1) * sizeof(char));
	if (copy != NULL)
	{
		c = copy;
		while (*str)
		*c++ = *str++;
		*c = '\0';
	}
	return (copy);
}

/**
 * Jag_tostring - Convert an integer to a string and print it
 * @num: The integer to convert and print
 *
 * This function takes an integer `num` and converts it to
 * a string representation. The resulting string is then printed
 * using the `write` function. The string is printed to the standard
 * output with a length equal to the number of digits in the integer.
 */
void Jag_tostring(int num)
{
	char str[20];
	int i, rem, len = 0, n, dec;

	n = num;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	dec = len - 1;
	for (i = 0; i < len; i++)
	{
		rem = num % 10;
		num = num / 10;
		str[dec] = rem + '0';
		dec--;
	}
	str[len] = '\0';
	write(1, str, len);
}

/**
 * Jag__printf - Custom implementation of printf
 * @format: Format string
 * @...: Variable number of arguments
 */
void Jag__printf(const char *format, ...)
{
	char *str;
	int num;
	va_list args;

	va_start(args, format);

	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			if (*format == 's')
			{
				str = va_arg(args, char*);
				write(1, str, Jag__strlen(str));
			} else if (*format == 'd')
			{
				num = va_arg(args, int);
				Jag_tostring(num);
			}
		} else
		{
			write(1, format, 1);
		}
		format++;
	}
	va_end(args);
}

