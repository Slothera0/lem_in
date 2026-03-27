/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvoyer <arvoyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:03:51 by arvoyer           #+#    #+#             */
/*   Updated: 2023/11/24 12:16:38 by arvoyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_digit(long long nbr, char *base);

int	ft_putnbr_base(long long nbr, char *base)
{
	int	temp;

	temp = 0;
	if (nbr > -ft_strlen(base) && nbr < ft_strlen(base))
		return (print_digit(nbr, base));
	if (nbr < 0)
	{
		if (ft_putchar('-') < 0)
			return (-1);
		temp = ft_putnbr_base(-(nbr / ft_strlen(base)), base);
		if (temp < 0 || ft_putchar((base[-(nbr % ft_strlen(base))])) < 0)
			return (-1);
		return (2 + temp);
	}
	temp = ft_putnbr_base(nbr / ft_strlen(base), base);
	if (temp < 0 || ft_putchar(base[nbr % ft_strlen(base)]) < 0)
		return (-1);
	return (1 + temp);
}

int	print_digit(long long nbr, char *base)
{
	if (nbr < 0)
	{
		if (ft_putchar('-') < 0 || ft_putchar(base[-nbr]) < 0)
			return (-1);
		return (2);
	}
	if (ft_putchar(base[nbr]) < 0)
		return (-1);
	return (1);
}
