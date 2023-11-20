/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:26:13 by rboudwin          #+#    #+#             */
/*   Updated: 2023/11/20 16:26:03 by rboudwin         ###   ########.fr       */
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
	static char	buffer[BUFFER_SIZE];
	int			bytes_read;
	int			len;
	int			i;
	char		*current_line;
	
	current_line[0] = '\0';
	i = 0;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1)
		return (NULL);
	while(bytes_read != 0)
	{
		// handle case of new line coming before end of buffer
		while (buffer[i] != '\0' && buffer[i] != '\n')
		{
			len++;
			i++;
		}
		if (buffer[i] == '\n')
		{
			current_line = ft_strjoin(current_line, buffer[i]);
			return(current_line);
		}
		if (buffer[i] == '\0')
			current_line = ft_strjoin();
		// handle case of end of buffer coming before new line

	}
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
