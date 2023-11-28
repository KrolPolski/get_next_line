/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:24:49 by rboudwin          #+#    #+#             */
/*   Updated: 2023/11/28 10:52:46 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	a;

	if (!s)
		return (NULL);
	i = 0;
	a = (char)c;
	while (s[i] != a && s[i] != '\0')
		i++;
	if (s[i] == a)
		return ((char *)&s[i]);
	else
		return (NULL);
}

char	*ft_read_as_needed(int fd, char *stash, t_gnl *gnl)
{
	if (ft_strchr(stash, '\n'))
		return (stash);
	gnl->ptr_parking = NULL;
	gnl->bytes_read = 1;
	gnl->buffer = malloc(BUFFER_SIZE + 1);
	if (!gnl->buffer)
		return (NULL);
	while (!ft_strchr(stash, '\n') && gnl->bytes_read != 0)
	{
		gnl->bytes_read = read(fd, gnl->buffer, BUFFER_SIZE);
		if (gnl->bytes_read == -1)
		{
			free(gnl->buffer);
			free(stash);
			stash = NULL;
			gnl->buffer = NULL;
			return (NULL);
		}
		else if (gnl->bytes_read == 0)
		{
			free(gnl->buffer);
			gnl->buffer = NULL;
			return (stash);
		}
		gnl->buffer[gnl->bytes_read] = '\0';
		if (stash == NULL)
		{
			stash = malloc(1);
			if (!stash)
				return (NULL);
			stash[0] = '\0';
		}
		gnl->ptr_parking = stash;
		stash = ft_strjoin(stash, gnl->buffer);
		free(gnl->ptr_parking);
		gnl->ptr_parking = NULL;
	}
	free(gnl->buffer);
	gnl->buffer = NULL;
	return (stash);
}

char	*ft_fetch_line(char *stash, t_gnl *gnl)
{
	if (!stash)
		return (NULL);
	gnl->i = 0;
	while (stash[gnl->i] != '\0' && stash[gnl->i] != '\n')
		gnl->i++;
	gnl->line = malloc(gnl->i + 3);
	if (gnl->line == NULL)
		return (NULL);
	gnl->k = 0;
	while (gnl->k <= gnl->i)
	{
		gnl->line[gnl->k] = stash[gnl->k];
		gnl->k++;
	}
	if (stash[gnl->i] != '\0')
	{
		if (stash[gnl->k] == '\n' && stash[gnl->k - 1] != '\n')
		{
			gnl->line[gnl->k] = stash[gnl->k];
			gnl->k++;
		}
	}
	gnl->line[gnl->k] = '\0';
	return (gnl->line);
}

char	*ft_trim_stash(char *stash, t_gnl *gnl)
{
	gnl->strchr_result = ft_strchr(stash, '\n');
	if (!gnl->strchr_result)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	else if (ft_strchr(stash, '\n') && ft_strlen(gnl->strchr_result) == 1)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	{
		gnl->ptr_parking = stash;
		stash = ft_substr(stash, (gnl->strchr_result - stash) + 1, ft_strlen(stash));
		free(gnl->ptr_parking);
		gnl->ptr_parking = NULL;
		return (stash);
	}
}

char	*get_next_line(int fd)
{
	static char	*stash;
	t_gnl		gnl;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read_as_needed(fd, stash, &gnl);
	if (!stash)
		return (NULL);
	gnl.line = ft_fetch_line(stash, &gnl);
	if (!gnl.line)
		return (NULL);
	stash = ft_trim_stash(stash, &gnl);
	return (gnl.line);
}
