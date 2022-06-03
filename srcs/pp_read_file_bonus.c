/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_read_file_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:36:02 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/03 11:00:39 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stddef.h>
#include "libft.h"
#include "pipex.h"

/*
 * Read the given file and put it content on STD_OUT.
 *
 */

static int	pp_update_count(char *line, char *end_name, int *count);

int	pp_read_file_bonus(char *end_name)
{
	int		len;
	int		count;
	char	*line;

	count = 0;
	len = ft_strlen(end_name);
	while (errno == 0)
	{
		line = get_next_line(0);
		if (line == NULL)
			continue ;
		if (ft_strncmp(line, end_name + count, len - count) == 0
			&& line[len - count] == '\n')
		{
			free(line);
			break ;
		}
		if (pp_update_count(line, end_name, &count) != 0)
			continue ;
		ft_printf("%s", line);
		free(line);
	}
	if (errno != 0)
		return (1);
	return (0);
}

static int	pp_update_count(char *line, char *end_name, int *count)
{
	if (ft_strncmp(line, end_name + *count, ft_strlen(line)) == 0)
	{
		*count += ft_strlen(line);
		return (1);
	}
	write(1, end_name, *count);
	*count = 0;
	return (0);
}
