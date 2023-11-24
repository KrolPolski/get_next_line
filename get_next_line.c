/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:26:13 by rboudwin          #+#    #+#             */
/*   Updated: 2023/11/24 15:42:17 by rboudwin         ###   ########.fr       */
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
	static char	*stashes[256];
	char		*ptr_parking;
	int			bytes_read;
	char		buffer[BUFFER_SIZE + 1];
	int			i;
	char		*result;
	char 		*substr_result;

	i = 0;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	buffer[BUFFER_SIZE] = '\0';
	if (bytes_read == -1)
		return (NULL);
	while (bytes_read != 0)
	{
		if (stashes[fd] == NULL)
		{
			stashes[fd] = malloc(1);
			if (stashes[fd] == NULL)
				return (NULL);
			stashes[fd][0] = '\0';
		}
		while (buffer[i] != '\0')
		{
			if (buffer[i] != '\n')
				i++;
			else if (buffer[i] == '\n' || buffer[i] == 26)
			{
				//ptr_parking = stashes[fd];
				substr_result = ft_substr(buffer, 0, i);
				if (substr_result == NULL)
					return (NULL);
				result = ft_strjoin(stashes[fd], substr_result);
				if (result == NULL)
					return (NULL);
				free(stashes[fd]);
				stashes[fd] = NULL;
				free(substr_result);
				if (buffer[i+1] != '\0')
					stashes[fd] = ft_substr(buffer, i, BUFFER_SIZE - i);
				return (result);
			}
		}
		ptr_parking = stashes[fd];
		stashes[fd] = ft_strjoin(ptr_parking, buffer);
		free(ptr_parking);
		//ft_bzero(buffer, BUFFER_SIZE + 1);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[BUFFER_SIZE] = '\0';
		i = 0;
	}
	free(stashes[fd]);
	//ft_bzero(buffer, BUFFER_SIZE + 1);
	return (NULL);
}

