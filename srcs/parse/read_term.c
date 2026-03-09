#include "get_next_line.h"
#include "libft.h"
#include "node.h"
#include "vector.h"
#include "ft_error.h"
#include "lem_in.h"
#include <errno.h>
#include <stdio.h>

int 	create_link(t_vector *nodes, char *args);
int 	create_node(t_vector *nodes, char **args, t_room_type type);
void	free_node(void *data);

static int			get_nb_ant();
static t_vector		*parse_data();
static t_room_type 	parse_nodes(t_vector *nodes, char *line, t_room_type type);
static void			parse_link(t_vector *nodes, char *line);
static t_room_type	set_type(char *line);

t_lem_in *read_term()
{
	t_lem_in	*data;

	data = malloc(sizeof(t_lem_in));
	if (!data)
	{
		perror("ERROR");
		exit(1);
	}

	data->nb_ants = get_nb_ant();
	if (data->nb_ants <= 0)
	{
		free(data);
		get_next_line(-1);
		if (errno == 0)
			ft_putstr_fd("ERROR\n", 2);
		else
			perror("ERROR");
		exit(1);
	}
	
	data->node = parse_data();
	if (!data->node)
	{
		free(data);
		perror("ERROR");
		exit(1);
	}

	return (data);
}


static t_room_type	set_type(char *line)
{
	if (ft_strncmp(line, "##start", ft_strlen(line)) == 0)
		return (START);
	if (ft_strncmp(line, "##end", ft_strlen(line)) == 0)
		return (END);
	return (NORMAL);
}

static int	get_nb_ant()
{
	char 	*line;
	int		nb_ant;		

	nb_ant = -1;
	line = get_next_line(0);
	if (line)
		nb_ant = ft_atoi(line);

	free(line);
	return (nb_ant);
}

static t_vector *parse_data()
{
	t_vector	*nodes = vec_create(10);
	char		*line = get_next_line(0);
	t_room_type	type = NORMAL;

	if (!nodes)
		return (NULL);
	while (line)
	{
		type = parse_nodes(nodes, line, type);
		if (errno != 0)
		{
			if (errno < 0)
			{
				errno = 0;
				break ;
			}
			free(line);
			vec_iter(nodes, free_node);
			vec_free(nodes);
			return (NULL);
		}
		free(line);
		line = get_next_line(0);
	}

	while (line)
	{
		parse_link(nodes, line);
		if (errno != 0)
		{
			free(line);
			if (errno > 0)
			{
				vec_iter(nodes, free_node);
				vec_free(nodes);
				return (NULL);
			}
			return (nodes);
		}
		free(line);
		line = get_next_line(0);
	}
	return (nodes);
}

static t_room_type parse_nodes(t_vector *nodes, char *line, t_room_type type)
{
	char	**split_line = NULL;

	if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	if (!line || line[0] == '\0')
	{
		errno = PARSE_ERROR;
		get_next_line(-1);
		return (type);
	}
	if (line[0] == '#')
		type = set_type(line);
	else
	{
		split_line = ft_split(line, ' ');
		int	ret = create_node(nodes, split_line, type);
		if (ret == MALLOC_ERROR)
		{
			ft_free_array(split_line);
			get_next_line(-1);
			return (type);
		}
		else if (ret == PARSE_ERROR)
		{
			errno = PARSE_ERROR;
			ft_free_array(split_line);
			return (type);
		}
		type = NORMAL;
		ft_free_array(split_line);
	}
	return (type);
}

static void	parse_link(t_vector *nodes, char *line)
{
	if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	if (line[0] == '#')
		return ;
	int ret = create_link(nodes, line);
	if (ret == MALLOC_ERROR)
	{
		get_next_line(-1);
		return ;
	}
	else if (ret == PARSE_ERROR)
	{
		errno = PARSE_ERROR;
		get_next_line(-1);
		return ;
	}
}