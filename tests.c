/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:09:24 by rboudwin          #+#    #+#             */
/*   Updated: 2023/11/25 12:11:15 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("fileread", O_RDONLY);
	printf("fd is %d\n", fd);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	printf("Now running single character file test\n");
	fd = open("1char", O_RDONLY);
	printf("Fd is now %d\n", fd);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	printf("Now running test of alpha with no nl char\n");
	fd = open("alpha_nonl", O_RDONLY);
	printf("FD is now %d\n", fd);
	str = get_next_line(fd);
	printf("%s\n", str);
	free(str);
	printf("Now running single character no nl char test\n");
	fd = open("1char_nonl", O_RDONLY);
	str = get_next_line(fd);
	printf("%s\n", str);
	free(str);
	printf("Now running multiple nl only test\n");
	fd = open("mult_nl", O_RDONLY);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
}
