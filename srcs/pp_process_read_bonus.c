/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_process_read_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:34:02 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/01 16:34:15 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>
#include "pipex.h"

int	pp_process_read_bonus(char *filename, int *pipe_fd)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	if (pp_read_file_bonus(filename) != 0)
	{
		perror(filename);
		return (1);
	}
	return (0);
}
