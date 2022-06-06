/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:55:49 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/06 15:47:25 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "libft.h"
#include "pipex.h"

/*
 * Read the given file and put it content on STD_OUT.
 *
 */

int	pp_read_file(char *filename)
{
	int		fd;
	char	buffer[R_BUFF_SIZE];
	ssize_t	re;
	ssize_t	w_status;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	ft_bzero(buffer, R_BUFF_SIZE * sizeof(*buffer));
	re = 1;
	w_status = 1;
	while (re > 0 && w_status > 0)
	{
		re = read(fd, buffer, R_BUFF_SIZE);
		if (re > 0)
			w_status = write(1, buffer, re);

	}
	close(fd);
	if (re < 0 || w_status < 0)
		return (1);
	return (0);
}
