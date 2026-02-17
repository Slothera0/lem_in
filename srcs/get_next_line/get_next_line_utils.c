/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvoyer <arvoyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 01:04:43 by arvoyer           #+#    #+#             */
/*   Updated: 2023/12/07 14:13:29 by arvoyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dst;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dst)
		return (double_free(s1, s2));
	i = 0;
	j = 0;
	while (s1 && s1[j])
	{
		dst[j] = s1[j];
		j++;
	}
	while (s2 && s2[i])
	{
		dst[j + i] = s2[i];
		i++;
	}
	dst[j + i] = '\0';
	double_free(s1, s2);
	return (dst);
}

char	*ft_strdup_stop(char *str)
{
	int		i;
	char	*dst;

	if (!str || !str[0])
		return (NULL);
	dst = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		dst[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		dst[i++] = '\n';
	dst[i] = '\0';
	return (dst);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*suppr_current_line(char *str, char **buffer)
{
	char		*dst;
	size_t		i;
	int long	j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	if (i == ft_strlen(str))
		(*buffer) = NULL;
	if (i == ft_strlen(str))
		return (double_free(str, NULL));
	dst = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!dst)
	{
		(*buffer) = NULL;
		return (double_free(str, NULL));
	}
	j = -1;
	while (str[i + (++j)])
		dst[j] = str[i + j];
	dst[j] = '\0';
	(*buffer) = dst;
	return (double_free(str, NULL), dst);
}

char	*double_free(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}
