/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvoyer <arvoyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:34:32 by arvoyer           #+#    #+#             */
/*   Updated: 2023/11/14 13:19:55 by arvoyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (c > 127)
		c -= 128;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == c)
			return (&(((char *)s)[i]));
		i--;
	}
	return (NULL);
}
