/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvoyer <arvoyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:58:38 by arvoyer           #+#    #+#             */
/*   Updated: 2023/11/27 12:48:14 by arvoyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str)
{
	if (!str)
		return (write(1, "(null)", 6));
	if (write(1, str, ft_strlen(str)) < 0)
		return (-1);
	return (ft_strlen(str));
}
