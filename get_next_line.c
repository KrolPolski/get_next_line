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
	static char	*stashes[sizeof(char *) * 256];
	char		*ptr_parking;
	int			bytes_read;
	char		buffer[BUFFER_SIZE];
	
	int			i;
	char		*result;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (stashes[fd] == NULL)
	{
		stashes[fd] = malloc(1);
		if (stashes[fd] == NULL)
			return (NULL);
		// stashes[fd][0] = '\0';
	}
	//printf("About to enter the loop \n");
	while (bytes_read != 0)
	{
		while(buffer[i] != '\0')
		{
			if (buffer[i] != '\n')
				i++;
			else if (buffer[i] == '\n')
			{
			//	printf("We found a new line\n");
				ptr_parking = stashes[fd];
				result = ft_strjoin(ptr_parking, ft_substr(buffer, 0, i));
				free(ptr_parking);
				stashes[fd] = ft_substr(buffer, i, BUFFER_SIZE - i);
				return (result);
			}
		}
		// this should only trigger if we hit end of buffer without a newline
		ptr_parking = stashes[fd];
		stashes[fd] = ft_strjoin(ptr_parking, buffer);
		free(ptr_parking);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		i = 0;
	}
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
