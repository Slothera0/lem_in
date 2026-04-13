#include "vector.h"
#include "libft.h"
#include "rend.h"

#include <stdio.h>

t_vector *create_path(char **split_line)
{
	t_vector *path = vec_create(10);
	if (!path)
		return (NULL);
	
	for (int i = 0; split_line[i]; i++)
	{
		if (split_line[i][0] != 'L')
			continue ;
		t_path *p = malloc(sizeof(t_path));
		if (!p)
		{
			vec_iter(path, free);
			vec_free(path);
			return (NULL);
		}
		char **one_path = ft_split(split_line[i] + 1, '-'); // voir si + 1 casse pas tout
		if (!one_path)
		{
			free(p);
			vec_iter(path, free);
			vec_free(path);
			return (NULL);
		}
		if (ft_sstrlen(one_path) != 2)
		{
			ft_free_array(one_path);
			free(p);
			continue ;
		}
		if (!is_a_num(one_path[0]))
		{
			ft_free_array(one_path);
			free(p);
			continue ;
		}
		p->ant = ft_atoi(one_path[0]);
		p->node = ft_strdup(one_path[1]);
		if (!p->node)		
		{
			ft_free_array(one_path);
			free(p);
			vec_iter(path, free);
			vec_free(path);
			return (NULL);
		}
		ft_free_array(one_path);
	
		if (p->node[ft_strlen(p->node) - 1] == '\n')
			p->node[ft_strlen(p->node) - 1] = '\0';
		path = vec_append(path, p);
		if (!path)
		{
			free(p->node);
			free(p);
			return (NULL);
		}
	}
	return (path);
}