/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvoyer <arvoyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 01:04:33 by arvoyer           #+#    #+#             */
/*   Updated: 2023/12/11 14:54:40 by arvoyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*str;
	int			ret;
	char		*buf;

	str = ft_strdup_stop(buffer);
	if (buffer)
		suppr_current_line(buffer, &buffer);
	if (str && str[ft_strlen(str) - 1] == '\n')
		return (str);
	ret = 1;
	while (ret > 0)
	{
		ret = read_line(&buf, fd);
		if (ret == 0)
			return (str);
		else if (ret < 0)
			return (NULL);
		str = ft_strjoin(str, ft_strdup_stop(buf));
		suppr_current_line(buf, &buffer);
		if (!str || str[ft_strlen(str) - 1] == '\n')
			break ;
	}
	return (str);
}

int	read_line(char **buf, int fd)
{
	int		ret;

	ret = 1;
	(*buf) = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!(*buf))
		return (-1);
	ret = read(fd, (*buf), BUFFER_SIZE);
	if (ret > 0)
		(*buf)[ret] = '\0';
	else
		free((*buf));
	return (ret);
}

