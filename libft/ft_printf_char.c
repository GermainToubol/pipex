/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:04:39 by gtoubol           #+#    #+#             */
/*   Updated: 2022/05/16 16:52:49 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"

int	ft_printf_char(char c, t_convert *convert)
{
	int	len;

	len = 0;
	convert->padd_char = ' ';
	if (!convert->leftify)
		len += ft_printf_padding(1, convert);
	len += write(1, &c, 1);
	len += ft_printf_padding(len, convert);
	return (len);
}
