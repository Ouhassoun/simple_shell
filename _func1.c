#include "main.h"

/**
* Jag__strcmp - function to compare
* @string1: The input string
* @string2: The input string
* Return: return int
*/
int Jag__strcmp(const char *string1, const char *string2)
{
	while (*string1 && (*string1 == *string2))
	{
		string1++;
		string2++;
	}
	return (*(unsigned char *)string1 - *(unsigned char *)string2);
}

/**
* Jag__strlen - Calculates the length of a string
* @str: The input string
* Return: The length of the string
*/
size_t Jag__strlen(const char *str)
{
	const char *s;

	for (s = str; *s; ++s)
		;
	return (s - str);

}

/**
 * Jag__space - Checks if a character is a whitespace character
 * @c: The character to check
 * Return: 1 if it's a whitespace character, 0 otherwise
 */
int Jag__space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

/**
 * Jag_c_memmov - Move memory block
 * @dest: Pointer to the destination memory block
 * @src: Pointer to the source memory block
 * @n: Number of bytes to move
 *
 * Return: des
 * This function moves `num` bytes of memory from the source block pointed to
 * by `src` to the destination block pointed to by `des`. The memory blocks may
 * overlap. The function returns a pointer to the destination memory block.
 */
void *Jag_c_memmov(void *dest, const void *src, size_t n)
{
	char *to_dest, *current;
	const char *from_src;
	unsigned int j;

	to_dest = (char *)dest;
	from_src = (const char *)src;
	current = malloc(sizeof(char) * n);
	if (!current)
		return (NULL);
	for (j = 0; j < n; ++j)
		*(current + j) = *(from_src + j);
	for (j = 0; j < n; ++j)
		*(to_dest + j) = *(current + j);
	free(current);
	return (dest);
}

/**
* Jag_trim_buffer - leading and trailing whitespace from a buffer
* @buffer: The input buffer
* return:  always 0
*/
void Jag_trim_buffer(char *buffer)
{
	size_t size = _strlen(buffer), i = 0;

	if (size == 0)
		return;

	while (_space((unsigned char)buffer[i]))
		i++;

	c_memmov(buffer, buffer + i, size - i + 1);
	size -= i;

	while (size > 0 && _space((unsigned char)buffer[size - 1]))
		size--;

	buffer[size] = '\0';
}

