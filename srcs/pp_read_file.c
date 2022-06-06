/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:55:49 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/06 14:22:07 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"
#include "pipex.h"

/*
 * Read the given file and put it content on STD_OUT.
 *
 */

#define BSIZE 4096

int	pp_read_file(char *filename)
{
	int		fd;
	char	*line;
	int re;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	line = ft_calloc(BUFFER_SIZE + 1, sizeof(*line));
	if (line == NULL)
		return (1);
	re = read(fd, line, BUFFER_SIZE);
	while (re > 0)
	{
		if (re > 0)
			ft_putstr_fd(line, 1);
		ft_bzero(line, (BUFFER_SIZE + 1) * sizeof(*line));
		re = read(fd, line, BUFFER_SIZE);
	}
	free(line);
	close(fd);
	if (errno != 0)
		return (1);
	return (0);
}
