#include "get_next_line.h"
#include "libft.h"
#include "lem_in.h"

void create_link();
void create_node();

static t_room_type	set_type(char *line);

t_node *read_term()
{
	t_node		*nodes = NULL;
	char		*line;
	char		**split_line;
	t_room_type	type;

	line = get_next_line(0);
	type = NORMAL;
	while (line)
	{
		if (line[0] == '#')
			type = set_type(line); // peut etre rajouter des options prochainement
		else
		{
			split_line = ft_split(line, ' ');
			if (ft_sstrlen(split_line) == 3)
				create_node();
			if (ft_sstrlen(split_line) == 1)
				create_link();
		}

		line = get_next_line(0);
	}

	return (nodes);
}


static t_room_type	set_type(char *line)
{
	if (ft_strncmp(line, "##start", ft_strlen(line)) == 0)
		return (START);
	if (ft_strncmp(line, "##end", ft_strlen(line)) == 0)
		return (END);
	return (NORMAL);
}
