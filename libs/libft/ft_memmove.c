/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvoyer <arvoyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:32:48 by arvoyer           #+#    #+#             */
/*   Updated: 2023/11/14 13:26:11 by arvoyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	if (dest < src)
	{
		while (i < n)
		{
			((unsigned char *)(dest))[i] = ((unsigned char *)(src))[i];
			i++;
		}
	}
	else
	{
		while (n > 0)
		{
			n--;
			((unsigned char *)(dest))[n] = ((unsigned char *)(src))[n];
		}
	}
	return (dest);
}
