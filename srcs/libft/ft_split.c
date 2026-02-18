/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvoyer <arvoyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:13:35 by arvoyer           #+#    #+#             */
/*   Updated: 2024/02/16 13:05:19 by arvoyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_tablen(const char *str, char c);
static char	*ft_strdup_stop(const char *s, char c);
static char	**free_array(char **tab, int max);

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**tab;
	int		j;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (1 + ft_tablen(s, c)));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (s[j] && i < ft_tablen(s, c))
	{
		while (s[j] && s[j] == c)
			j++;
		if (s[j])
			tab[i] = ft_strdup_stop(&s[j], c);
		if (!tab[i])
			return (free_array(tab, i));
		while (s[j] && s[j] != c)
			j++;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

static char	*ft_strdup_stop(const char *s, char c)
{
	size_t	i;
	size_t	len;
	char	*copy;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

static int	ft_tablen(const char *str, char c)
{
	int	i;
	int	len;
	int	boolean;

	i = 0;
	len = 0;
	boolean = 0;
	while (str[i])
	{
		if (str[i] != c)
			boolean = 1;
		if (str[i] == c && i > 0 && str[i - 1] != c)
		{
			while (str[i] == c)
				i++;
			if (str[i])
				len++;
		}
		i++;
	}
	return (len + boolean);
}

static char	**free_array(char **tab, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

// #include <stdio.h>

// int		main(void)
// {
// 	const char		*str = NULL;
// 	char			sep;
// 	char			**tab;
// 	unsigned int	i;

// 	sep = ' ';
// 	i = 0;
// 	tab = ft_split(str, sep);
// 	printf("\n %s", *tab);
// 	while (tab[i])
// 	{
// 		printf("\n%s", tab[i]);
// 		i++;
// 	}
// 	free_array(tab, i);
// 	return (0);
// }