/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvoyer <arvoyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:33:12 by arvoyer           #+#    #+#             */
/*   Updated: 2023/11/14 13:19:40 by arvoyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (c > 127)
		c -= 128;
	while (s[i])
	{
		if (s[i] == c)
			return (&(((char *)s)[i]));
		i++;
	}
	if (s[i] == c)
		return (&(((char *)s)[i]));
	return (NULL);
}
