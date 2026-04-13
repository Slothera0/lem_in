#include "vector.h"
#include "rend.h"
#include "libft.h"
#include "get_next_line.h"

#include <stdio.h>

t_vector	*create_path(char **split_line);

t_vector	*read_ants_path()
{
	t_vector *paths = vec_create(10);
	if (!paths)
		return (NULL);
	
	char *line = get_next_line(0);
	while (line)
	{
		char **split_line = ft_split(line, ' ');
		free(line);
		if (!split_line)
		{
			vec_iter(paths, vec_free);
			vec_free(paths);
			get_next_line(-1);
			return (NULL);
		}
		t_vector *path = create_path(split_line);
		ft_free_array(split_line);
		if (!path)	
		{
			vec_iter(paths, vec_free);
			vec_free(paths);
			get_next_line(-1);
			return (NULL);
		}
		paths = vec_append(paths, path);
		if (!paths)
		{
			vec_free(path);
			get_next_line(-1);
			return (NULL);
		}

		line = get_next_line(0);
	}
	return (paths);
}