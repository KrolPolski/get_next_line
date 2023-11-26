/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:15:14 by rboudwin          #+#    #+#             */
/*   Updated: 2023/11/26 16:38:04 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	if (s[i] == c)
		return ((char *)&s[i]);
	else
		return (NULL);
}

char	*ft_strdup(const char *s1)
{
	int		length;
	char	*s2;

	length = ft_strlen(s1);
	s2 = malloc(length + 1);
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy(s2, s1, length + 1);
	return (s2);
}

char	*process_buffer(char *stash, t_gnl *gnl, int fd)
{
	ft_bzero(gnl->buffer, BUFFER_SIZE + 1);
	gnl->bytes_read = read(fd, gnl->buffer, BUFFER_SIZE);
	if (gnl->bytes_read == -1)
		return (NULL);
	if (stash == NULL && gnl->bytes_read == 0)
		return (NULL);
	gnl->buffer[gnl->bytes_read] = '\0';

	if (stash == NULL)
		stash = ft_strdup(gnl->buffer);
	else
	{
		gnl->ptr_parking = stash;
		stash = ft_strjoin(stash, gnl->buffer);
		free(gnl->ptr_parking);
		gnl->ptr_parking = NULL;
	}
	while (!ft_strchr(stash, '\n') && gnl->bytes_read > 0)
	{
		gnl->ptr_parking = stash;
		ft_bzero(gnl->buffer, BUFFER_SIZE + 1);
		gnl->bytes_read = read(fd, gnl->buffer, BUFFER_SIZE);
		stash = ft_strjoin(gnl->ptr_parking, gnl->buffer);
		free(gnl->ptr_parking);
		gnl->ptr_parking = NULL;
	}
	gnl->strchr_result = ft_strchr(stash, '\n');
	if (!gnl->strchr_result)
		return(stash);
	else
	{
		gnl->result = ft_substr(stash, 0, stash - gnl->strchr_result + 1);
		gnl->ptr_parking = stash;
		stash = ft_substr(gnl->ptr_parking, gnl->ptr_parking - gnl->strchr_result, ft_strlen(gnl->ptr_parking) - 1);
		free(gnl->ptr_parking);
		gnl->ptr_parking = NULL;
		if (stash[0] == '\0')
		{
			free(stash);
			stash = NULL;
		}
		if (gnl->result[0] == '\0')
		{
			free(gnl->result);
			gnl->result = NULL;
		}
		return (gnl->result);
	}
}
char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	t_gnl 		gnl;

	if (fd < 0 || fd > 1023)
		return (NULL);
	return (process_buffer(stash, &gnl, fd));
}
