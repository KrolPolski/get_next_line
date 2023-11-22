/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:26:23 by rboudwin          #+#    #+#             */
/*   Updated: 2023/11/20 16:23:45 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int		i;
	size_t	length;

	i = 0;
	length = 0;
	while (s[i] != '\0')
	{
		length++;
		i++;
	}
	return (length);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	int		i;
	size_t	j;

	i = start;
	j = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s) || s[0] == '\0' || len == 0)
	{
		substring = malloc(1);
		substring[0] = '\0';
		return (substring);
	}
	if (ft_strlen(s) > len)
		substring = malloc(len + 1);
	else
		substring = malloc(ft_strlen(s) + 1 - start);
	if (substring == NULL)
		return (NULL);
	while (s[i] != '\0' && j < len)
		substring[j++] = s[i++];
	substring[j] = '\0';
	return (substring);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_length;
	int		s2_length;
	char	*new_string;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	new_string = malloc(s1_length + s2_length + 1);
	if (new_string == NULL)
		return (NULL);
	ft_strlcpy(new_string, s1, s1_length + 1);
	ft_strlcat(new_string, s2, s1_length + s2_length + 1);
	return (new_string);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclength;
	size_t	dstlength;
	size_t	i;
	size_t	j;
	size_t	max;

	srclength = ft_strlen(src);
	if (dstsize == 0)
		return (dstsize + srclength);
	dstlength = ft_strlen(dst);
	max = dstsize - dstlength;
	if (dstsize <= dstlength)
		return (dstsize + srclength);
	i = 0;
	j = 0;
	while (dst[j] != '\0')
		j++;
	while (src[i] != '\0' && i < max - 1)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (srclength + dstlength);
}