#include "vector.h"
#include "rend.h"
#include "libft.h"
#include "get_next_line.h"

#include <stdio.h>

t_vector	*create_path(char **split_line, t_vector *nodes);
void 		free_path(void *data);

t_vector	*read_ants_path(t_vector *nodes)
{
	t_vector *paths = vec_create(10);
	if (!paths)
		return (NULL);

	char *line = get_next_line(0);
	while (line)
	{
		remove_endline(line);
		if (!line[0])
		{
			free(line);
			line = get_next_line(0);
			continue ;
		}
		char **split_line = ft_split(line, ' ');
		free(line);
		if (!split_line)
		{
			vec_iter(paths, vec_free);
			vec_free(paths);
			get_next_line(-1);
			return (NULL);
		}
		t_vector *path = create_path(split_line, nodes);
		ft_free_array(split_line);
		if (!path)	
		{
			for(unsigned int i = 0; i < paths->size; i++)
			{
				vec_iter(paths->array[i], free_path);
			}
			vec_iter(paths, vec_free);
			vec_free(paths);
			get_next_line(-1);
			return (NULL);
		}
		paths = vec_append(paths, path);
		if (!paths)
		{
			vec_iter(path, free_path);
			vec_free(path);
			get_next_line(-1);
			return (NULL);
		}

		line = get_next_line(0);
	}
	return (paths);
}