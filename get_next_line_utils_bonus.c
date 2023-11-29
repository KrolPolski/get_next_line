/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:55:53 by rboudwin          #+#    #+#             */
/*   Updated: 2023/11/29 12:55:58 by rboudwin         ###   ########.fr       */
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
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	new_string = malloc(s1_length + s2_length + 1);
	if (new_string == NULL)
		return (NULL);
	i = 0;
	while (i < s1_length && s1[i] != '\0')
	{
		new_string[i] = s1[i];
		i++;
	}
	new_string[i] = '\0';
	ft_strlcat(new_string, s2, s1_length + s2_length + 1);
	return (new_string);
}

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
