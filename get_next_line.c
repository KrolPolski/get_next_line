/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:15:14 by rboudwin          #+#    #+#             */
/*   Updated: 2023/11/25 16:56:02 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*initialize_stashes(char **stashes, t_gnl *gnl, int fd)
{
	if (stashes[fd] == NULL && gnl->buffer[0] == '\0')
		return (NULL);
	if (stashes[fd] == NULL)
	{
		stashes[fd] = malloc(1);
		if (stashes[fd] == NULL)
			return (NULL);
		stashes[fd][0] = '\0';
	}
	gnl->exp_buf = ft_strjoin(stashes[fd], gnl->buffer);
	return (gnl->exp_buf);
}

static char	*process_exp_buf(char **stashes, t_gnl *gnl, int fd)
{
	//parse what we have, and if needed use recursion to process it again?
	gnl->i = 0;
	while (gnl->exp_buf[gnl->i] != '\0')
	{
		if (gnl->exp_buf[gnl->i] != '\n')
			gnl->i++;
		else if (gnl->exp_buf[gnl->i] == '\n')
		{
			gnl->substr_result = ft_substr(gnl->exp_buf, 0, gnl->i + 1);
			if (gnl->substr_result == NULL)
				return (NULL);
			gnl->i++;
			free(stashes[fd]);
			stashes[fd] = NULL;
			stashes[fd] = ft_substr(gnl->exp_buf, gnl->i, ft_strlen(gnl->exp_buf) - gnl->i);
			//free(gnl->exp_buf);
			return (gnl->substr_result);
		}
	}
	return (NULL);
}

static char	*read_as_needed(char **stashes, t_gnl *gnl, int fd)
{
	gnl->bytes_read = read(fd, gnl->buffer, BUFFER_SIZE);
	if (gnl->bytes_read == -1)
		return (NULL);
	else if (gnl->bytes_read == 0)
	{
		free(stashes[fd]);
		stashes[fd] = NULL;
		return (gnl->exp_buf);
	}
	else
	{
		free(stashes[fd]);
		stashes[fd] = NULL;
		stashes[fd] = gnl->exp_buf;
		gnl->exp_buf = ft_strjoin(stashes[fd], gnl->buffer);
		//process_exp_buf(stashes, gnl, fd);
		return (gnl->exp_buf);
	}
}
char	*get_next_line(int fd)
{
	t_gnl		gnl;
	static char	*stashes[256];

	gnl.i = 0;
	gnl.bytes_read = read(fd, gnl.buffer, BUFFER_SIZE);
	if (gnl.bytes_read == -1)
		return (NULL);
	gnl.buffer[gnl.bytes_read] = '\0';
	if (!initialize_stashes(stashes, &gnl, fd))
		return (NULL);
	if (gnl.bytes_read == 0)
	{
		gnl.result = process_exp_buf(stashes, &gnl, fd);
		free(gnl.exp_buf);
		if (gnl.result == NULL)
		{
			free(stashes[fd]);
			stashes[fd] = NULL;
		}
		return (gnl.result);
	}

	//printf("We managed to initialize stashes\n");
	gnl.result = process_exp_buf(stashes, &gnl, fd);
	//printf("About to enter read as needed loop")
	while (gnl.result == NULL && gnl.bytes_read > 0)
	{
		read_as_needed(stashes, &gnl, fd);
		gnl.result = process_exp_buf(stashes, &gnl, fd);
	}
	// if we get here, we have failed to find an end of line.
	//printf("'%s'", gnl.exp_buf);
	if (!gnl.result)
	{
		return (gnl.exp_buf);
	}
	else
	{
		free(gnl.exp_buf);
		return (gnl.result);
	}
		
	//	printf("We managed to process_exp_buf\n");
	//return (gnl.result);
}