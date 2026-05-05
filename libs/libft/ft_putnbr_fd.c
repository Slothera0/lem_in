/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvoyer <arvoyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:59:58 by arvoyer           #+#    #+#             */
/*   Updated: 2023/11/13 14:39:54 by arvoyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < -9)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-(n / 10), fd);
		ft_putchar_fd(-(n % 10) + '0', fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			ft_putchar_fd(-n + '0', fd);
		}
		else
			ft_putchar_fd(n + '0', fd);
	}
}
