#include "get_next_line.h"
#include "libft.h"
#include "node.h"
#include "vector.h"
#include "ft_error.h"
#include "lem_in.h"
#include <errno.h>
#include <stdio.h>

int			one_end(t_vector *nodes);
int			one_start(t_vector *nodes);
t_room_type	set_type(char *line);
int			get_nb_ant();

static void			parse_data();
static t_room_type 	parse_nodes(char *line, t_room_type type);
static void			parse_link(char *line);

static t_vector *nodes;

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
	if (data->nb_ants == 0)
	{
		free(data);
		get_next_line(-1);
		if (errno == 0)
			ft_putstr_fd("ERROR\n", 2);
		else
			perror("ERROR");
		exit(1);
	}
	
	parse_data();
	data->node = nodes;
	if (!data->node)
	{
		free(data);
		if (errno > 0)
			perror("ERROR");
		else
			ft_putstr_fd("ERROR\n", 2);
		exit(1);
	}
	
	if (!one_start(nodes) || !one_end(nodes))
	{
		vec_iter(nodes, free_node);
		vec_free(nodes);
		free(data);
		ft_putstr_fd("ERROR\n", 2);
		exit(1);
	}

	return (data);
}

static void parse_data()
{
	char		*line = get_next_line(0);
	t_room_type	type = NORMAL;
	
	nodes = vec_create(100);
	
	if (!nodes)
		return ;
	while (line)
	{
		type = parse_nodes(line, type);
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
			nodes = NULL;
			return ;
		}
		free(line);
		line = get_next_line(0);
	}

	while (line)
	{
		parse_link(line);
		if (errno != 0)
		{
			free(line);
			if (errno > 0)
			{
				vec_iter(nodes, free_node);
				vec_free(nodes);
				nodes = NULL;
				return ;
			}
			return ;
		}
		free(line);
		line = get_next_line(0);
	}
	return ;
}

static t_room_type parse_nodes(char *line, t_room_type type)
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
		nodes = create_node(nodes, split_line, type);
		if (errno != 0)
		{
			if (errno > 0)
				get_next_line(-1);
			ft_free_array(split_line);
			return (type);
		}
		type = NORMAL;
		ft_free_array(split_line);
	}
	return (type);
}

static void	parse_link(char *line)
{
	if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	if (line[0] == '#')
		return ;
	int ret = create_link(nodes, line);
	if (ret == MALLOC_ERROR)
		get_next_line(-1);
	else if (ret == PARSE_ERROR)
	{
		errno = PARSE_ERROR;
		get_next_line(-1);
	}
}
