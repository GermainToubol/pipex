/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_read_file_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:36:02 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/01 16:08:23 by gtoubol          ###   ########.fr       */
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

int	pp_read_file_bonus(char *end_name)
{
	int		len;
	char	*line;

	len = ft_strlen(end_name);
	while (errno == 0)
	{
		line = get_next_line(0);
		if (line == NULL)
			continue ;
		if (ft_strncmp(line, end_name, len) == 0 && line[len] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, 1);
		free(line);
	}
	if (errno != 0)
		return (1);
	return (0);
}
