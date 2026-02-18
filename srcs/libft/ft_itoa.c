/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvoyer <arvoyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:59:22 by arvoyer           #+#    #+#             */
/*   Updated: 2024/03/18 16:31:03 by arvoyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_size(int n);
static int	pos(int n);

char	*ft_itoa(int n)
{
	char	*s;
	size_t	len_nb;
	size_t	sign;

	len_nb = nb_size(n);
	s = (char *)malloc(sizeof(char) * (len_nb + 1));
	if (!s)
		return (NULL);
	sign = 0;
	if (n < 0)
		sign = 1;
	s[len_nb] = '\0';
	len_nb--;
	while (len_nb + 1 > sign)
	{
		s[len_nb] = pos(n % 10) + '0';
		n /= 10;
		len_nb--;
	}
	if (sign == 1)
		s[0] = '-';
	return (s);
}

static int	nb_size(int n)
{
	size_t	size;

	size = 1;
	if (n < 0)
		size++;
	while (n <= -10 || n >= 10)
	{
		size++;
		n /= 10;
	}
	return (size);
}

static int	pos(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}
