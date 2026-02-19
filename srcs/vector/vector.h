#ifndef VECTOR_H
# define VECTOR_H

#include <stdlib.h>

typedef struct s_vector
{
	void 			**array;
	unsigned int	size;
	unsigned int	max_size;
} t_vector ;


t_vector	*vec_append(t_vector *vector, void *content);
t_vector	*vec_create(unsigned int size);
void		vec_copy(t_vector *src, t_vector *dest);
void		vec_free(t_vector *vector);


#endif