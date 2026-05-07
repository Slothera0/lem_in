#include "get_next_line.h"
#include "libft.h"

int	get_nb_ant()
{
	char 	*line;
	int		nb_ant;

	nb_ant = -1;
	line = get_next_line(0);
	if (!line)
		return (0);

	if (!is_a_num(line))
	{
		free(line);
		return (0);
	}

	nb_ant = ft_atoi(line);
	free(line);
	if (nb_ant < 0)
		return (0);
	return (nb_ant);
}
