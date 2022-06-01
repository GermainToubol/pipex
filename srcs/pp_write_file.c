/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_write_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:56:18 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/01 15:22:36 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"
#include "pipex.h"

int	pp_write_file(char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	line = get_next_line(0);
	while (line != NULL)
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(0);
	}
	close(fd);
	if (errno != 0)
		return (1);
	return (0);
}
