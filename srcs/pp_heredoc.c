/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:52:35 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/07 09:52:36 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "pipex.h"

int	pp_heredoc(char *arg, int *here_doc)
{
	*here_doc = 0;
	if (ft_strcmp(arg, "here_doc") == 0)
		*here_doc = 1;
	return (0);
}
