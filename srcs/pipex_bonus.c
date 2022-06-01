/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:09:17 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/01 17:00:10 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"
#include "pipex.h"

static void	pp_close_pipes(int pfd[2][2])
{
	close(pfd[0][0]);
	close(pfd[0][1]);
	close(pfd[1][0]);
	close(pfd[1][1]);
}

int	main(int argc, char **argv)
{
	int	pfd[2][2];
	int	status;
	int	is_son;
	int	i;
	int	here_doc;

	if (argc < 5)
		return (0);
	is_son = 0;
	i = 1;
	if (ft_strcmp(argv[i], "here_doc") == 0)
		i++;
	here_doc = i - 1;
	status = do_read_bonus(argv[i], pfd[i % 2], &is_son, here_doc);
	while (!is_son && status == 0 && i < argc - 1)
	{
		status = do_process(argv[i], pfd[i % 2], pfd[(i + 1) % 2], &is_son);
		i++;
	}
	if (!is_son && status == 0)
		status = do_write_bonus(argv[i], pfd[i % 2], &is_son, here_doc);
	pp_close_pipes(pfd);
	return (status);
}
