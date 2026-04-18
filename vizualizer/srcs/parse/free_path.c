#include "rend.h"

void free_path(void *data)
{
	t_path *path = data;
	free(path->node);
	free(path);
}