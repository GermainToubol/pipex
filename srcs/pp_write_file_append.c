/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_write_file_append.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:48:08 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/06 15:48:44 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "libft.h"
#include "pipex.h"

int	pp_write_file_append(char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd == -1)
		return (1);
	line = get_next_line(0);
	while (line != NULL && errno == 0)
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
