/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_read_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:04:53 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/06 15:36:21 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "pipex.h"

static int	pp_update_count(char *line, char *end_name, int *count);
static int	pp_join_lines(char **line, char **buffer);
static int	pp_read_return(char *buffer);

/*
 * Read the standart input until end_name matches the line content
 * (including C-d and '\n')
 *
 */

int	pp_read_heredoc(char *end_name)
{
	int		len;
	int		count;
	char	*line;
	char	*buffer;

	count = 0;
	buffer = NULL;
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
		if (pp_join_lines(&line, &buffer))
			break ;
	}
	return (pp_read_return(buffer));
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

static int	pp_join_lines(char **line, char **buffer)
{
	size_t	len;
	char	*new;

	if (*buffer == NULL)
		len = ft_strlen(*line);
	else
		len = ft_strlen(*line) + ft_strlen(*buffer);
	new = ft_calloc(len + 1, sizeof(*new));
	if (new == NULL)
	{
		free(*line);
		free(*buffer);
		*buffer = NULL;
		return (1);
	}
	if (buffer != NULL)
		ft_strlcat(new, *buffer, len + 1);
	ft_strlcat(new, *line, len + 1);
	free(*line);
	free(*buffer);
	*buffer = new;
	return (0);
}

static int	pp_read_return(char *buffer)
{
	if (errno != 0 || buffer == NULL)
	{
		free(buffer);
		return (1);
	}
	ft_printf("%s", buffer);
	free(buffer);
	return (0);
}
