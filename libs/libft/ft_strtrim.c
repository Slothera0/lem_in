/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvoyer <arvoyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:01:02 by arvoyer           #+#    #+#             */
/*   Updated: 2023/11/10 17:39:18 by arvoyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (start < ft_strlen(s1) && in_set(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (end > 0 && in_set(s1[end], set))
		end--;
	if (end < start)
		new = malloc(sizeof(char));
	else
		new = malloc(sizeof(char) * (end - start + 2));
	if (!new)
		return (NULL);
	i = -1;
	while (++i + start < end + 1)
		new[i] = s1[start + i];
	new[i] = '\0';
	return (new);
}
