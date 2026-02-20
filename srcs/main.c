#include "lem_in.h"
#include "vector.h"

t_vector *read_term();

int	main()
{
	
	t_vector *node;

	node = read_term();
	vec_free(node);
	return (0);
}