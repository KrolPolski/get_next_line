/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:26:13 by rboudwin          #+#    #+#             */
/*   Updated: 2023/11/20 15:38:54 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

/* Let's think through the problem. 
 *
 * The challenge is, we do not know:
 * 1) if the buffer will run out before we have a \n
 * 2) if the \n will come before the end of the buffer
 * 
 *
 *
 * */
char	*get_next_line(int fd)
{
	char		*current_line;
	static char	*buffer = NULL;
	int			bytes_read;
	int			i;
	int			j;
	int			k;
	int			len;

	i = 0;
	len = 0;
	j = 0;
	if (buffer == NULL)
	{
		buffer = malloc(BUFFER_SIZE);
		if (buffer == NULL)
			return (NULL);
		bytes_read = read(fd, buffer, BUFFER_SIZE); 
		printf("Buffer is '%s'\n", buffer);
	}
	else
	{
		while (buffer[i] != '\n')
		{
			i++;
		}
		buffer = &buffer[i - 1];
	}
	current_line = NULL;
	while (current_line == NULL)
	{
		while (buffer[i] != '\0')
		{
			while (buffer[i] != '\n')
			{
				len++;
				i++;
	//			printf("i is now '%d'\n", i);
			}
			if (buffer[i] == '\n')
			{	
				k = i - len;
				current_line = malloc(len + 1);
				while (j < len)
				{
					current_line[j] = buffer[k];
					j++;
					k++;
				}
				current_line[j] = '\0';
				i++;
				return(current_line);
			}
		i++;	
		}
		current_line = buffer;
		k = len;
		buffer = malloc(BUFFER_SIZE);
		read(fd, buffer, BUFFER_SIZE);
		// do the next read and continue
	}

	// if we get here, we never found an EOL
	current_line = buffer;
	i = 0;


	return (NULL);
}

#include <fcntl.h>
int main(void)
{
	int fd;
	char *str;
	fd = open("fileread", O_RDONLY);
	printf("fd is %d\n", fd);
	str = get_next_line(fd);
	printf("%s\n", str); 
	str = get_next_line(fd);
	printf("%s\n", str); 
	str = get_next_line(fd);
	printf("%s\n", str); 
	str = get_next_line(fd);
	printf("%s\n", str); 
	str = get_next_line(fd);
	printf("%s\n", str); 
	str = get_next_line(fd);
	printf("%s\n", str); 
	str = get_next_line(fd);
	printf("%s\n", str); 
	str = get_next_line(fd);
	printf("%s\n", str); 


		free(str);
}
