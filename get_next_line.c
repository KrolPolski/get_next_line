/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:26:13 by rboudwin          #+#    #+#             */
/*   Updated: 2023/11/24 19:39:56 by rboudwin         ###   ########.fr       */
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

static char	*process_stash(char **stashes, int fd)
{
	//char		*result;
	char 		*substr_result;
	char		*ptr_parking;
	int			i;

	i = 0;
	//printf("We are trying to process a stash");
	while (stashes[fd][i] != '\0')
		{
			if (stashes[fd][i] != '\n')
				i++;
			else if (stashes[fd][i] == '\n')
			{
				substr_result = ft_substr(stashes[fd], 0, i + 1);
				if (substr_result == NULL)
					return (NULL);
				//printf("stashes[fd] is currently '%s'", stashes[fd]);
				//printf("and substr_result is currently '%s'", substr_result);
				//result = ft_strjoin(stashes[fd], substr_result);
				ptr_parking = stashes[fd];
				i++;
				stashes[fd] = ft_substr(stashes[fd], i, ft_strlen(stashes[fd])- i);
				//printf("stashes[fd] after substringing is now '%s'", stashes[fd]);
				free(ptr_parking);
				return(substr_result);
				//if (result == NULL)
				//	return (NULL);
				//printf("result of strjoin is %s", result);
				//free(stashes[fd]);
				//stashes[fd] = NULL;
				//free(substr_result);
				//substr_result = NULL;
				/*if (stashes[fd][i+1] != '\0')
				{
					//i++;
					stashes[fd] = ft_substr(stashes[fd], i + 1, ft_strlen(stashes[fd] - i));
				}
				return (result);*/
			}
		}
	return (NULL);
}
char	*get_next_line(int fd)
{
	static char	*stashes[256];
	char		*ptr_parking;
	int			bytes_read;
	char		buffer[BUFFER_SIZE + 1];
	int			i;
	char		*result;
	

	i = 0;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	
	if (bytes_read == -1) //this is not handling the case where we have 
	//stash left over but nothing more to read
		return (NULL);
	
	//buffer[bytes_read] = '\0';

	//above line got changed from BUFFER_SIZE
	if (stashes[fd] == NULL)
	{
		stashes[fd] = malloc(1);
		if (stashes[fd] == NULL)
			return (NULL);
		stashes[fd][0] = '\0';
	}
	ptr_parking = stashes[fd];
	//printf("Buffer is '%s'\n", buffer);
	stashes[fd] = ft_strjoin(ptr_parking, buffer);
	free(ptr_parking);
	result = process_stash(stashes, fd);
		//printf("on exiting process_stash, stashes[fd] is currently '%s'\n", stashes[fd]);
	if (result != NULL)
		return (result);
	while (bytes_read > 0)
	{
		// we ran out of stuff to read before we found a nl, need to chain reads
		ptr_parking = stashes[fd];
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		if (bytes_read == 0)
			return (stashes[fd]);
		stashes[fd] = ft_strjoin(ptr_parking, buffer);
		//printf("result of strjoin is %s\n", stashes[fd]);
		free(ptr_parking);
		ptr_parking = NULL;
		if (bytes_read < BUFFER_SIZE)
			return (stashes[fd]);
	}
		return (stashes[fd]);
		//return (NULL);
	/*
	//	ft_bzero(buffer, BUFFER_SIZE + 1);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		if (bytes_read == 0)
			return (stashes[fd]);
		
		buffer[bytes_read] = '\0';
		i = 0;}
	}
	if (stashes[fd] != NULL)
		return(stashes[fd]);
	free(stashes[fd]);
	stashes[fd] = NULL;
	//ft_bzero(buffer, BUFFER_SIZE + 1);*/
	return (NULL);
}

