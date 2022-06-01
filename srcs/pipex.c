/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 09:31:07 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/01 16:10:01 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "pipex.h"

/*
 * 1. lire le fichier
 * 2. ecrire le fichier dans le pipe 0.
 * 3. exec de facon generale.
 *
 */

int	main(int argc, char **argv)
{
	int	pfd[2][2];
	int	status;
	int	is_son;

	if (argc != 5)
		return (0);
	is_son = 0;
	status = do_read(argv[1], pfd[0], &is_son);
	if (!is_son && status == 0)
		status = do_process(argv[2], pfd[0], pfd[1], &is_son);
	if (!is_son && status == 0)
		status = do_process(argv[3], pfd[1], pfd[0], &is_son);
	if (!is_son && status == 0)
		status = do_write(argv[4], pfd[0], &is_son);
	close(pfd[0][0]);
	close(pfd[0][1]);
	close(pfd[1][0]);
	close(pfd[1][1]);
	return (status);
}
