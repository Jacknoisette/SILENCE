#include "get_next_line.h"

char *ft_strdup(char *str)
{
	char *dest;
	int i;
	int len;

	len = 0;
	i = 0;
	while (str[len] != '\0')
		len++;
	dest = malloc((len + 1) * sizeof(char));
	while(str[i] != '\0')
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE];
	char line[70000];
	static int buffer_read;
	static int buffer_pos;
	int	i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_read == 0)
				break ;
		}
		line[i] = buffer[buffer_pos];
		if (line[i] == '\n' || buffer_pos > 70000)
			break ;
		buffer_pos++;
		i++;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}

int main(void)
{
	char *test;
	int	i;

	i = 0;
	while (i < 10)
	{
		test = get_next_line(1);
		printf("%s", test);
		free(test);
		i++;
	}
	return (i);
}