#include "get_next_line.h"
#include "libft.h"
#include "node.h"
#include "vector.h"
#include "ft_error.h"

int create_link(t_vector *nodes, char *args);
int create_node(t_vector *nodes, char **args, t_room_type type);

static t_room_type	set_type(char *line);

t_vector *read_term()
{
	t_vector	*nodes = vec_create(10);
	char		*line = get_next_line(0);
	char		**split_line = NULL;
	t_room_type	type = NORMAL;

	while (line)
	{
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (line[0] == '#' || line[0] == 'L')
			type = set_type(line); // peut etre rajouter des options prochainement
		else
		{
			split_line = ft_split(line, ' ');
			if (ft_sstrlen(split_line) == 3)
			{
				int ret = create_node(nodes, split_line, type);
				type = NORMAL;
				if (ret == MALLOC_ERROR)
				{
					free(line);
					ft_free_array(split_line);
					vec_free(nodes);
					exit(ft_error(ret)); // peut être remplacer par perror ou strerror
				}
				else if (ret == PARSE_ERROR)
				{
					free(line);
					ft_free_array(split_line);
					break ;
				}
			}
			if (ft_sstrlen(split_line) == 1)
			{
				int ret = create_link(nodes, split_line[0]);
				if (ret == MALLOC_ERROR)
				{
					free(line);
					ft_free_array(split_line);
					vec_free(nodes);
					exit(ft_error(ret));
				}
				else if (ret == PARSE_ERROR)
				{
					free(line);
					ft_free_array(split_line);
					break ;
				}
			}
			ft_free_array(split_line);
		}

		free(line);
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
