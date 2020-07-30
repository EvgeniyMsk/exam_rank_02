// Assignment name  : get_next_line
// Expected files   : get_next_line.c get_next_line.h
// Allowed functions: read, free, malloc
// --------------------------------------------------------------------------------
// Write a function will store, in the parameter "line", a line that has been read from the file descriptor 0.
// Your function must be prototyped as follows: int get_next_line(char **line);
// Your function should be memory leak free.
// What we call a "line that has been read" is a succession of 0 to n characters that end with '\n' (ascii code 0x0a) or with End Of File (EOF).
// The string stored in the parameter "line" should not contained any '\n'.
// The parameter is the address of a pointer to a character that will be used to store the line read.
// The return value can be 1, 0 or -1 depending on whether a line has been read, when the reading has been completed (meaning read has returned 0), 
// or if an error has happened respectively.
// When you've reached the End Of File, you must store the current buffer in "line". If the buffer is empty you must store an empty string in "line".
// When you've reached the End Of File, your function should keep 0 memory allocated with malloc except the last buffer that you should have stored in "line".
// What you've stored in "line" should be free-able.
// Calling your function get_next_line in a loop will therefore allow you to read the text available on a file descriptor one line at a time until the end of the text, 
// no matter the size of either the text or one of its lines.
// Make sure that your function behaves well when it reads from a file, from the standard output, from a redirection etc.
// No call to another function will be done on the file descriptor between 2 calls of get_next_line.
// Finally we consider that get_next_line has an undefined behavior when reading from a binary file.
// You should use the test.sh to help you test your get_next_line.

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

int			ft_strchr(char *str, char c)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = str;
	while (ptr[i] && !(ptr[i] == c))
		i++;
	if (ptr[i] == c)
		return (i);
	return (-1);
}

void		*ft_calloc(int n, size_t size)
{
	int		total;
	void	*result;

	total = n * size;
	if (!(result = malloc(total)))
		return (NULL);
	while (total--)
		*(unsigned char *)result++ = 0;
	return (result - n * size);
}

char		*ft_strjoin(char *str1, char *str2)
{
	char	*join;
	int		len;

	len = ft_strchr(str1, '\0') + ft_strchr(str2, '\0') + 1;
	if (!(join = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	while (*str1)
		*join++ = *str1++;
	while (*str2)
		*join++ = *str2++;
	*join++ = '\0';
	return (join - len);
}

char		*ft_substr(char *str, int start, int length)
{
	char	*sub;
	int		i;

	if (!(sub = (char *)malloc(sizeof(char) * length + 1)))
		return (NULL);
	i = 0;
	while (str[start] && length)
	{
		sub[i] = str[start];
		i++;
		start++;
		length--;
	}
	sub[i] = '\0';
	return (sub);
}

int					get_next_line(char **line)
{
	static char 	*rest;
	char			*buffer;
	char			*tmp;
	int				ret;

	if (!line)
		return (-1);
	if (!rest && !(rest = ft_calloc(1, sizeof(char))))
		return (-1);
	if (!(buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (-1);
	while (ft_strchr(rest, '\n') < 0 && ((ret = read(0, buffer, BUFFER_SIZE)) > 0))
	{
		buffer[ret] = 0;
		tmp = rest;
		rest = ft_strjoin(rest, buffer);
		free(tmp);
	}
	if (ret < 0)
		return (-1);
	*line = ft_substr(rest, 0, ft_strchr(rest, '\n'));
	if (ft_strchr(rest, '\n') < 0)
	{
		free(rest);
		return (0);
	}
	tmp = rest;
	rest = ft_substr(rest, ft_strchr(rest, '\n') + 1, ft_strchr(rest, '\0'));
	free(tmp);
	return (1);
}

int main(void)
{
	int		r;
	char	*line;

	line = NULL;
	while ((r = get_next_line(&line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	printf("%s", line);
	free(line);
	line = NULL;
}