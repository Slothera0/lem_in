/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvoyer <arvoyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:00:34 by arvoyer           #+#    #+#             */
/*   Updated: 2023/11/10 17:40:23 by arvoyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*final_str;

	final_str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!final_str)
		return (NULL);
	final_str[0] = '\0';
	ft_strlcat(final_str, s1, (ft_strlen(s1) + ft_strlen(s2) + 1));
	ft_strlcat(final_str, s2, (ft_strlen(s1) + ft_strlen(s2) + 1));
	return (final_str);
}
