/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:24:49 by rboudwin          #+#    #+#             */
/*   Updated: 2023/11/26 19:28:32 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_read_as_needed(int fd, char *stash)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;

	while (!ft_strchr(stash, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
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

	strchr_result = ft_strchr(stash, '\n');
	if (!strchr_result)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	else
		return (strchr_result);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	if (stash == NULL)
	{
		stash = malloc(1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	stash = ft_read_as_needed(fd, stash);
//printf("after reads stash is '%s'", stash);
	line = ft_fetch_line(stash);
	stash = ft_trim_stash(stash);
	return (line);
}
