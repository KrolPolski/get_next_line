/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:24:49 by rboudwin          #+#    #+#             */
/*   Updated: 2023/11/27 13:47:00 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_read_as_needed(int fd, char *stash)
{
	char	*buffer;
	int		bytes_read;
	char	*ptr_parking;

	if (ft_strchr(stash, '\n'))
	{
		return (stash);
	}
	ptr_parking = NULL;
	bytes_read = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	
	while (!ft_strchr(stash, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
		else if (bytes_read == 0)
		{
			free(buffer);
			buffer = NULL;
			return (stash);
		}
		buffer[bytes_read] = '\0';
		if (stash == NULL)
		{
			stash = malloc(1);
			if (!stash)
				return (NULL);
			stash[0] = '\0';
		}
		ptr_parking = stash;
		stash = ft_strjoin(stash, buffer);
		free(ptr_parking);
		ptr_parking = NULL;
	}
	free(buffer);
	buffer = NULL;
	return (stash);
}

char	*ft_fetch_line(char *stash)
{
	char	*line;
	int		i;
	int		k;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (line == NULL)
		return (NULL);
	k = 0;
	while (k <= i)
	{
		line[k] = stash[k];
		k++;
	}
	if (stash[k] == '\n')
	{
		line[k] = stash[k];
		k++;
	}
	line[k] = '\0';
	return (line);
}

char	*ft_trim_stash(char *stash)
{
	char	*strchr_result;
	char	*ptr_parking;

	strchr_result = ft_strchr(stash, '\n');
	if (!strchr_result)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	// let's think through the problem. we get heap overflow if we go outside of bounds. that
	// +1 is doing that in some cases.
	else
	if (ft_strchr(stash, '\n') && ft_strlen(stash) == 1)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	{
		ptr_parking = stash;
		//this line is causing the heap overflow, but the code doesn't work without the + 1;
		//it is probably triggering only at the end of a file. 
		// if (strchr_result[1] != '\0')
		stash = ft_substr(stash, (strchr_result - stash) + 1, ft_strlen(stash));
		free(ptr_parking);
		ptr_parking = NULL;
		return (stash);
	}
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read_as_needed(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_fetch_line(stash);
	if (!line)
		return (NULL);
	stash = ft_trim_stash(stash);
	return (line);
}
