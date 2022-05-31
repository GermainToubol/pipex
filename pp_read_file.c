/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:55:49 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/31 18:19:50 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"
#include "pipex.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Read the given file and put it content on STD_OUT.
 *
 */

int	pp_read_file(char *filename)
{
	int		fd;
	char	*line;
	int tube[2];
	char *args[] = {"cat", NULL};

	pipe(tube);
	//dup2(tube[0], 0);
	dup2(tube[1], 1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_putstr_fd(line, tube[1]);
		free(line);
		line = get_next_line(fd);
	}
	execve("/usr/bin/cat", args, NULL);
	if (errno != 0)
		return (1);
	return (0);
}
